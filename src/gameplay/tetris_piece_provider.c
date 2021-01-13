#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_piece_creator.c"

void drawTetrisBlock(struct Block *block, u16 type) {
    VDP_setTileMapXY(
        BG_A, TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, type + 1), 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block));
    
    /*VDP_fillTileMapRectInc(
        BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 2), 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block), 1, 1);*/
}

void drawTetrisPiece(struct TetrisPiece *tetrisPiece) {
    drawTetrisBlock(tetrisPiece->block0, tetrisPiece->type);
    drawTetrisBlock(tetrisPiece->block1, tetrisPiece->type);
    drawTetrisBlock(tetrisPiece->block2, tetrisPiece->type);
    drawTetrisBlock(tetrisPiece->block3, tetrisPiece->type);
}

void deleteTetrisBlock(struct Block *block) {
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionX(block),
        getBlockSpritePositionY(block));
    
    MEM_free(block);
}

void deleteTetrisTileOnGrid(u16 column, u16 row) {
    VDP_setTileMapXY(
        BG_A, 0, 
        getBlockSpritePositionXFromColumn(column),
        getBlockSpritePositionYFromRow(row));
}

void drawTetrisTileOnGrid(u16 column, u16 row) {
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

void deleteSpritesOnRow(u16 row) {
    VDP_setTileMapDataRow(
        BG_A, 0, 
        getBlockSpritePositionYFromRow(row), 
        getBlockSpritePositionXFromColumn(0), 10, CPU );
}