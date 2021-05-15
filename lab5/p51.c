#include<unistd.h>

int main(int argc, char** argv){
    char *buf[80];
    int len = read(STDIN_FILENO, buf, 80);
    write(STDOUT_FILENO, buf, len);
    write(STDERR_FILENO, buf, len);
    return 0;
}
