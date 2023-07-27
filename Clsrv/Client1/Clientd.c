#include <arpa/inet.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#define BILLION 1000000000L



int main(){
    struct timespec start, end;
    int t = 0;
    while(t <= 10000){
        const char* server_name = "localhost";
        const int server_port = 8877;
        struct sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        inet_pton(AF_INET, server_name, &server_address.sin_addr);
        server_address.sin_port = htons(server_port);
        uint64_t diff[10000];

        int sock;
        if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0){
            printf("Could not create socket\n");
            return 1;
        }
        else{
            printf("OK\n");
        }


        const char* data_to_send = "Give me count//";
        clock_gettime(CLOCK_MONOTONIC, &start);
        int len = sendto(sock, data_to_send, strlen(data_to_send), 0, (struct sockaddr*)&server_address, sizeof(server_address));
        printf("%d", len);   
        int arg;
        recvfrom(sock, &arg, sizeof(arg), 0, NULL, NULL);
        printf("recieved: '%d'\n", arg);
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff[t] = (BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec) / 1000;
        printf("Time = %llu millisec\n", (long long unsigned int) diff[t]);
        t++;
    
    close(sock);
    }
    return 0;
}