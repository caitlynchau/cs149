// Caitlyn Chau
// CS 149 Fall 20
// Assignment 3 Part 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
    FILE * file;
    char * command = NULL;
    size_t len = 0;
    ssize_t read;
    char outFileName[10];
    char errFileName[10];
    int pid, status;
    int lineCount = 1;

    file = fopen("cmdfile", "r");
    if (file == NULL) {
        fprintf(stderr, "proc_manager: cannot open file\n");
        exit(1);
    }

    while ((read = getline(&command, &len, file)) != -1) {
        // process line for command and arguments
        command[strlen(command) -1] = 0; // replace newline with null
        char args[20][20];
        int j = 0, ctr = 0;
        // split string by space
        for (int i = 0; i <= (strlen(command)); i++){
            if (command[i] == ' ' || command[i] == '\0') {
                args[ctr][j] = '\0';
                ctr++; // next word
                j = 0; // reset initial index to 0
            } else {
                args[ctr][j] = command[i];
                j++;
            }
        }

        pid = fork();
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
                    lineCount, (int)getpid(), (int)getppid());
            fflush(stdout);

            // execute command
            char *myargs[20];
            int index = 0;
            while (ctr < 20 && *(args[index]) != '\0') {
                myargs[index] = args[index];
                index += 1;
            }
            myargs[index] = NULL;
            execvp(myargs[0], myargs);

            // print error if execvp fails
            perror(myargs[0]);
            exit(2);
        } else { // parent process
            lineCount += 1;
        }
    }

    // parent process will wait until any child is complete
    while ((pid = wait(&status)) >= 0) {
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

        if (WIFEXITED(status)) {
            fprintf(stderr, "Child %d terminated normally with exit code: %d\n",
                    pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Child %d terminated abnormally with signal number: %d\n",
                    pid, WTERMSIG(status));
        }

        close(out_fd);
        close(err_fd);
    }
}