//
// Created by diana on 24/12/2019.
//

#include "problem_3_13.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void findExit(matrix *labyrinth, point *currentTile);

bool tileIsAtEdge(matrix *labyrinth, point currentTile);

void foundExit(matrix *labyrinth);

bool validTilesExist(matrix *labyrinth, point currentTile);

point getNewValidTile(matrix *labyrinth, point currentTile);

void finishedSearching();

point getPreviousTile(matrix *labyrinth, point currentTile);

void setTile(matrix *labyrinth, point tile, int value);

void p_3_13() {
    //region declarations
    FILE *inputFile = fopen("labyrinth.txt", "r");
    matrix labyrinth;
    point startingTile;
    //endregion
    //region reading labyrinth
    fscanf(inputFile, "%d", &labyrinth.nrOfRows);
    fscanf(inputFile, "%d", &labyrinth.nrOfCols);
    labyrinth.matrix = (int**) malloc(labyrinth.nrOfRows* sizeof(int*));
    for (int i = 0; i < labyrinth.nrOfRows; ++i) {
        labyrinth.matrix[i] = (int*) malloc(labyrinth.nrOfCols* sizeof(int));
    }
    for (int row = 0; row < labyrinth.nrOfRows; ++row) {
        for (int col = 0; col < labyrinth.nrOfCols; ++col) {
            fscanf(inputFile, "%d", &labyrinth.matrix[row][col]);
        }
    }
    //endregion
    //region print labyrinth
    foundExit(&labyrinth);
    printf("Labyrinth is an %d x %d matrix stored int file \"labyrinth.txt\"\n", labyrinth.nrOfRows, labyrinth.nrOfCols);
    setbuf(stdout, 0);
    //endregion
    //region choose starting point
    printf("Choose starting point row:\n");
    scanf("%d", &startingTile.row);
    printf("Choose starting point column:\n");
    scanf("%d", &startingTile.col);
    if (labyrinth.matrix[startingTile.row][startingTile.col] == 0) {
        printf("Starting point is a wall, no exits available.\n");
        return;
    }
    labyrinth.matrix[startingTile.row][startingTile.col] = STARTING_TILE;
    //endregion

    findExit(&labyrinth, &startingTile);
}

void findExit(matrix *labyrinth, point *currentTile) {
    if (tileIsAtEdge(labyrinth, *currentTile)) {
        setTile(labyrinth, *currentTile, TRAVERSED_TILE);
        foundExit(labyrinth);
    }
    if (validTilesExist(labyrinth, *currentTile)) {
        if (labyrinth->matrix[currentTile->row][currentTile->col] == STARTING_TILE || labyrinth->matrix[currentTile->row][currentTile->col] == STARTING_TRAVERSED_TILE) setTile(labyrinth, *currentTile, STARTING_TRAVERSED_TILE);
        else setTile(labyrinth, *currentTile, TRAVERSED_TILE);
        *currentTile = getNewValidTile(labyrinth, *currentTile);
        findExit(labyrinth, currentTile);
    } else {
        if ((labyrinth->matrix[currentTile->row][currentTile->col] == STARTING_TILE) || labyrinth->matrix[currentTile->row][currentTile->col] == STARTING_TRAVERSED_TILE) {
            finishedSearching();
            return;
        } else {
            setTile(labyrinth, *currentTile, WALL);
            *currentTile = getPreviousTile(labyrinth, *currentTile);
            findExit(labyrinth, currentTile);
        }
    }
}

void setTile(matrix *labyrinth, point tile, int value) {
    labyrinth->matrix[tile.row][tile.col] = value;
}

