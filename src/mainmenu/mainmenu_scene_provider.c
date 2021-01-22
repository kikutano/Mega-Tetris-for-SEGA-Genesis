#include <genesis.h>
#include <resources.h>

void loadMainMenuGraphics() {
    VDP_setPalette(PAL0, 
        mainmenu_scene_background.palette->data);
    VDP_drawImageEx(
        BG_B, 
        &mainmenu_scene_background, 
        TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 1), 0, 0, 1, DMA);
    
    VDP_drawTextBG(BG_A, "v0.8.1", 30, 26);
    VDP_drawTextBG(BG_A, "@kikutano", 30, 27);
}