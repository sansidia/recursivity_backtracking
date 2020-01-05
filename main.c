#include <stdio.h>
#include "problem_3_2.h"
#include "problem_3_13.h"
#include "problem 3_14.h"

int main() {
    setbuf(stdout, 0);
    printf("Select problem number:\n");
    printf("a) Problem 3.2\n"
           "b) Problem 3.13\n"
           "c) Problem 3.14\n");
    int choice = getchar();
    choice = choice-'a';
    switch (choice) {
        case 0: {
            p_3_2();
            break;
        }
        case 1: {
            p_3_13();
            break;
        }
        case 2: {
            p_3_14();
            break;
        }
    }
    return 0;
}