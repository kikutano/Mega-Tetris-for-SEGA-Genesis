#ifndef TETRIS_PIECE
#define TETRIS_PIECE

int tetrisSpriteMatrixOffsetX = 15;
int tetrisSpriteMatrixOffsetY = 2;

struct Block {
    u16 row;
    u16 column;
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

u16 TETRISPIECE_I = 0;
u16 TETRISPIECE_J = 1;
u16 TETRISPIECE_L = 2;
u16 TETRISPIECE_O = 3;
u16 TETRISPIECE_S = 4;
u16 TETRISPIECE_T = 5;
u16 TETRISPIECE_Z = 6;

struct TetrisPiece {
    struct Block *block0;
    struct Block *block1;
    struct Block *block2;
    struct Block *block3;
    u16 pivotPosX;
    u16 pivotPosY;
    int rotationCount;
    u16 Type;
};
#endif