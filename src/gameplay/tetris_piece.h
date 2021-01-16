#ifndef TETRIS_PIECE
#define TETRIS_PIECE

int tetrisSpriteMatrixOffsetX = 15;
int tetrisSpriteMatrixOffsetY = 2;
u8 guiNextTetrisPieceXPos = 24;
u8 guiNextTetrisPieceYPos = 4;

struct Block {
    u16 row;
    u16 column;
    u16 type;
};

int getBlockSpritePositionX(struct Block *block) {
    return block->column + tetrisSpriteMatrixOffsetX;
}

int getBlockSpritePositionY(struct Block *block) {
    return block->row + tetrisSpriteMatrixOffsetY;
}

int getBlockSpritePositionXFromColumn(int column) {
    return column + tetrisSpriteMatrixOffsetX;
}

int getBlockSpritePositionYFromRow(int row) {
    return row + tetrisSpriteMatrixOffsetY;
}

int getBlockGUINextSpritePositionX(u16 column) {
    return guiNextTetrisPieceXPos + column;
}

int getBlockGUINextSpritePositionY(u16 row) {
    return guiNextTetrisPieceYPos + row;
}

u16 TETRISPIECE_I = 1;
u16 TETRISPIECE_J = 2;
u16 TETRISPIECE_L = 3;
u16 TETRISPIECE_O = 4;
u16 TETRISPIECE_S = 5;
u16 TETRISPIECE_T = 6;
u16 TETRISPIECE_Z = 7;

struct TetrisPiece {
    struct Block *block0;
    struct Block *block1;
    struct Block *block2;
    struct Block *block3;
    u16 pivotColumn;
    u16 pivotRow;
    u16 type;
    int rotationCount;
};
#endif