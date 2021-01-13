#include <genesis.h>
#include "tetris_piece.h"

u16 tetrisPiecesNumber = 7;

u16 getRandomNumber(u16 endIndex) {
    return (random() % endIndex - 1) + 1;
}

/*
    NES Tetris Pieces Generator:
    1. Choose a piece from 1-7
    2. If the last piece it's the same of the last, go to 1 just one time.
*/

u16 getRandomTetrisPieceUsingNesAlgorithm(struct TetrisPiece *currentTetrisPiece) {
    if (currentTetrisPiece != NULL) {
        u16 nextTetrisPieceType = getRandomNumber(tetrisPiecesNumber);

        if (nextTetrisPieceType != currentTetrisPiece->type) {
            return nextTetrisPieceType;
        }
    }

    return getRandomNumber(tetrisPiecesNumber);
}