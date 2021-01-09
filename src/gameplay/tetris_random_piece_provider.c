#include <genesis.h>
#include "tetris_piece.h"

u16 getRandomNumber(u16 endIndex) {
    return (random() % endIndex - 1) + 1;
}

u16 getRandomTetrisPieceUsingNesAlgorithm(struct TetrisPiece *currentTetrisPiece) {
    return getRandomNumber(7);
}