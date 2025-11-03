#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/epoll.h>
#include <errno.h>
#include "serial.hpp"

int main()
{
   std::string port= "/dev/serial0";

   int open_port= open_serial(port, 9600);
 fprintf(stderr, "[INFO] opened %s\n", port.c_str());
    for(;;){
        read_serial(open_port);
        usleep(50'000); // 50 ms
    }
    close(open_port);

}