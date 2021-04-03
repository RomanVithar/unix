#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void sig_handler(int sig){
   switch(sig){
        case SIGINT:
            printf("catching SIGINT %d\n", sig);
            break;
        case SIGTSTP:
            printf("catching SIGSTP %d\n", sig);
            break;
        case SIGQUIT:
            printf("catching SIGQUIT %d\n", sig);
            break;
        default: 
            printf("Also catching SIGUSR1 %d\n", sig);
            break;
   }
}

int main(){
    if(signal(SIGINT, sig_handler) == SIG_ERR) perror("signal SIGINT");
    if(signal(SIGTSTP, sig_handler) == SIG_ERR) perror("signal SIGTSTP");
    if(signal(SIGQUIT, sig_handler) == SIG_ERR) perror("signal SIGQUIT");
    if(signal(SIGUSR1, sig_handler) == SIG_ERR) perror("signal SIGUSR1");
}
