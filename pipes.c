/*
This program emulates the behavior of the shell command "ps -aux | sort -r -n -k 5".
It creates two child processes. Child 1 executes the "ps -aux" command and redirects its stdout to the write end of a pipe.
Child 2 executes the "sort -r -n -k 5" command and redirects its stdin to the read end of the same pipe.
The parent process waits for both children to terminate before exiting.
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


//In the main() function, it creates a pipe using the pipe() function, then creates two child processes with fork().

//main function
int main(){
    int mypipe[2]; //creating pipe with read and write end | 0 - for read and 1 - for write
    pid_t child1, child2; //creating variable of type pid_t to store IDs for child process

    //creating the pipe using pipe() and immediately checking for errors i learnt from online sources that it is critical in C to check
    if (pipe(mypipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //Child 2 redirects its input from stdin to the read end of the pipe, then it executes the "sort -r -n -k 5" command.

    //Creating Child2 and checking for error
    child2 = fork();
    if (child2 == -1) {//child2 gets the copy reference to the read and write end.
        perror("fork");
        exit(EXIT_FAILURE);
    }


    if (child2 == 0) {

        //Redirecting to read end by "0" from stdin
        dup2(mypipe[0], STDIN_FILENO);
        close(mypipe[0]);
        close(mypipe[1]);

        // Execute "sort -r -n -k 5" command
        execlp("sort", "sort", "-r", "-n", "-k", "5", NULL);
        perror("execlp sort");
        exit(EXIT_FAILURE);
    }

    //Child 1 redirects stdout to the write end of the pipe and then executes with execlp() the "ps -aux" command.

    //creating child1
    child1 = fork();
    if (child1 == -1) {//checking for errors immediately
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0) {
        // Child 1: Redirect stdout to write end of the pipe
        dup2(mypipe[1], STDOUT_FILENO);
        close(mypipe[0]);
        close(mypipe[1]);

        // Execute "ps -aux" command
        execlp("ps", "ps", "-aux", NULL);
        perror("execlp ps");
        exit(EXIT_FAILURE);
    }

    // Closing the read and write ends for parent process.
    // Not necessary but i learned that it prevents resource leaks and is a good standard to close.
    close(mypipe[0]);
    close(mypipe[1]);

    // Waiting for both children to terminate
    // To make sure they terminate before parent process is closed and avoid errors and zombie/orphan processes.
    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    return 0;
}


