# Signals

Signal_2 is a program that creates recursive signals. That is, signals from whose handlers new signals are called.

## What does the program do

We start by assigning several handlers to signals. We create a new process and the father waits for the child to terminate (exit). A SIGCHLD signal is sent to the father notifying him that the child process has been terminated. The signal handler I assigned to SIGCHILD is abe_handler (abe is what I named this process.) 
Abe proceeds to divide (attempt to divide) by zero, from within abe_handler, and a SIGFPE signal is called. The corresponding handler is error_handler. Abe creates a new process that we call Issac and Abe sleeps for a second.
Meanwhile, Issac puts himself to sleep. When Abe wakes, he sends Issac a SIGUSR1 signal, whose handler is message_child. Abe then waits for Issac to terminate. Issac is now in the message_child function and and he sends himself the SIGUSR2 signals with handler count_some.
Issac counts to two, reassigns a new handler to SIGUSR1, end_grand_child, creates a new process, Jacob, sends Jacob a SIGUSR1 signal and puts himself to sleep. Jacob is executing the end_grand_child function now and he sends his father, Issac, a SIGINT signal, previously assigned the handler curse_father. Jacob exits. Issac is wakened by the signal, prints the message in curse_father and then exits. 
Abe, who has been waiting all this time, exits as well.

## Compiling and runing the program

```c
gcc signal_2.c -o signal_2.o
./signal_2.o


