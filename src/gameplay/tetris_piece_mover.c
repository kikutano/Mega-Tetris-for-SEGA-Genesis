#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_piece_provider.c"
#include "tetris_piece_collision_checker.c"
#include "tetris_game_settings.h"

bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS];
int rowsCleared[ROWS_MAX_CLEARED];
struct TetrisPiece *currentTetrisPiece;

void updateMatrixSlot(int column, int row, bool value) {
    tetrisMatrix[column][row] = value;
}

void putNextPieceOnTop() {
    currentTetrisPiece = createTetrisPiece_O(5, 0, 0);
}

bool isCurrentTetrisPieceOnBottom() {
    return isTetrisPieceOnBottom(currentTetrisPiece);
} 

bool isCurrentTetrisPieceTouchingAnotherPieceOnBottom() {
    return isTetrisPieceTouchingAnotherPieceOnBottom(tetrisMatrix, currentTetrisPiece);
}

void occupyMatrixSlotForTetrisPiece(struct TetrisPiece *tetrisPiece) {
    updateMatrixSlot(tetrisPiece->block0->column, tetrisPiece->block0->row, TRUE);
    updateMatrixSlot(tetrisPiece->block1->column, tetrisPiece->block1->row, TRUE);
    updateMatrixSlot(tetrisPiece->block2->column, tetrisPiece->block2->row, TRUE);
    updateMatrixSlot(tetrisPiece->block3->column, tetrisPiece->block3->row, TRUE);
}

void lockTetrisPieceOnBackground() {
    occupyMatrixSlotForTetrisPiece(currentTetrisPiece);
}

void moveDownRowLine(int row) {
    for (int column = 0; column < GRID_COLUMNS; ++column) {
        if (tetrisMatrix[column][row]) {
            tetrisMatrix[column][row] = FALSE;
            deleteTetrisTileOnGrid(column, row);
            drawTetrisTileOnGrid(column, row + 1);
            tetrisMatrix[column][row + 1] = TRUE;
        }
    }
}

void updateTetrisPiecePosition() {
    deleteTetrisPiece(currentTetrisPiece);
    currentTetrisPiece 
        = createTetrisPiece_O(
            currentTetrisPiece->pivotPosX, 
            currentTetrisPiece->pivotPosY, 
            currentTetrisPiece->rotationCount);
}

void rotateAntiClockwiseCurrentTetrisPiece() {
    currentTetrisPiece->rotationCount++;

    if (currentTetrisPiece->rotationCount >= 4) {
        currentTetrisPiece->rotationCount = 0;
    }

    updateTetrisPiecePosition();
}

void rotateClockwiseCurrentTetrisPiece() {
    currentTetrisPiece->rotationCount--;

    if (currentTetrisPiece->rotationCount <= -1) {
        currentTetrisPiece->rotationCount = 3;
    }

    updateTetrisPiecePosition();
}

void moveCurrentTetrisPieceDown() {
    currentTetrisPiece->pivotPosY++;
    updateTetrisPiecePosition();
}

void moveCurrentTetrisPieceLeft() {
    if (!isTetrisPieceOnLeftLimit(currentTetrisPiece)
        && !isTetrisPieceTouchingAnotherPieceOnLeft(tetrisMatrix, currentTetrisPiece)) {
        currentTetrisPiece->pivotPosX--;
        updateTetrisPiecePosition();
    }
}

void moveCurrentTetrisPieceRight() {
    if (!isTetrisPieceOnRightLimit(currentTetrisPiece)
        && !isTetrisPieceTouchingAnotherPieceOnRight(tetrisMatrix, currentTetrisPiece)) {
        currentTetrisPiece->pivotPosX++;
        updateTetrisPiecePosition();
    }
}

void moveTetrisRowOnBottom(int row, int offset) {
    for (int column = 0; column < GRID_COLUMNS; ++column) {
        if (tetrisMatrix[column][row]) {
            drawTetrisTileOnGrid(column, row + offset);
            tetrisMatrix[column][row + offset] = TRUE;
            deleteTetrisTileOnGrid(column, row);
        }
    }
}

int getCompletedRowLinesCount() {
    setCompletedLinesCount(tetrisMatrix, rowsCleared, currentTetrisPiece);

    if (rowsCleared[3] != 0) {
        return 4;
    } 
    
    if (rowsCleared[2] != 0) {
        return 3;
    } 

    if (rowsCleared[1] != 0) {
        return 2;
    } 

    if (rowsCleared[0] != 0) {
        return 1;
    } 

    return 0;
}

void clearRows() {
    int rowCount = 0;
    for (int x = 0; x < ROWS_MAX_CLEARED; ++x) {
        if (rowsCleared[x] != 0) {
            deleteSpritesOnRow(rowsCleared[x]);
            ++rowCount;
        }
    }
    
    //ordinare la lista rowsCleared e farlo partire dal più piccolo
    int startPoint = GRID_ROWS - rowCount - 1;

    for (int i = startPoint; i > 0; --i) {
        moveTetrisRowOnBottom(i, rowCount);
    }
    
    rowsCleared[0] = 0;
    rowsCleared[1] = 0;
    rowsCleared[2] = 0;
    rowsCleared[3] = 0;
}