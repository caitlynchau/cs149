// Caitlyn Chau
// CS 149 Sec 1

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 600

/* function prototypes */
void printMin(double arr[], unsigned int n);
void printMax(double arr[], unsigned int n);

int main(int argc, char *argv[]) {
    FILE *file;
    unsigned int lineCount = 0;
    double data[MAX_NUM] = {0};

    if (argc < 1) exit(1); 
    else if (argc == 1) { // only one argument
        puts("No file specified");
        exit(0);
    } else { 
        // more than 1 argument, if more than 2 arguments, rest are ignored
        file = fopen(argv[1], "r"); // argv[1] is path
        if (file == NULL){
            printf("range: cannot open file\n");
            exit(1);
        }

        // read in all lines from file and increment lineCount
        fscanf(file, "%lf", &data[lineCount++]);
        while (!feof(file)){
            fscanf(file, "%lf", &data[lineCount++]);
        }
        fclose(file); // finished reading file

        lineCount--;
        if (lineCount == 0){
            printf("Empty file\n");
            exit(0);
        }

        // print minimum and maximum
        printMin(data, lineCount);
        printMax(data, lineCount);
        exit(0); // success
    }
}

/* print minimum element in array */
void printMin(double arr[], unsigned int n) {
    double min = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] < min){
            min = arr[i];
        }
    }
    printf("min: %.4lf\n", min);
}

/* print maximum element in array */
void printMax(double arr[], unsigned int n) {
    double max = arr[0];
    for (int i = 1; i < n; i++){
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    printf("max: %.4lf\n", max);
}