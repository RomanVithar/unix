#include<unistd.h>
#define BLOCK 512

void copy(int fd1, int fd2){
    char buffer[BLOCK];
    int len;
    while((len = read(fd1, buffer, BLOCK))>0){
        write(fd2, buffer, len); 
    }
}

int main(void) {
    copy(0, 1);
    return 0;
}
