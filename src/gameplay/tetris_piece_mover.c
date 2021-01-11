#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_piece_provider.c"
#include "tetris_piece_collision_checker.c"
#include "tetris_game_settings.h"
#include "tetris_random_piece_provider.c"

bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS];
u16 rowsCleared[ROWS_MAX_CLEARED];
u16 rowStartPoint = 0;
u16 columnStartPoint = 5;
//struct TetrisPiece *nextTetrisPiece;
struct TetrisPiece *currentTetrisPiece;

void updateMatrixSlot(u16 column, u16 row, bool value) {
    tetrisMatrix[column][row] = value;
}

u16 getNextRandomTetrisPiece() {
    return getRandomTetrisPieceUsingNesAlgorithm(currentTetrisPiece);
}

void putNextPieceOnTop() {
    u16 nextTetriPieceType = getNextRandomTetrisPiece();

    if (nextTetriPieceType == TETRISPIECE_I) {
        currentTetrisPiece 
            = createTetrisPiece_I(columnStartPoint, rowStartPoint, 0);
    }
    else if (nextTetriPieceType == TETRISPIECE_O) {
        currentTetrisPiece 
            = createTetrisPiece_O(columnStartPoint, rowStartPoint, 0);
    } 
    else if (nextTetriPieceType == TETRISPIECE_T) {
        currentTetrisPiece 
            = createTetrisPiece_T(columnStartPoint, rowStartPoint, 0);
    }
    else if (nextTetriPieceType == TETRISPIECE_J) {
        currentTetrisPiece 
            = createTetrisPiece_J(columnStartPoint, rowStartPoint, 0);
    }
    else if (nextTetriPieceType == TETRISPIECE_L) {
        currentTetrisPiece 
            = createTetrisPiece_L(columnStartPoint, rowStartPoint, 0);
    }
    else if (nextTetriPieceType == TETRISPIECE_S) {
        currentTetrisPiece 
            = createTetrisPiece_S(columnStartPoint, rowStartPoint, 0);
    }
    else if (nextTetriPieceType == TETRISPIECE_Z) {
        currentTetrisPiece 
            = createTetrisPiece_Z(columnStartPoint, rowStartPoint, 0);
    }

    drawTetrisPiece(currentTetrisPiece);
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

void updateTetrisPiecePosition() {
    deleteTetrisPiece(currentTetrisPiece);
    if (currentTetrisPiece->Type == TETRISPIECE_I) {
        currentTetrisPiece 
            = createTetrisPiece_I(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->Type == TETRISPIECE_O) {
        currentTetrisPiece 
            = createTetrisPiece_O(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    } 
    else if (currentTetrisPiece->Type == TETRISPIECE_T) {
        currentTetrisPiece 
            = createTetrisPiece_T(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->Type == TETRISPIECE_J) {
        currentTetrisPiece 
            = createTetrisPiece_J(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->Type == TETRISPIECE_L) {
        currentTetrisPiece 
            = createTetrisPiece_L(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->Type == TETRISPIECE_S) {
        currentTetrisPiece 
            = createTetrisPiece_S(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }
    else if (currentTetrisPiece->Type == TETRISPIECE_Z) {
        currentTetrisPiece 
            = createTetrisPiece_Z(
                currentTetrisPiece->pivotPosX, 
                currentTetrisPiece->pivotPosY, 
                currentTetrisPiece->rotationCount);
    }

    drawTetrisPiece(currentTetrisPiece);
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

void moveDownTetrisRow(u16 row, u16 offset) {
    deleteSpritesOnRow(row);

    for (u16 column = 0; column < GRID_COLUMNS; ++column) {    
        if (row + offset < GRID_ROWS) {
            if (tetrisMatrix[column][row]) {
                drawTetrisTileOnGrid(column, row + offset);
                tetrisMatrix[column][row + offset] = TRUE;
            }
            else {
                tetrisMatrix[column][row + offset] = FALSE;
            }

            tetrisMatrix[column][row] = FALSE;
        }
    }
}

u16 getCompletedRowLinesCount() {
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
    u16 rowCount = 0;
    u16 startPoint = 0;
    for (u16 x = 0; x < ROWS_MAX_CLEARED; ++x) {
        if (rowsCleared[x] != 0) {
            deleteSpritesOnRow(rowsCleared[x]);
            ++rowCount;
            startPoint = rowsCleared[x];
        }
    }

    startPoint -= rowCount;

    for (u16 i = startPoint; i > 0; --i) {
        moveDownTetrisRow(i, rowCount);
    }

    rowsCleared[0] = 0;
    rowsCleared[1] = 0;
    rowsCleared[2] = 0;
    rowsCleared[3] = 0;
}