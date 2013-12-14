#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(){
    int server, fd, count;
    int bufsize = 1024;
    char *buf = malloc(bufsize);
    char fname[256];
    struct sockaddr_in address;

    server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0){
        printf("Error creating socket");
        return -1;
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);
    
    if(connect(server,(struct sockaddr*)& address, sizeof(address)) == 0){
        printf("Connection with server established\n");
    }
    return 0;                                                   
}
