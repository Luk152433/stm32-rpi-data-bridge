#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include "serial.hpp"
#include <optional>
#include <cstring>
#include "crc16.hpp"



#pragma pack(push, 1)
typedef struct {
    uint16_t sof;
    uint32_t timestamp;
    int16_t  temp;
    uint16_t press;
    uint16_t hum;
    uint16_t crc;
} DataFrame_t;
#pragma pack(pop)

std::optional<DataFrame_t> bytes_to_frame(const std::vector<uint8_t>& data);
std::optional<std::vector<uint8_t>> try_extract_frame(std::vector<uint8_t>& buf);

union DataFrameUnion {
    DataFrame_t frame;
    uint8_t     raw[sizeof(DataFrame_t)];
};

constexpr size_t FRAME_SIZE = sizeof(DataFrame_t);

int main()
{
   std::string port = "/dev/serial0";
    int open_port = open_serial(port, 9600);

    if (open_port < 0) {
        perror("open_serial");
        return 1;
    }

    fprintf(stderr, "[INFO] opened %s\n", port.c_str());

    std::vector<uint8_t> rx_buf;

    for (;;) {
        auto raw = read_serial(open_port);

        if (!raw.empty()) 
        {
            rx_buf.insert(rx_buf.end(), raw.begin(), raw.end());

            // wyciągamy ramki tak długo, jak się da
            while (true)
            {
                auto fb = try_extract_frame(rx_buf);
                if (!fb)
                    break;

                auto f = bytes_to_frame(*fb);
                if (!f)
                    continue; 

                printf("T = %.1f C, P = %u hPa, H = %u %%\n",
                       f->temp / 10.0,
                       f->press,
                       f->hum);
            }
        }

        usleep(50'000); // 50 ms
    }

    close(open_port);
    return 0;

}




std::optional<DataFrame_t> bytes_to_frame(const std::vector<uint8_t>& data)
{
    if (data.size() != FRAME_SIZE)
        return std::nullopt;

    DataFrame_t frame;
    std::memcpy(&frame, data.data(), FRAME_SIZE);


    if (frame.sof != 0xAA55)
        return std::nullopt;

       uint16_t crc_calc = CRC16_CCITT( reinterpret_cast<const uint8_t*>(&frame), sizeof(DataFrame_t) - sizeof(frame.crc));

    if (crc_calc != frame.crc)
        return std::nullopt;

    return frame;
}



std::optional<std::vector<uint8_t>> try_extract_frame(std::vector<uint8_t>& buf)
{
  
    size_t i = 0;
    while (i + 1 < buf.size()) {
        if (buf[i] == 0x55 && buf[i + 1] == 0xAA)
            break;
        ++i;
    }

   
    if (i > 0) {
        buf.erase(buf.begin(), buf.begin() + i);
    }


    if (buf.size() < FRAME_SIZE)
        return std::nullopt;


    std::vector<uint8_t> frame_bytes(FRAME_SIZE);
    std::copy(buf.begin(), buf.begin() + FRAME_SIZE, frame_bytes.begin());

    
    buf.erase(buf.begin(), buf.begin() + FRAME_SIZE);

    return frame_bytes;
}
