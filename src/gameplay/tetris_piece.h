#ifndef TETRIS_PIECE
#define TETRIS_PIECE

int tetrisSpriteMatrixOffsetX = 15;
int tetrisSpriteMatrixOffsetY = 2;

struct Block {
    int row;
    int column;
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

struct TetrisPiece {
    struct Block *block0;
    struct Block *block1;
    struct Block *block2;
    struct Block *block3;
    int pivotPosX;
    int pivotPosY;
    int rotationCount;
};
#endif