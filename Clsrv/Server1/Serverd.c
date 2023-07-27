#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "mydriverio.h"

int main(int argc, char *argv[]){

    int SERVER_PORT = 8877;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
        printf("Could not create socket\n");
        return 1;
    }
    else{
        printf("OK\n");
    }

    if((bind(sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0){
        printf("Could not bind socket///");
        return 1;
    }

    struct sockaddr_in client_address;
    int client_address_len = sizeof(server_address);
    
    int fd1;
    fd1 = open("/dev/foo", O_RDONLY);
    printf("%d\n", fd1);
    while(true){
        const int arg;
        ioctl(fd1, MYDRIVER_GET, &arg);
        printf("%d\n", arg);
        char buffer[500];
        
        sendto(sock, &arg, sizeof(arg), 0, (struct sockaddr *)&client_address, sizeof(client_address));
        int len = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_address, &client_address_len);

        printf("recieved: '%s' from client %s\n", buffer, inet_ntoa(client_address.sin_addr));
        
    }

    close(fd1);

    return 0;
}