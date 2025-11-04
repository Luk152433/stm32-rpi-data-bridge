#include "serial.hpp"

static speed_t to_baud(int b);

int open_serial(const std::string& port, int baud)
{

         int serial_port = open( port.c_str() , O_RDWR | O_NOCTTY | O_NONBLOCK);

       struct termios tty;

        if(tcgetattr(serial_port, &tty) != 0) {
            printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
            return 1;
         }
        
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag &= ~  CRTSCTS;
        tty.c_cflag &= ~  PARENB;  //wylaczenie parzystosci
          tty.c_cflag &= ~CSTOPB;  // czyscimy zeby jeden bit stopu
        tty.c_cflag |= CS8;                 // control
        tty.c_cflag |= CREAD;  // zalacza odbieranie
         tty.c_cflag |= CLOCAL; // nie wylacza   

        tty.c_lflag &= ~ ISIG;
        tty.c_lflag &= ~ ICANON;
        tty.c_lflag &= ~ ECHO;
        tty.c_lflag &= ~ECHOE;  
        tty.c_lflag &= ~ECHONL; 

         tty.c_iflag &= ~(IXON | IXOFF | IXANY); 
        tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

          tty.c_cc[VTIME] = 1;   
        tty.c_cc[VMIN] = 0;


         cfsetispeed(&tty, to_baud(baud));
        cfsetospeed(&tty, to_baud(baud));

 
        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
            printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
            return 1;
        }

        return serial_port;
}

std::vector<uint8_t> read_serial(int port)
{
    std::vector<uint8_t> data;
    uint8_t buf[256];

    ssize_t n = ::read(port, buf, sizeof(buf));
    if (n > 0) {
        printf("Odebrano %zd bajtów:\n", n);
          data.assign(buf, buf + n);

    } else if (n < 0 && errno != EAGAIN) {
        perror("read");
    }

    return data;

}

static speed_t to_baud(int b){
    switch(b){
        case 9600: return B9600; case 19200: return B19200; case 38400: return B38400;
        case 57600: return B57600; case 115200: return B115200; case 230400: return B230400;
        case 460800: return B460800; case 921600: return B921600; default: return B115200;
    }
}
