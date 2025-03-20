#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>        
#include <cstring>

using namespace std;

static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n = read(connfd, rbuf, sizeof(rbuf)-1);
    if (n < 0) {
        perror("read() error");
        return;
    }
    fprintf(stderr, "client says: %s\n", rbuf);

    char wbuf[] = "world";
    write(connfd, wbuf, strlen(wbuf));
}

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (fd < 0) { 
        perror("socket()"); 
        return 1;
    }

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET; 
    addr.sin_port = htons(1234);  // FIXED: Should use htons()
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, (const sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind() error");
        return 1;
    }

    if (listen(fd, SOMAXCONN) < 0) {
        perror("listen() error");
        return 1;
    }

    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            perror("accept() error");
            continue;
        }
        do_something(connfd);
        close(connfd);
    }

    close(fd);
    return 0;
}
