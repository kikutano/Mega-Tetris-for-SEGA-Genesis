#include "tetris_piece.h"
#include "tetris_game_settings.h"

int leftLimit  = 0;
int rightLimit = 9;
int downLimit  = 23;

bool isTetrisPieceOnLeftLimit(struct TetrisPiece *tetrisPiece) {
    return 
        tetrisPiece->block0->column == leftLimit 
        || tetrisPiece->block1->column == leftLimit 
        || tetrisPiece->block2->column == leftLimit
        || tetrisPiece->block3->column == leftLimit;       
}

bool isTetrisPieceOnRightLimit(struct TetrisPiece *tetrisPiece) {
    return 
        tetrisPiece->block0->column == rightLimit 
        || tetrisPiece->block1->column == rightLimit 
        || tetrisPiece->block2->column == rightLimit
        || tetrisPiece->block3->column == rightLimit;       
}

bool isTetrisPieceTouchingAnotherPieceOnLeft(
    bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS], struct TetrisPiece *tetrisPiece) {
        return 
            tetrisMatrix
                [tetrisPiece->block0->column - 1]
                [tetrisPiece->block0->row]
            || 
            tetrisMatrix
                [tetrisPiece->block1->column - 1]
                [tetrisPiece->block1->row]
            || 
            tetrisMatrix
                [tetrisPiece->block2->column - 1]
                [tetrisPiece->block2->row]
            || 
            tetrisMatrix
                [tetrisPiece->block3->column - 1]
                [tetrisPiece->block3->row]; 
}

bool isTetrisPieceTouchingAnotherPieceOnRight(
    bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS], struct TetrisPiece *tetrisPiece) {
        return 
            tetrisMatrix
                [tetrisPiece->block0->column + 1]
                [tetrisPiece->block0->row]
            || 
            tetrisMatrix
                [tetrisPiece->block1->column + 1]
                [tetrisPiece->block1->row]
            || 
            tetrisMatrix
                [tetrisPiece->block2->column + 1]
                [tetrisPiece->block2->row]
            || 
            tetrisMatrix
                [tetrisPiece->block3->column + 1]
                [tetrisPiece->block3->row]; 
}

bool isTetrisPieceTouchingAnotherPieceOnBottom(
    bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS], struct TetrisPiece *tetrisPiece) {
    return 
        tetrisMatrix
            [tetrisPiece->block0->column]
            [tetrisPiece->block0->row + 1]
        || 
        tetrisMatrix
            [tetrisPiece->block1->column]
            [tetrisPiece->block1->row + 1]
        || 
        tetrisMatrix
            [tetrisPiece->block2->column]
            [tetrisPiece->block2->row + 1]
        || 
        tetrisMatrix
            [tetrisPiece->block3->column]
            [tetrisPiece->block3->row + 1];
}

bool isTetrisPieceOnBottom(struct TetrisPiece *tetrisPiece) {
    return
        (tetrisPiece->block0->row) == downLimit 
        || (tetrisPiece->block1->row) == downLimit 
        || (tetrisPiece->block2->row) == downLimit 
        || (tetrisPiece->block3->row) == downLimit;
}

bool isRowLineCompleted(bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS], int row) {
    for (int column = 0; column < GRID_COLUMNS; ++column) {
        if (!tetrisMatrix[column][row]) {
            return FALSE;
        }
    }

    return TRUE;
}

bool isRowAlreadyCleared(int rowsCleared[ROWS_MAX_CLEARED], int value) {
    for (int i = 0; i < ROWS_MAX_CLEARED; ++i) {
        if (rowsCleared[i] == value) {
            return TRUE;
        }
    }

    return FALSE;
}

void orderClearedRowsArray(int rowsCleared[ROWS_MAX_CLEARED]) {
    for (int i = 0; i < ROWS_MAX_CLEARED; ++i) {
        for (int j = i + 1; j < ROWS_MAX_CLEARED; ++j) {
            if (rowsCleared[i] > rowsCleared[j]) {
                int a =  rowsCleared[i];
                rowsCleared[i] = rowsCleared[j];
                rowsCleared[j] = a;
            }
        }
    }
}

void setCompletedLinesCount(
    bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS], 
    int rowsCleared[ROWS_MAX_CLEARED], 
    struct TetrisPiece *tetrisPiece) {
    
    int completedCount = 0;
    if (isRowLineCompleted(tetrisMatrix, tetrisPiece->block0->row)) {
        rowsCleared[completedCount] = tetrisPiece->block0->row;
        ++completedCount;
    }

    if (!isRowAlreadyCleared(rowsCleared, tetrisPiece->block1->row) 
        && isRowLineCompleted(tetrisMatrix, tetrisPiece->block1->row)) {
        rowsCleared[completedCount] = tetrisPiece->block1->row;
        ++completedCount;
    }

    if (!isRowAlreadyCleared(rowsCleared, tetrisPiece->block2->row) 
        && isRowLineCompleted(tetrisMatrix, tetrisPiece->block2->row)) {
        rowsCleared[completedCount] = tetrisPiece->block2->row;
        ++completedCount;
    }

    if (!isRowAlreadyCleared(rowsCleared, tetrisPiece->block3->row) 
        && isRowLineCompleted(tetrisMatrix, tetrisPiece->block3->row)) {
        rowsCleared[completedCount] = tetrisPiece->block3->row;
        ++completedCount;
    }

    //orderClearedRowsArray(rowsCleared);
}