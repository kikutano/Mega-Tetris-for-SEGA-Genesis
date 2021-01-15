#include <genesis.h>
#include "tetris_game_settings.h"

u16 data[10];
u16 rowsToClear;
u16 rowToStart;
bool blinkAnimationOn;

void startClearRowsAnimation(u16 startRow, u16 rowsCount) {
    rowToStart = startRow;
    rowsToClear = rowsCount;
}

void setTetrisRowTile(u16 tile) {
    for (int i = 0; i < 10; ++i) {
        data[i] = TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, tile);
    }

    for (int i = rowToStart; i > rowToStart - rowsToClear; --i) {
        VDP_setTileMapDataRow(
            BG_A, data,
            getBlockSpritePositionYFromRow(i), 
            getBlockSpritePositionXFromColumn(0), GRID_COLUMNS, DMA);
    }
}

void updateRowBlinkingAnimation() {
    if (blinkAnimationOn) {
        setTetrisRowTile(2);
    }
    else {
        setTetrisRowTile(1);
    }

    blinkAnimationOn = !blinkAnimationOn;
}