#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"

void drawTetrisBlock(struct Block *block) {
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block));
    
    VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block), 1, 1);
}

void drawTetrisPiece(struct TetrisPiece *tetrisPiece) {
    drawTetrisBlock(tetrisPiece->block0);
    drawTetrisBlock(tetrisPiece->block1);
    drawTetrisBlock(tetrisPiece->block2);
    drawTetrisBlock(tetrisPiece->block3);
}

void deleteTetrisBlock(struct Block *block) {
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block));
    
    MEM_free(block);
}

void deleteTetrisTileOnGrid(int column, int row) {
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionXFromColumn(column),
        getBlockSpritePositionYFromRow(row));
}

void drawTetrisTileOnGrid(int column, int row) {
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionXFromColumn(column),
        getBlockSpritePositionYFromRow(row));
}

void deleteTetrisPiece(struct TetrisPiece *tetrisPiece) {
    deleteTetrisBlock(tetrisPiece->block0);
    deleteTetrisBlock(tetrisPiece->block1);
    deleteTetrisBlock(tetrisPiece->block2);
    deleteTetrisBlock(tetrisPiece->block3);

    MEM_free(tetrisPiece);
}

void deleteSpritesOnRow(int row) {
    VDP_setTileMapDataRow(
        BG_A, 0, 
        getBlockSpritePositionYFromRow(row), 
        getBlockSpritePositionXFromColumn(0), 10, CPU );
}

struct TetrisPiece* createTetrisPiece() {
    struct TetrisPiece *tetrisPiece 
        = MEM_alloc( sizeof(struct TetrisPiece) );

    tetrisPiece->block0 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block1 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block2 = MEM_alloc( sizeof( struct Block ) );
    tetrisPiece->block3 = MEM_alloc( sizeof( struct Block ) );

    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_T(
    int column, int row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPiece();

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
    
    drawTetrisPiece(tetrisPiece);
    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_O(
    int column, int row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPiece();

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
    
    drawTetrisPiece(tetrisPiece);
    return tetrisPiece;
}

struct TetrisPiece* createTetrisPiece_I(
    int column, int row, int rotationCount) {
    struct TetrisPiece *tetrisPiece = createTetrisPiece();

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
    else if ( rotationCount == 1 || rotationCount == 3) {
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
    
    drawTetrisPiece(tetrisPiece);
    return tetrisPiece;
}