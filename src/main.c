#include <genesis.h>
#include <resources.h>
#include "gameplay/tetris_gameplay.c"

int main() {
 
    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
     
    //VDP_setPalette(PAL1, bgtile.palette->data);

    VDP_loadTileSet(tetrisblock_I.tileset, TETRISPIECE_I, DMA);
    VDP_loadTileSet(tetrisblock_J.tileset, TETRISPIECE_J, DMA);
    VDP_loadTileSet(tetrisblock_L.tileset, TETRISPIECE_L, DMA);
    VDP_loadTileSet(tetrisblock_O.tileset, TETRISPIECE_O, DMA);
    VDP_loadTileSet(tetrisblock_S.tileset, TETRISPIECE_S, DMA);
    VDP_loadTileSet(tetrisblock_T.tileset, TETRISPIECE_T, DMA);
    VDP_loadTileSet(tetrisblock_Z.tileset, TETRISPIECE_Z, DMA);

    VDP_loadTileSet(bgtile.tileset, 8, DMA);
    VDP_setPalette(PAL2, bgtile.palette->data);  
    
    /*VDP_fillTileMapRect(
        BG_B, 
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 1), 
        tetrisSpriteMatrixOffsetX - 1, 
        1, 
        GRID_COLUMNS + 2, GRID_ROWS + 2);*/

    VDP_fillTileMapRect(
        BG_B,  
        TILE_ATTR_FULL(PAL2, 0, FALSE, FALSE, 8),
        tetrisSpriteMatrixOffsetX, 
        tetrisSpriteMatrixOffsetY,  
        GRID_COLUMNS, GRID_ROWS);

    JOY_init();   
    JOY_setEventHandler(&onJoystickInput);
    startGameplay();           

    while(1) {  
        VDP_showFPS(TRUE); 
        updateGameplay(); 
        VDP_waitVSync();     
    }  

    return 0;
}