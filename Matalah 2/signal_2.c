#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void count_some(int signum);
void abe_handler(int signum);
void error_handler(int signum);
void message_child(int signum);
void end_grand_child(int signum);
void curse_father(int signum);

void abe_handler(int signum){
    printf("I am Abe and this is abe_handler\n");
    fflush(stdout);
    int i=5;
	int j=0;
	int k;
    k=i/j;
}

void error_handler(int signum){
    printf("This is Abe and I am in error handler after I divided by zero\n");
    fflush(stdout);
    int proc_id=fork();
    if(proc_id==0){
        printf("I am Issac. I was born into error_handler and my process id is %d\n", getpid());
        fflush(stdout);
        sleep(10);
    }
    else{
        sleep(1);
        printf("This is Abe after fathering Issac. Abe's id is %d\n", getpid());
        fflush(stdout);
        kill(proc_id, SIGUSR1);
        int status;
        wait(&status);
        printf("This is Abe. Everyone is gone. Now I will die too\n");
        exit(1);
    }
}

void message_child(int signum){
    printf("This is Issac in message_child and my id is %d\n", getpid());
    fflush(stdout);
    signal (SIGUSR2, count_some);
    raise(SIGUSR2);
}

void count_some(int signum){
    printf("I will count to 2\n");
    fflush(stdout);
    for(int i=0; i<3; i++){
        printf("i=%d\n", i);
        fflush(stdout);
    }
    int status;
    signal(SIGUSR1, end_grand_child);
    setpgid(getpid(), getpid());
    int grand_id=fork();
    if(grand_id==0){
        printf("This is Jacob. I was born just now\n");
        sleep(1);
    }
    else{
        kill(grand_id, SIGUSR1);
        //wait(&status);
        //pause();
        sleep(10);
        printf("This is Issac. Jacob woke me up- he is now dead. Now is my turn\n");
        fflush(stdout);
        exit(1);
    }
}

void end_grand_child(int signum){
    printf("This is Jacob. Time to die. But first I will curse my father\n");
    fflush(stdout);
    kill(getpgid(getpid()), SIGINT);
    sleep(10);
    exit(1);
}

void curse_father(int signum){
    printf("Message from son Jacob: you stink\n");
}



int main()
{
	int status;
	signal (SIGCHLD, abe_handler);
	signal (SIGUSR1, message_child);
	signal (SIGFPE, error_handler);
    signal(SIGINT, curse_father);
	if (!(fork())) {
		exit(1);
	}
	wait(&status);

}