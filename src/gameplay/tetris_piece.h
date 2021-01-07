#ifndef TETRIS_PIECE
#define TETRIS_PIECE

struct Block {
    int row;
    int column;
};

int getBlockSpritePositionX(struct Block *block) {
    return block->column + 15;
}

int getBlockSpritePositionY(struct Block *block) {
    return block->row + 1;
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