#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void handler(int signum){

    int num = 10;
    int zero = 0;
    switch(signum){

        case SIGCHLD:
            printf("1. child status changed signal handeled, lets call the illegal instruction signal \n"); // raised by wait()
            fflush(stdout); //present that print, clean the output buffer
            asm("ud2"); // raise SIGILL signal
            sleep(1);
            break;
        
        case SIGILL:
            printf("2. illegal instruction signal handeled, lets call the alarm signal \n");
            fflush(stdout);
            alarm(1); // will raise the SIGALRM signal
            sleep(1);
            break;
        
        case SIGALRM:
            printf("3. alarm signal handeled, lets call the Floating-Point arithmetic exeption signal \n");
            fflush(stdout);
            zero = num/zero; // will raise the SIGFPE signal
            sleep(1);
            break;
        
        case SIGFPE:
            printf("4. Floating-Point arithmetic exeption signal handeled, lets call the Segmentation Violation signal \n");
            fflush(stdout);
            sleep(1);
            int *p = 0;
		    *p = 30; // will raise the SIGSEGV signal
            break;
        
        case SIGSEGV:
            printf("5. Segmentation Violation signal handeled, lets call the first User-defined signal \n");
            fflush(stdout);
            sleep(1);
            raise(SIGUSR1); // will raise the SIGUSR1 signal
            break;
            

        case SIGUSR1:
            printf("6. first User-defined signal handeled, lets call the abort signal \n");
            printf("there been a mistake press ctrl c to terminate the program \n");
            fflush(stdout); // will raise the intterupted signal
            while(1){
                sleep(1);
            }
            break;

        case SIGINT:
            printf("\n7. gotcha, interrupted signal handeled, lets call the abort signal \n");
            fflush(stdout);
            sleep(1);
            abort(); // will raise the abort signal
            break;

        case SIGABRT:
            printf("8. abort signal handeled, lets call the second User-defined signal \n");
            fflush(stdout);
            sleep(1);
            kill(getpid(), SIGUSR2); // will raise the SIGUSR2 signal
            break;
        
        case SIGUSR2:
            printf("9. the last signal for today- the second User-defined signal handeled :) \n");
            fflush(stdout);
            exit(1);
            break;
    }
}

int main()
{
    signal(SIGCHLD, handler);
    signal(SIGILL, handler);
    signal(SIGALRM, handler);
    signal(SIGFPE, handler);
    signal(SIGSEGV, handler);
	signal(SIGUSR1, handler);
    signal(SIGINT, handler);
    signal(SIGABRT, handler);
	signal(SIGUSR2, handler);

    printf("today we will handle 9 diffrent signals, lets start with the first one- the child status changed signal \n");
 
    //raise the first signal- child stopped signal
	if (!(fork()))
	{
		exit(1);
	}
	wait(0);
}