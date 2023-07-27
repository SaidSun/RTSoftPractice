#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <>

int main(){
    int fd;
    char buf[100];
    fd = open("/dev/foo", O_RDONLY);
    printf("%d", fd);
    read(fd, buf, 5);
    printf("input >>> %s <<<\n", buf);
    close(fd);
    return 0;
}