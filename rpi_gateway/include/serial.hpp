#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <system_error>
#include <string>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>


int open_serial(const std::string& dev, int baud);
void read_serial(int port);
