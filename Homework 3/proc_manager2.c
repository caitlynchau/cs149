// Caitlyn Chau
// CS 149 Fall 20
// Assignment 3 Part 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#include "CommandNode.h"

int main(int argc, char * argv[]) {
    FILE * file;
    char * command = NULL;
    size_t len = 0;
    ssize_t read;
    char outFileName[10];
    char errFileName[10];
    int pid, status;

    struct timespec start, finish;
    double elapsed;

    /* Initialize linked list */
    CommandNode * head = NULL;
    CommandNode * current = NULL;
    CommandNode * prev = (CommandNode*)malloc(sizeof(CommandNode));
    int nodeIndex = 0;

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "proc_manager: cannot open file\n");
        exit(1);
    }

    /* Read all commands from file */
    while ((read = getline(&command, &len, file)) != -1) {
        // process line for command and arguments
        command[strlen(command) - 1] = 0; // replace newline with null
        char args[20][20];
        int j = 0, ctr = 0;
        // split string by space
        for (int i = 0; i <= (strlen(command)); i++) {
            if (command[i] == ' ' || command[i] == '\0') {
                args[ctr][j] = '\0';
                ctr++; // next word
                j = 0; // reset initial index to 0
            } else {
                args[ctr][j] = command[i];
                j++;
            }
        }

        // Create new linked list with parsed arguments
        current = (CommandNode*)malloc(sizeof(CommandNode));
        CreateCommandNode(current, args, nodeIndex, NULL);
        InsertCommandAfter(prev, current);
        prev = current;
        if (nodeIndex == 0) head = current;
        nodeIndex++;

    } // end while
    fclose(file);

    /* Iterate through linked list */
    current = head;
    while (current != NULL) {
        pid = fork();

        /* Start timer */
        clock_gettime(CLOCK_MONOTONIC, &start);
        current->starttime = start.tv_sec;

        if (pid < 0) {
            fprintf(stderr, "fork failed");
            exit(1);
        }

        // fork successful:
        if (pid == 0) { // child process
            // create and open .out and .err files for each process
            sprintf(outFileName, "%d.out", (int)getpid());
            sprintf(errFileName, "%d.err", (int)getpid());
            int out_fd = open(outFileName, O_CREAT|O_APPEND|O_RDWR, 0777);
            int err_fd = open(errFileName, O_CREAT|O_APPEND|O_RDWR, 0777);

            // redirect output
            dup2(out_fd, STDOUT_FILENO); // redirect stdout (1) to out_fd
            dup2(err_fd, STDERR_FILENO); // redirect stderr (2) to err_fdc

            // write Starting process
            fprintf(stdout, "Starting command %d: child %d pid of parent %d\n",
                    current->index, (int)getpid(), (int)getppid());
            fflush(stdout);

            // execute command
            char *myargs[20];
            int index = 0;
            while (*(current->command[index]) != '\0') {
                myargs[index] = current->command[index];
                index += 1;
            }
            myargs[index] = NULL;
            execvp(myargs[0], myargs);

            // print error if execvp fails
            perror(myargs[0]);
            exit(2);
        } else { // parent process
            current->PID = pid;
        }

        // move on to next node in linked list
        current = GetNextCommand(current);

    } // end while loop

    // parent process will wait until any child is complete
    while ((pid = wait(&status)) >= 0) {
        // get the finished node
        CommandNode *finished = FindCommand(head, pid);

        // calculate elapsed runtime
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = finish.tv_sec - (finished->starttime);

        // write Finished process
        sprintf(outFileName, "%d.out", pid);
        sprintf(errFileName, "%d.err", pid);
        int out_fd = open(outFileName, O_CREAT|O_APPEND|O_RDWR, 0777);
        int err_fd = open(errFileName, O_CREAT|O_APPEND|O_RDWR, 0777);
        // redirect output
        dup2(out_fd, STDOUT_FILENO); // redirect stdout (1) to out_fd
        dup2(err_fd, STDERR_FILENO); // redirect stderr (2) to err_fdc

        // this should get printed in .out file
        fprintf(stdout, "Finished child %d pid of parent %d\n", pid, (int)getpid());
        fflush(stdout);
        
        fprintf(stdout, "Finished at %ld, runtime duration %f\n", finish.tv_sec, elapsed);
        fflush(stdout);

        close(out_fd);
        close(err_fd);


        if (WIFEXITED(status)) {
            fprintf(stderr, "Child %d terminated normally with exit code: %d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Child %d terminated abnormally with signal number: %d\n",
                    pid, WTERMSIG(status));
        }

        if (elapsed < 2) {
            // print Spawning too fast in .err file
            fprintf(stderr, "Spawning too fast\n");
        }   

        // otherwise elapsed time > 2, re-execute
        if (elapsed > 2) { 
            // restart the process
            pid = fork();

            // restart the timer
            clock_gettime(CLOCK_MONOTONIC, &start);
            finished->starttime = start.tv_sec;

            if (pid < 0) {
                fprintf(stderr, "fork failed");
                exit(1);
            }

            // fork successful:
            if (pid == 0) { // child process

                sprintf(outFileName, "%d.out", (int)getpid());
                sprintf(errFileName, "%d.err", (int)getpid());
                int out_fd = open(outFileName, O_CREAT|O_APPEND|O_RDWR, 0777);
                int err_fd = open(errFileName, O_CREAT|O_APPEND|O_RDWR, 0777);

                // redirect output
                dup2(out_fd, STDOUT_FILENO); // redirect stdout (1) to out_fd
                dup2(err_fd, STDERR_FILENO); // redirect stderr (2) to err_fdc

                fprintf(stdout, "RESTARTING\n");

                // write Starting process
                fprintf(stdout, "Starting command %d: child %d pid of parent %d\n",
                        finished->index, (int)getpid(), (int)getppid());
                fflush(stdout);

                // execute command
                char *myargs[20];
                int index = 0;
                while (*(finished->command[index]) != '\0') {
                    myargs[index] = finished->command[index];
                    index += 1;
                }
                myargs[index] = NULL;

                // execute commands
                execvp(myargs[0], myargs);

                // print error if execvp fails
                perror(myargs[0]);
                exit(2);
            } else { // parent process
                finished->PID = pid;
            }

        } 

    }
}
