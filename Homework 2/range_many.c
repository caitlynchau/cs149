#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <float.h>
#include <sys/wait.h>

/* function prototypes */
void readFile(FILE * file, double * min, double * max);

int main(int argc, char *argv[]) {
    int fd[2]; //pipe file descriptor
    double buf[2]; // buffer to hold min and max
    pid_t pid;
    double minimum = FLT_MAX;
    double maximum = FLT_MIN;

    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe Failed");
        exit(1);
    }

    if (argc <= 1) {
        printf("No files specified");
        exit(0); // no files specified
    }
    printf("parent id: %d\n", (int)getpid());
    // process each file
    for (int i = 1; i < argc; i++) {
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Fork failed");
            exit(1);
        } else if (pid == 0) { // child process
            FILE *file = fopen(argv[i], "r"); // argv[i] is path
            if (file == NULL) {
                printf("Child process %d could not open file\n", (int) getpid());
            } else {
                double min = FLT_MAX, max = FLT_MIN; // initialize local min and max
                readFile(file, &min, &max);
                fclose(file);
                buf[0] = min;
                buf[1] = max;

                write(fd[1], buf, sizeof(buf)); // write to buffer
                //printf("Child %d wrote: min: %lf max %lf\n", (int) getpid(), buf[0], buf[1]);
            }
            exit(0); // child process ends
        }
    } // end for loop

    // parent process will wait until any child is complete
    while (wait(NULL) > 0) {
        // read end of pipe
        if (read(fd[0], buf, sizeof(buf)) < 0) {
            perror("Read failed");
            exit(1);
        }
        // update global minimum and maximum if necessary
        if (buf[0] < minimum) minimum = buf[0];
        if (buf[1] > maximum) maximum = buf[1];
    } // end while loop

    printf("min: %lf\n", minimum);
    printf("max: %lf\n", maximum);

    return 0;
}

/* read file and extract the minimum and maximum */
void readFile(FILE * file, double * min, double * max) {
    double num;
    // read in input from file until eof encountered
    fscanf(file, "%lf", &num);
    while (!feof(file)){
        // update local min and max
        if (num < *min) *min = num;
        if (num > *max) *max = num;
        fscanf(file, "%lf", &num);
    }
}