point getPreviousTile(matrix *labyrinth, point currentTile) {
    point previousTile;
    if (currentTile.col - 1 >= 0)
        if (labyrinth->matrix[currentTile.row][currentTile.col - 1] == TRAVERSED_TILE || labyrinth->matrix[currentTile.row][currentTile.col - 1] == STARTING_TRAVERSED_TILE) {
            previousTile.row = currentTile.row;
            previousTile.col = currentTile.col-1;
            return previousTile;
        }
    if (currentTile.col + 1 <= labyrinth->nrOfCols - 1)
        if (labyrinth->matrix[currentTile.row][currentTile.col + 1] == TRAVERSED_TILE || labyrinth->matrix[currentTile.row][currentTile.col + 1] == STARTING_TRAVERSED_TILE) {
            previousTile.row = currentTile.row;
            previousTile.col = currentTile.col+1;
            return previousTile;
        }
    if (currentTile.row - 1 >= 0)
        if (labyrinth->matrix[currentTile.row - 1][currentTile.col] == TRAVERSED_TILE || labyrinth->matrix[currentTile.row - 1][currentTile.col] == STARTING_TRAVERSED_TILE) {
            previousTile.row = currentTile.row-1;
            previousTile.col = currentTile.col;
            return previousTile;
        }
    if (currentTile.row + 1 >= 0)
        if (labyrinth->matrix[currentTile.row + 1][currentTile.col] == TRAVERSED_TILE || labyrinth->matrix[currentTile.row + 1][currentTile.col] == STARTING_TRAVERSED_TILE) {
            previousTile.row = currentTile.row+1;
            previousTile.col = currentTile.col;
            return previousTile;
        }
    return previousTile;
}

void finishedSearching() {
    printf("There are no more possible ways to exit the labyrinth.\n");
}

point getNewValidTile(matrix *labyrinth, point currentTile) {
    point newTile;
    if (currentTile.col - 1 >= 0)
        if (labyrinth->matrix[currentTile.row][currentTile.col - 1] == WALKABLE_TILE) {
            newTile.row = currentTile.row;
            newTile.col = currentTile.col-1;
            return newTile;
        }
    if (currentTile.col + 1 <= labyrinth->nrOfCols - 1)
        if (labyrinth->matrix[currentTile.row][currentTile.col + 1] == WALKABLE_TILE) {
            newTile.row = currentTile.row;
            newTile.col = currentTile.col+1;
            return newTile;
        }
    if (currentTile.row - 1 >= 0)
        if (labyrinth->matrix[currentTile.row - 1][currentTile.col] == WALKABLE_TILE) {
            newTile.row = currentTile.row-1;
            newTile.col = currentTile.col;
            return newTile;
        }
    if (currentTile.row + 1 >= 0)
        if (labyrinth->matrix[currentTile.row + 1][currentTile.col] == WALKABLE_TILE) {
            newTile.row = currentTile.row+1;
            newTile.col = currentTile.col;
            return newTile;
        }
}

bool validTilesExist(matrix *labyrinth, point currentTile) {
    if (currentTile.col - 1 >= 0)
        if (labyrinth->matrix[currentTile.row][currentTile.col - 1] == WALKABLE_TILE)
            return true;
    if (currentTile.col + 1 <= labyrinth->nrOfCols - 1)
        if (labyrinth->matrix[currentTile.row][currentTile.col + 1] == WALKABLE_TILE)
            return true;
    if (currentTile.row - 1 >= 0)
        if (labyrinth->matrix[currentTile.row - 1][currentTile.col] == WALKABLE_TILE)
            return true;
    if (currentTile.row + 1 <= labyrinth->nrOfRows-1)
        if (labyrinth->matrix[currentTile.row + 1][currentTile.col] == WALKABLE_TILE)
            return true;
    return false;
}

void foundExit(matrix *labyrinth) {
    printf("Path to exit to the labyrinth found:\n");
    for (int row= 0; row < labyrinth->nrOfRows; ++row) {
        for (int col = 0; col < labyrinth->nrOfCols; ++col) {
            printf("%d", labyrinth->matrix[row][col]);
        }
        printf("\n");
    }
}

bool tileIsAtEdge(matrix *labyrinth, point currentTile) {
    if (labyrinth->matrix[currentTile.row][currentTile.col] != TRAVERSED_TILE && labyrinth->matrix[currentTile.row][currentTile.col] != STARTING_TRAVERSED_TILE) {
        if ((currentTile.row == 0) || (currentTile.row == labyrinth->nrOfRows - 1))
            return true;
        if ((currentTile.col == 0) || (currentTile.col == labyrinth->nrOfCols - 1))
            return true;
    }
    return false;
}
