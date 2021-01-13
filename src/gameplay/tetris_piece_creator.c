#include <genesis.h>
#include "tetris_piece.h"

struct TetrisPiece* createTetrisPieceContainer() {
    struct TetrisPiece *tetrisPiece 
        = MEM_alloc( sizeof(struct TetrisPiece) );

    tetrisPiece->block0 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block1 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block2 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block3 = MEM_alloc( sizeof( struct Block ) );

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_T(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    tetrisPiece->block0->row = row;
    tetrisPiece->block0->column = column;

    if (rotationCount == 0) {
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column - 1;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column;
    }
    else if (rotationCount == 1) {
        tetrisPiece->block1->row = row - 1;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column;
    }
    else if (rotationCount == 2) {
        tetrisPiece->block1->row = row - 1;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 3) {
        tetrisPiece->block1->row = row - 1;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row;
        tetrisPiece->block3->column = column - 1;
    }

    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_T;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_O(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column + 1;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column + 1;
    }

    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_O;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_I(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0 || rotationCount == 2) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row + 1;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 2;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 3;
        tetrisPiece->block3->column = column;
    }
    else if (rotationCount == 1 || rotationCount == 3) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column - 1;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row;
        tetrisPiece->block3->column = column + 2;
    }
    
    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_I;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_J(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column - 1;        
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column + 1;
    }
    else if (rotationCount == 1) {
        tetrisPiece->block0->row = row - 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 2) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column + 1;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column - 1;
        tetrisPiece->block3->row = row - 1;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 3) {
        tetrisPiece->block0->row = row + 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row - 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row - 1;
        tetrisPiece->block3->column = column + 1;
    }
    
    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_J;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_L(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column - 1;        
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 1) {
        tetrisPiece->block0->row = row - 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row - 1;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 2) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column - 1;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row - 1;
        tetrisPiece->block3->column = column + 1;
    }
    else if (rotationCount == 3) {
        tetrisPiece->block0->row = row - 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column + 1;
    }
    
    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_L;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_S(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0 || rotationCount == 2) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column + 1;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column - 1;
    }
    else if (rotationCount == 1 || rotationCount == 3) {
        tetrisPiece->block0->row = row - 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column + 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column + 1;
    }
    
    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_S;

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_Z(
    u16 column, u16 row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPieceContainer();

    if (rotationCount == 0 || rotationCount == 2) {
        tetrisPiece->block0->row = row;
        tetrisPiece->block0->column = column - 1;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row + 1;
        tetrisPiece->block2->column = column;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column + 1;
    }
    else if (rotationCount == 1 || rotationCount == 3) {
        tetrisPiece->block0->row = row - 1;
        tetrisPiece->block0->column = column;
        tetrisPiece->block1->row = row;
        tetrisPiece->block1->column = column;
        tetrisPiece->block2->row = row;
        tetrisPiece->block2->column = column - 1;
        tetrisPiece->block3->row = row + 1;
        tetrisPiece->block3->column = column - 1;
    }
    
    tetrisPiece->rotationCount = rotationCount;
    tetrisPiece->pivotPosX = column;
    tetrisPiece->pivotPosY = row;
    tetrisPiece->type = TETRISPIECE_Z;

    return tetrisPiece;
}