//
// Created by diana on 24/12/2019.
//

#include "problem_3_2.h"
#include <stdio.h>

void recursiveSolution();

int hermitePolynomial(int rank, int x);

void p_3_2() {
    recursiveSolution();
}

void recursiveSolution() {
    int termNumber, x;
    printf("What is x?\n");
    scanf("%d", &x);
    printf("What term of the Hermite polynomial do you want to calculate?\n");
    scanf("%d", &termNumber);
    printf ("The term of rank %d is: %d", termNumber, hermitePolynomial(termNumber, x));
}

int hermitePolynomial(int rank, int x) {
    if (rank == 0) return 1;
    if (rank == 1) return 2 * x;
    return (2 * rank * hermitePolynomial(rank - 1, x) - 2 * (rank - 1) * hermitePolynomial(rank-2, x));
}
