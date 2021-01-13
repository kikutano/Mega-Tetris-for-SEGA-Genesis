#include <genesis.h>
#include <resources.h>
#include "gameplay/tetris_gameplay.c"

void onJoystickInput( u16 joy, u16 changed, u16 state) {
	if (joy == JOY_1) {
		if (state & BUTTON_LEFT) {
            moveCurrentTetrisPieceLeft();
        }
        else if (state & BUTTON_RIGHT) {
            moveCurrentTetrisPieceRight();
        }
        else if (state & BUTTON_X) {
            rotateAntiClockwiseCurrentTetrisPiece();
        }
        else if (state & BUTTON_Y) {
            rotateClockwiseCurrentTetrisPiece();
        }
	}
}



int main() {
 
    VDP_setPaletteColor(0, RGB24_TO_VDPCOLOR(0x6dc2ca));
    
    //VDP_setPalette(PAL1, bgtile.palette->data);

    VDP_loadTileSet(tetrisblock_I.tileset, 1, DMA);
    VDP_loadTileSet(tetrisblock_J.tileset, 2, DMA);
    VDP_loadTileSet(tetrisblock_L.tileset, 3, DMA);
    VDP_loadTileSet(tetrisblock_O.tileset, 4, DMA);
    VDP_loadTileSet(tetrisblock_S.tileset, 5, DMA);
    VDP_loadTileSet(tetrisblock_T.tileset, 6, DMA);
    VDP_loadTileSet(tetrisblock_Z.tileset, 7, DMA);

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
        updateGameplay();            
        VDP_waitVSync();  
    }  

    return 0;
}