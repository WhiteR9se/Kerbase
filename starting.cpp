#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <iostream>         
#include <reiserfs/misc.h>


using namespace std;

struct sockaddr_in {
    uint16_t sin_family; //af-inet . 16 bits presumably.
    uint16_t sin_port;   //port in big endian
    struct in_addr sin_addr; //ip v4
};
struct in_addr {
    uint32_t s_addr;  // ipv4 big endian
};

int main(){
    cout<<"hello\n";
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));    
    struct sockaddr_in addr = {};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(1234);
    addr.sin_addr.s_addr=htonl(0);

    int rv = bind(fd, (const sockaddr*)&addr, sizeof(addr));
    if(rv) {
        die("bind()");
    }


}