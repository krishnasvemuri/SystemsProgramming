/* Name : Krishna Sindhuri Vemuri G-Number : G01024066
   Class : CS 531 Section : 003 Professor : Harold Greenwald
   HomeWork Assignment 1 Date November 1st 2017
*/

/* The following program
   --implements user defined system function with signal handling
*/


/* These are the header files needed for the program
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int cs531_system(char *comm); //Declared a user defined system function 

void signal_handler(int signo); //Declared a user defined signal _handler function


//The following code represents a function that catches the signals

void signal_handler(int signo) {
        printf("\nYou have entered the signal handler\n");
        if (signo == SIGINT)
                printf("received SIGINT with status %d\n", signo);
        if (signo == SIGQUIT)
                printf("received SIGQUIT with status %d\n", signo);
        if (signo == SIGSTOP)
                printf("This is never received!!!!!!!! SIGSTOP with status %d\n", signo);
        if (signo == SIGKILL)
                printf("This is never received!!!!!!!! SIGKILL with status %d\n", signo);
}

// This is the main function of the program and it takes command line arguments 

int main(int argc,char* argv[]){
     int status;
     status = cs531_system(argv[1]);
     return status;
}

//The follwing code implements the user defined system function

int cs531_system(char * comm) {
        pid_t child; //Creating a process
        int status; // Used to get the status of the process
        printf("The parent PID is %d\n", getpid());
        printf("The is the parent process, SIGINT and SIGQUIT are ignored here\n");
		printf("The process sleeps for 5 seconds\n");
        signal(SIGINT, SIG_IGN); //The signal Ctrl-C is ignored here 
        signal(SIGQUIT, SIG_IGN); //The signal Ctrl-\ is ignored here 
        sleep(5);
        if ((child = fork()) == 0) { // using fork a child process is created 
	    int tt = open("/dev/tty",O_RDWR); //We have now opened the /dev/tty terminal 
            close(0);dup(tt);
            close(1);dup(tt); 
            close(2);dup(tt); 
            close(tt);
                printf("The child PID is %d\n", getpid());
                printf("This is the child process, SIGINT and SIGQUIT are handled here\n");
				printf("The process sleeps for 15 seconds\n");
                execlp("sh", "sh", "-c", comm, (char * ) 0); // the execlp command is used to execute the shell commands 
                printf("Shell command is invalid\n");
                exit(1);
        }
        // the child sleeps for 15 seconds to check if the user sent any signals 
        if (child) {
                if (signal(SIGINT, signal_handler)==SIG_ERR)
	            printf("This can't happen\n");
                if (signal(SIGQUIT, signal_handler)==SIG_ERR)
	            printf("This can't happen\n");
		if (signal(SIGKILL, signal_handler) == SIG_ERR)
                    printf("\ncan't catch SIGKILL\n");
                if (signal(SIGSTOP, signal_handler) == SIG_ERR)
                    printf("\ncan't catch SIGSTOP\n");
                sleep(15);
        }
        // checks if fork failed 
        if (child == (pid_t)(-1)) {
                perror("Fork failed.\n");
                return -1;
        }
        waitpid(child, & status, 0); // the parent process waits until child is done
        printf("This is the parent process again, SIGINT and SIGQUIT are ignored here\n");
		printf("The process sleeps for 5 seconds\n");
        //The parent ignores the signal SIGINT and SIGQUIT
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        sleep(5);
        //The following code prints the exit status of the child 
	if(WIFEXITED(status)){
          printf("exited,status=%d\n",WEXITSTATUS(status));
        } else if(WIFSIGNALED(status)){
          printf("killed by signal %d\n",WTERMSIG(status));
        } else if(WIFSTOPPED(status)){
          printf("stopped by signal %d\n",WSTOPSIG(status));
        }else if(WIFCONTINUED(status)){
          printf("continued\n");
        }
        exit(status);

}

