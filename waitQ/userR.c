#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>

#define SIZE 32
int main()
{
        int fd,ret;
        char buffR[SIZE];

        fd=open("/dev/sample0",O_RDWR);
        if(fd<0)
        {
                perror("error opening p\n");
                return fd;
        }

        ret = read(fd,buffR,SIZE);

        printf("GOT: %s NO of bytes read :%d\n",buffR,ret);

        return 0;
}

