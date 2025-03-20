#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>         
#include <cstring>

using namespace std;

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (fd < 0) { 
        perror("socket()"); 
        return 1;
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // Loopback IP (127.0.0.1)

    if (connect(fd, (const sockaddr*)&addr, sizeof(addr)) < 0) { 
        perror("connect() error");
        close(fd);
        return 1;
    }

    char msg[] = "hello";
    write(fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf)-1);
    if (n < 0) {
        perror("read() error");
        close(fd);
        return 1;
    }

    printf("server says: %s\n", rbuf);
    close(fd);
    return 0;
}
