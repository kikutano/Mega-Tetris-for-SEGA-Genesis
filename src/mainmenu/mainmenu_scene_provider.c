#include <genesis.h>
#include <resources.h>

void loadAndShowMainMenuGraphicsWithFadeIn();

void loadAndShowMainMenuGraphicsWithFadeIn() {
    VDP_setPaletteColors(PAL0, (u16*)palette_black, 64);

    VDP_drawImageEx(
        BG_B, 
        &mainmenu_scene_background, 
        TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 1), 0, 0, FALSE, DMA);

    VDP_fadeInAll(mainmenu_scene_background.palette->data, 40, FALSE);
    VDP_waitFadeCompletion();

    VDP_setPalette(PAL0, 
        mainmenu_scene_background.palette->data);
    
    VDP_drawTextBG(BG_A, "v0.8.1", 30, 26);
    VDP_drawTextBG(BG_A, "@kikutano", 30, 27);
}