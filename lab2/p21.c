#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv){
	pid_t child_pid;
	pid_t wait_pid;
	int status;
	child_pid = fork();
	if(child_pid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(child_pid == 0){
		printf("Child PID is %ld\n", (long) getpid());
		if(argc == 1){
            // wait signal from other program (than thar quite from thar "if")
			pause();
		}
        // exit the pid of process; atoi get the onli nuber in string
		_exit(atoi(argv[1]));
	}else{
		do{
            // wait ending child
			wait_pid = waitpid(child_pid, &status, WUNTRACED|WCONTINUED);
            // crash at waiting
			if(wait_pid == -1){
				perror("waitpid");
				exit(EXIT_FAILURE);
			}	
            // is the macross for output status ending
            // we send some signal with console into child process, then that macros write what's happening
			if(WIFEXITED(status)){
				printf("exited, status=%d\n", WEXITSTATUS(status));
			}else if(WIFSIGNALED(status)){
				printf("killed by signal %d\n", WTERMSIG(status));
			}else if(WIFSTOPPED(status)){
				printf("stopped by signal %d\n", WSTOPSIG(status));
			}else if (WIFCONTINUED(status)){
				printf("continued\n");
			}	
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
		exit(EXIT_SUCCESS);
	}
	return 0;
}
