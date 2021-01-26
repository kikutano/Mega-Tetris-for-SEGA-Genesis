#include <genesis.h>
#include <resources.h>
#include "tetris_piece.h"
#include "tetris_game_settings.h"
#include "tetris_gfx_drawer.c"

const u8 guiNextPieceRectX = 26;
const u8 guiNextPieceRectY = 2;
const u8 guiNextPieceRectW = 6;
const u8 guiNextPieceRectH = 4;

const u8 guiHighScoreRectX = 28;
const u8 guiHighScoreRectY = 4;
const u8 guiCurrScoreRectX = 28;
const u8 guiCurrScoreRectY = 8;
const u8 guiLevelRectX     = 30;
const u8 guiLevelRectY     = 16;
const u8 guiLinesRectX     = 30;
const u8 guiLinesRectY     = 12;

void loadTetrisPiecesGameplayGraphics();
void loadTetrisGameplayBackgroundWithFadeIn();
void updateUICurrentLines(const u16 level);
void updateUICurrentLevel(const u16 level);
void updateUICurrentScore(const u32 score);
void updateUICurrentHighScore(const u32 hiscore);
void initTetrisGameplayScene();

void loadTetrisPiecesGameplayGraphics() {
    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x000000));
     
    VDP_loadTileSet(tetrisblock_I.tileset, TETRISPIECE_I, DMA);
    VDP_loadTileSet(tetrisblock_J.tileset, TETRISPIECE_J, DMA);
    VDP_loadTileSet(tetrisblock_L.tileset, TETRISPIECE_L, DMA);
    VDP_loadTileSet(tetrisblock_O.tileset, TETRISPIECE_O, DMA);
    VDP_loadTileSet(tetrisblock_S.tileset, TETRISPIECE_S, DMA);
    VDP_loadTileSet(tetrisblock_T.tileset, TETRISPIECE_T, DMA);
    VDP_loadTileSet(tetrisblock_Z.tileset, TETRISPIECE_Z, DMA);
    VDP_loadTileSet(bgtile.tileset, 8, DMA);

    VDP_setPalette(PALETTE_TETRIS_PIECE, bgtile.palette->data);
}

void loadTetrisGameplayBackgroundWithFadeIn() {
    VDP_setPaletteColors(PAL0, (u16*)palette_black, 64);

    VDP_setPalette(PALETTE_TETRIS_BACKGOUND, 
        tetris_scene_background.palette->data);

    VDP_drawImageEx(
        BG_B, 
        &tetris_scene_background, 
        TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 9), 0, 0, FALSE, DMA);
    
    VDP_fadeInAll(tetris_scene_background.palette->data, 40, FALSE);
    VDP_waitFadeCompletion();

    VDP_setPalette(PALETTE_TETRIS_BACKGOUND, 
        tetris_scene_background.palette->data);
}

void updateUICurrentLines(const u16 level) {
    char s[3];
    uintToStr(level, s, 3);

    VDP_drawTextBG(BG_A, s, guiLinesRectX, guiLinesRectY);
}

void updateUICurrentLevel(const u16 level) {
    char s[3];
    uintToStr(level, s, 3);

    VDP_drawTextBG(BG_A, s, guiLevelRectX, guiLevelRectY);
}

void updateUICurrentScore(const u32 score) {
    char s[7];
    uintToStr(score, s, 7);

    VDP_drawTextBG(BG_A, s, guiCurrScoreRectX, guiCurrScoreRectY);
}

void updateUICurrentHighScore(const u32 hiscore) {
    char s[7];
    uintToStr(hiscore, s, 7);

    VDP_drawTextBG(BG_A, s, guiHighScoreRectX, guiHighScoreRectY);
}

void initTetrisGameplayScene() {
    loadTetrisGameplayBackgroundWithFadeIn();
    loadTetrisPiecesGameplayGraphics();
    
    updateUICurrentScore(0);
    updateUICurrentHighScore(0);
    updateUICurrentLevel(1);
    updateUICurrentLines(0);
    startAnimationWallOpeningTetrisGrid();
    
    JOY_init();
}