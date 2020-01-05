//
// Created by diana on 04/01/2020.
//

#include "problem 3_14.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int rowModifier[] = {2, 1, -1, -2, -2, -1,  1,  2};
int colModifier[] = {1, 2,  2,  1, -1, -2, -2, -1};

void findPath(board *pBoard, point pPoint, int index);

void placeKnight(board *pBoard, point pPoint, int index);

point setPoint(int row, int col);

bool validatePoint(point p, board *pBoard);

void printBoard(board *pBoard);

void clearKnight(board *pBoard, point pPoint);

void p_3_14() {


    board mBoard;
    //region declare board
    printf("What is the size of the chess board?\n");
    scanf("%d", &mBoard.size);
    for (int i = 0; i < mBoard.size; ++i) {
        mBoard.matrix[i] = (int*) malloc(mBoard.size* sizeof(int));
        for (int j = 0; j < mBoard.size; ++j) {
            mBoard.matrix[i][j] = 0;
        }
    }
    //endregion

    point currentPoint;
    currentPoint.row = 0;
    currentPoint.col = 0;
    int index = 1;
    findPath(&mBoard, currentPoint, index);

    printf("There are no more ways to make a path\n");
}

void findPath(board *pBoard, point pPoint, int index) {
    placeKnight(pBoard, pPoint, index);
    if (index == (pBoard->size* pBoard->size)) {
        printBoard(pBoard);
        clearKnight(pBoard, pPoint);
        return;
    }

    for (int n = 0; n < NR_OF_MOVEMENTS; ++n) {
        point newPoint = setPoint(pPoint.row + rowModifier[n], pPoint.col + colModifier[n]);
        if (validatePoint(newPoint, pBoard))
            findPath(pBoard, newPoint, index+1);
    }

    clearKnight(pBoard, pPoint);
}

void clearKnight(board *pBoard, point pPoint) {
    pBoard->matrix[pPoint.row][pPoint.col] = 0;
}

void printBoard(board *pBoard) {
    for (int i = 0; i < pBoard->size; ++i) {
        for (int j = 0; j < pBoard->size; ++j) {
            printf("%d ", pBoard->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

point setPoint(int row, int col) {
    point p;
    p.row = row;
    p.col = col;
    return p;
}

bool validatePoint(point p, board *pBoard) {
    if (p.row >= pBoard->size) return false;
    if (p.col >= pBoard->size) return false;
    if (p.col < 0) return false;
    if (p.row < 0) return false;
    if (pBoard->matrix[p.row][p.col] != 0) return false;
    return true;
}

void placeKnight(board *pBoard, point pPoint, int index) {
    pBoard->matrix[pPoint.row][pPoint.col] = index;
}
