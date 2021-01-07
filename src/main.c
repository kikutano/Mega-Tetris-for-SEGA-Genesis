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
    VDP_loadTileSet(bgtile.tileset, 1, DMA);
    VDP_setPalette(PAL1, bgtile.palette->data);
    VDP_fillTileMapRect(BG_B, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, 1), 15, 2, GRID_COLUMNS, GRID_ROWS); 
    JOY_init();
    JOY_setEventHandler(&onJoystickInput);
    startGameplay(); 
  
    while(1) {
        updateGameplay();  
        VDP_waitVSync();   
    } 

    return 0;
}