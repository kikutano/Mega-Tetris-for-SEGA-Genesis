#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"

void drawTetrisPiece(struct TetrisPiece *tetrisPiece) {
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionX(tetrisPiece->block0),
        getBlockSpritePositionY(tetrisPiece->block0));
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionX(tetrisPiece->block1),
        getBlockSpritePositionY(tetrisPiece->block1));
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionX(tetrisPiece->block2),
        getBlockSpritePositionY(tetrisPiece->block2));
    VDP_setTileMapXY(
        BG_A, 1, 
        getBlockSpritePositionX(tetrisPiece->block3),
        getBlockSpritePositionY(tetrisPiece->block3));    
    
    VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 
        getBlockSpritePositionX(tetrisPiece->block0),
        getBlockSpritePositionY(tetrisPiece->block0), 1, 1);
    VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 
        getBlockSpritePositionX(tetrisPiece->block1),
        getBlockSpritePositionY(tetrisPiece->block1), 1, 1);
    VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 
        getBlockSpritePositionX(tetrisPiece->block2),
        getBlockSpritePositionY(tetrisPiece->block2), 1, 1);
    VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 3), 
        getBlockSpritePositionX(tetrisPiece->block3),
        getBlockSpritePositionY(tetrisPiece->block3), 1, 1);
}

void deleteTetrisPiece(struct TetrisPiece *tetrisPiece) {
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(tetrisPiece->block0),
        getBlockSpritePositionY(tetrisPiece->block0));
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(tetrisPiece->block1),
        getBlockSpritePositionY(tetrisPiece->block1));
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(tetrisPiece->block2),
        getBlockSpritePositionY(tetrisPiece->block2));
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(tetrisPiece->block3),
        getBlockSpritePositionY(tetrisPiece->block3));

    MEM_free(tetrisPiece->block0);
    MEM_free(tetrisPiece->block1);
    MEM_free(tetrisPiece->block2);
    MEM_free(tetrisPiece->block3);
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