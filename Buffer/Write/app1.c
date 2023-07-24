#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
    int fd1;
    char buf1[20] = "Hello, there!";
    fd1 = open("/dev/foo", O_WRONLY);
    write(fd1, buf1, 14);
    printf("%d", fd1);
    close(fd1);
    return 0;
}