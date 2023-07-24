#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include "mydriverio.h"
int main(){
    int fd1;
    const int arg;
    int sec = 150;
    fd1 = open("/dev/foo", O_RDONLY);
    printf("%d", fd1);
    //ioctl(fd1, MYDRIVER_NULL, &arg);
    ioctl(fd1, MYDRIVER_SET, &sec);
    ioctl(fd1, MYDRIVER_GET, &arg);
    printf("%d", arg);
    close(fd1);
    return 0;
}