#include "tetris_piece.h"
#include "tetris_game_settings.h"

int leftLimit  = 0;
int rightLimit = 9;
int downLimit  = 24;

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

int getCompletedLinesCount(bool tetrisMatrix[GRID_COLUMNS][GRID_ROWS]) {
    int completedCount = 0;
    bool completedRow = TRUE;

    for (int row = 0; row <= GRID_ROWS; ++row) {
        for (int column = 0; column < GRID_COLUMNS; ++column) {
            if (!tetrisMatrix[column][row]) {
                completedRow = FALSE;
            }
        }

        if (completedRow) {
            ++completedCount;
        }
        
        completedRow = TRUE;
    }
    
    return completedCount;
}