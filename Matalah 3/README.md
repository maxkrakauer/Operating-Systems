# Threads

Program for sending clients messages, using multiple threads instead of multiple processes

## Compilation and Running

```
# makefile compiles the main file
make
# run the program
./main.o
```

## How the program works

The main thread listens for new client requests. After it accepts a requst it creates a new thread to deal with this client. The new thread executes the message_client function where it first locks the mutex and deals with the client. It sends "hello world" to the client and closes the connection, unclocks the mutex and exits the thread.

We can run 100 threads at the same time.

## Contributers

302245102

312708969

