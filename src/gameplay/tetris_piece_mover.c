#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_piece_provider.c"
#include "tetris_piece_collision_checker.c"
#include "tetris_game_settings.h"

bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS];
struct TetrisPiece *currentTetrisPiece;

void updateMatrixSlot(int column, int row, bool value) {
    tetrisMatrix[column][row] = value;
}

void putNextPieceOnTop() {
    currentTetrisPiece = createTetrisPiece_T(1, 0, 0);
}

bool isCurrentTetrisPieceOnBottom() {
    return isTetrisPieceOnBottom(currentTetrisPiece);
} 

bool isCurrentTetrisPieceTouchingAnotherPieceOnBottom() {
    return isTetrisPieceTouchingAnotherPieceOnBottom(tetrisMatrix, currentTetrisPiece);
} 

int getCompletedLinesCountAfterPieceTouchBottom() {
    return getCompletedLinesCount(tetrisMatrix);
}

/*void freeMatrixSlotForTetrisPiece(struct TetrisPiece *tetrisPiece) {
    updateMatrixSlot(tetrisPiece->block0->posX, tetrisPiece->block0->posY, FALSE);
    updateMatrixSlot(tetrisPiece->block1->posX, tetrisPiece->block1->posY, FALSE);
    updateMatrixSlot(tetrisPiece->block2->posX, tetrisPiece->block2->posY, FALSE);
    updateMatrixSlot(tetrisPiece->block3->posX, tetrisPiece->block3->posY, FALSE);
}*/

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
    currentTetrisPiece 
        = createTetrisPiece_T(
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
        /*&& !isTetrisPieceTouchingAnotherPieceOnLeft(tetrisMatrix, currentTetrisPiece)*/) {
        currentTetrisPiece->pivotPosX--;
        updateTetrisPiecePosition();
    }
}

void moveCurrentTetrisPieceRight() {
    if (!isTetrisPieceOnRightLimit(currentTetrisPiece)
        /*&& !isTetrisPieceTouchingAnotherPieceOnRight(tetrisMatrix, currentTetrisPiece)*/) {
        currentTetrisPiece->pivotPosX++;
        updateTetrisPiecePosition();
    }
}