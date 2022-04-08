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
    //attempt to divide by zero. SIGFPE is called and the process exuectues error_handler
}

void error_handler(int signum){
    printf("This is Abe and I am in error handler after I divided by zero\n");
    fflush(stdout);
    int proc_id=fork();
    if(proc_id==0){
        printf("I am Issac. I was born into error_handler and my process id is %d\n", getpid());
        fflush(stdout);
        sleep(10);
        //child process sleeps until it receives a signal from parent. It then executs message_child
    }
    else{
        sleep(1);
        printf("This is Abe after fathering Issac. Abe's id is %d\n", getpid());
        fflush(stdout);
        kill(proc_id, SIGUSR1);
        //Parent process sent child a signal to execute message_child
        int status;
        wait(&status);
        //Parent will wait until child exits
        printf("This is Abe. Everyone is gone. Now I will die too\n");
        exit(1);
    }
}

void message_child(int signum){
    printf("This is Issac in message_child and my id is %d\n", getpid());
    fflush(stdout);
    signal (SIGUSR2, count_some);
    //Child process sends itself a signal to execute count_some function
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
    //grandchild process is created 
    int grand_id=fork();
    if(grand_id==0){
        printf("This is Jacob. I was born just now\n");
        //grandchild waits for sleeps for a second. It will be sent a signal to execute end_grand_child
        sleep(1);
    }
    else{
        printf("This is Issac. I am telling my son Jacob to terminate\n");
        kill(grand_id, SIGUSR1);
        //signal sent to from child to grandchild to enter the execute the end_grand_child function
        sleep(10);
        //sleeps until interuped by SIGINT 
        printf("This is Issac. Jacob send me a nasty message- he is now dead. Now is my turn\n");
        fflush(stdout);
        exit(1);
    }
}

void end_grand_child(int signum){
    printf("This is Jacob. Time to die. But first I will curse my father\n");
    fflush(stdout);
    kill(getpgid(getpid()), SIGINT);    
    //sleep(1);
    printf("Jacob's last words: goodbye\n");
    fflush(stdout);
    exit(1);
}

void curse_father(int signum){
    //Child process reads message sent from grandchild
    printf("Message from son Jacob: you stink\n");
    sleep(1);
    //gives grandchild time to exit
}



int main()
{
	int status;
    //assigning signal handlers
	signal (SIGCHLD, abe_handler);
	signal (SIGUSR1, message_child);
	signal (SIGFPE, error_handler);
    signal(SIGINT, curse_father);
    //creating new child
	if (!(fork())) {
        //child process
		exit(1);
	}
    //father waits for son to exit. When he does, father is sent SIGCHLD signal and executs abe_handler
	wait(&status);

}