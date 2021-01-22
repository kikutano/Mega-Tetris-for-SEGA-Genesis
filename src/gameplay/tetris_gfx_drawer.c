#include <genesis.h>
#include "tetris_game_settings.h"


u16 data[10];
u16 rowsToClear;
u16 rowToStart;
bool blinkAnimationOn;

const u8 anFrameDelay = 2;
u8 anFrameCurrent     = 0;
u8 rowAnimatedCount   = 0;
bool openingAnimationEnded;
bool closingAnimationEnded;

void startClearRowsAnimation(u16 startRow, u16 rowsCount) {
    rowToStart = startRow;
    rowsToClear = rowsCount;
}

void setTetrisRowTile(const u16 *data, u8 rowToStart, u8 rowsToClear) {
    for (u8 i = rowToStart; i > rowToStart - rowsToClear; --i) {
        VDP_setTileMapDataRow(
            BG_A, data,
            getBlockSpritePositionYFromRow(i), 
            getBlockSpritePositionXFromColumn(0), GRID_COLUMNS, DMA);
    }
}

void setTetrisRowsTile(u16 tile) {
    for (int i = 0; i < 10; ++i) {
        data[i] = TILE_ATTR_FULL(PALETTE_TETRIS_PIECE, 0, FALSE, FALSE, tile);
    }

    setTetrisRowTile(data, rowToStart, rowsToClear);
}

void updateRowBlinkingAnimation() {
    if (blinkAnimationOn) {
        setTetrisRowsTile(2);
    }
    else {
        setTetrisRowsTile(1);
    }

    blinkAnimationOn = !blinkAnimationOn;
}

void startAnimationWallOpeningTetrisGrid() {
    rowToStart  = GRID_ROWS - 1;
    rowsToClear = GRID_ROWS - 1;
    setTetrisRowsTile(1);

    anFrameCurrent = 0;
    rowAnimatedCount = 0;
    openingAnimationEnded = FALSE;
}

void animationWallOpeningEnded() {
    openingAnimationEnded = TRUE;
}

void updateAnimationWallOpeningTetrisGrid() {
    if (!openingAnimationEnded) {
        ++anFrameCurrent;

        if (anFrameCurrent > anFrameDelay) {
            anFrameCurrent = 0;

            rowToStart = GRID_ROWS - rowAnimatedCount + 1;
            
            VDP_clearTileMapRect(
                BG_A, 
                getBlockSpritePositionXFromColumn(0),
                rowToStart,
                GRID_COLUMNS, 1);

            ++rowAnimatedCount;

            if (rowAnimatedCount == GRID_ROWS) {
                animationWallOpeningEnded();
            } 
        }
    }
}

void startAnimationWallClosingTetrisGrid() {
    rowToStart = 0;
    rowsToClear = 1;
    anFrameCurrent = 0;
    rowAnimatedCount = 0;
    closingAnimationEnded = FALSE;
}

void animationWallClosingEnded() {
    closingAnimationEnded = TRUE;
}

void updateAnimationWallClosingTetrisGrid() {
    if (!closingAnimationEnded) {
        ++anFrameCurrent;

        if (anFrameCurrent > anFrameDelay) {
            anFrameCurrent = 0;

            rowToStart = rowAnimatedCount + 1;
            rowsToClear = 1;

            setTetrisRowsTile(1);

            ++rowAnimatedCount;

            if (rowAnimatedCount >= GRID_ROWS - 1) {
                animationWallClosingEnded();
            }
        }
    }
}