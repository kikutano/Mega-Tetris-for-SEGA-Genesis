#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_game_settings.h"

const u8 guiNextPieceRectX = 26;
const u8 guiNextPieceRectY = 2;
const u8 guiNextPieceRectW = 6;
const u8 guiNextPieceRectH = 4;

const u8 guiCurrScoreRectX = 5;
const u8 guiCurrScoreRectY = 6;
const u8 guiCurrScoreRectW = 6;
const u8 guiCurrScoreRectH = 4;

const u8 guiHighScoreRectX = 5;
const u8 guiHighScoreRectY = 2;
const u8 guiHighScoreRectW = 6;
const u8 guiHighScoreRectH = 4;

const u8 guiLevelRectX = 26;
const u8 guiLevelRectY = 10;
const u8 guiLevelRectW = 6;
const u8 guiLevelRectH = 4;

const u8 guiLinesRemainingRectX = 26;
const u8 guiLinesRemainingRectY = 20;
const u8 guiLinesRemainingRectW = 6;
const u8 guiLinesRemainingRectH = 4;

void loadTetrisGameplayGraphics() {
    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
     
    VDP_loadTileSet(tetrisblock_I.tileset, TETRISPIECE_I, DMA);
    VDP_loadTileSet(tetrisblock_J.tileset, TETRISPIECE_J, DMA);
    VDP_loadTileSet(tetrisblock_L.tileset, TETRISPIECE_L, DMA);
    VDP_loadTileSet(tetrisblock_O.tileset, TETRISPIECE_O, DMA);
    VDP_loadTileSet(tetrisblock_S.tileset, TETRISPIECE_S, DMA);
    VDP_loadTileSet(tetrisblock_T.tileset, TETRISPIECE_T, DMA);
    VDP_loadTileSet(tetrisblock_Z.tileset, TETRISPIECE_Z, DMA);

    VDP_loadTileSet(bgtile.tileset, 8, DMA);
    VDP_setPalette(PAL2, bgtile.palette->data);  
}

void drawGameplayGrid() {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 8),
        tetrisSpriteMatrixOffsetX, 
        tetrisSpriteMatrixOffsetY,  
        GRID_COLUMNS, GRID_ROWS);
}

void drawGamplayNextTetrisPieceContainer() {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 8), 
        guiNextPieceRectX, 
        guiNextPieceRectY, 
        guiNextPieceRectW, 
        guiNextPieceRectH);
    
    VDP_drawTextBG(
        BG_A, "NEXT", guiNextPieceRectX + 1, guiNextPieceRectY);
}

void drawGameplayHighScore() {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 0), 
        guiHighScoreRectX, 
        guiHighScoreRectY, 
        guiHighScoreRectW, 
        guiHighScoreRectH);
    
    VDP_drawTextBG(
        BG_A, "H-Score", guiHighScoreRectX + 1, guiHighScoreRectY);
    
    VDP_drawTextBG(
        BG_A, "1000000", guiHighScoreRectX + 1, guiHighScoreRectY + 1);
}


void drawGameplayCurrentScore(char *score) {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 0), 
        guiCurrScoreRectX, 
        guiCurrScoreRectY, 
        guiCurrScoreRectW, 
        guiCurrScoreRectH);
    
    VDP_drawTextBG(
        BG_A, "Score", guiCurrScoreRectX + 1, guiCurrScoreRectY);

    VDP_drawTextBG(
        BG_A, score, guiCurrScoreRectX + 1, guiCurrScoreRectY + 1);
}

void drawGameplayCurrentLevel() {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 0), 
        guiLevelRectX, 
        guiLevelRectY, 
        guiLevelRectW, 
        guiLevelRectH);
    
    VDP_drawTextBG(
        BG_A, "LEVEL", guiLevelRectX + 1, guiLevelRectY);
    
    VDP_drawTextBG(
        BG_A, "1", guiLevelRectX + 1, guiLevelRectY + 1);
}

void drawGameplayLinesRemaining() {
    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 0), 
        guiLinesRemainingRectX, 
        guiLinesRemainingRectY, 
        guiLinesRemainingRectW, 
        guiLinesRemainingRectH);
    
    VDP_drawTextBG(
        BG_A, "LINE REMAINING", guiLinesRemainingRectX + 1, guiLinesRemainingRectY);
    
    VDP_drawTextBG(
        BG_A, "10", guiLinesRemainingRectX + 1, guiLinesRemainingRectY + 1);
}

void updateUICurrentScore(u16 score) {
    char s[7];
    uintToStr(score, s, 7);

    drawGameplayCurrentScore(s);
}

void initTetrisGameplayScene() {
    loadTetrisGameplayGraphics();
    drawGameplayGrid();
    drawGamplayNextTetrisPieceContainer();
    drawGameplayHighScore();
    drawGameplayCurrentLevel();
    drawGameplayLinesRemaining();
    
    updateUICurrentScore(0);
    
    JOY_init();     
}