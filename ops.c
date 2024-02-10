#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LINE 1000 //made to set the line of command limit to 1000 characters. | Referenced from StacksOverflow

int main(int argc, char *argv[]){
    //argc is for arg count and argv
    // is the argument vector containing the arguments including the program name


    //This block checks for errors i.e. it checks if there are enough arguments or not.
    //If there are not enough arguments it gives an error message
    // giving the syntax of the argument to be inputted in the command line along with the program name(argv[0])
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <operator> <operand>\n", argv[0]);
        return 1;
    }

    char *operator = argv[1]; //I chose char because the operator will be with second argument after program name.
    double p = atof(argv[2]);//I chose double because it is mentioned that the numbers could be decimals too.


    char line[LINE];

    //while loop also helps to keep reading data line-by-line from the textfile
    while (fgets(line, sizeof(line), stdin) != NULL) {
        double q = atof(line);

        // Perform operations based on the operator
        if (strcmp(operator, "+") == 0) {
            printf("%d\n", q + p);
        } else if (strcmp(operator, "-") == 0) {
            printf("%d\n", q - p);
        } else if (strcmp(operator, "x") == 0) {
            printf("%d\n", q * p);
        } else if (strcmp(operator, "/") == 0) {
            if (p == 0) {
                fprintf(stderr, "Error: You are dividing by zero\n");
                return 1;
            }
            printf("%lf\n", q / p);
        } else if (strcmp(operator, "%") == 0) {
            if (p == 0) {
                fprintf(stderr, "Error: You are dividing by zero\n");
                return 1;
            }
            printf("%lf\n", fmod(q, p));
        } else if (strcmp(operator, "==") == 0) {
            if(q == p){
                printf("%d\n", q);
            }
        } else if (strcmp(operator, "!=") == 0) {
            if(q != p){
                printf("%d\n", q);
            }
        } else if (strcmp(operator, "le") == 0) {
            if(q <= p){
                printf("%d\n", q);
            }

        } else if (strcmp(operator, "lt") == 0) {
            if(q < p){
                printf("%d\n", q);
            }
        } else if (strcmp(operator, "ge") == 0) {
            if(q >= p){
                printf("%d\n", q);
            }
        } else if (strcmp(operator, "gt") == 0) {
            if(q > p){
                printf("%d\n", q);
            }

        } else {
            fprintf(stderr, "Your operator is not valid\n");
            return 1;
        }
    }

    return 0;


}