//
// Created by diana on 24/12/2019.
//

#ifndef RECURSIVITY_BACKTRACKING_PROBLEM_3_13_H
#define RECURSIVITY_BACKTRACKING_PROBLEM_3_13_H
enum squares {WALL, WALKABLE_TILE, TRAVERSED_TILE, STARTING_TILE, STARTING_TRAVERSED_TILE};

typedef struct _matrix {
    int** matrix;
    int nrOfRows, nrOfCols;
} matrix;

typedef struct _point {
    int row, col;
}point;

void p_3_13();

#endif //RECURSIVITY_BACKTRACKING_PROBLEM_3_13_H
