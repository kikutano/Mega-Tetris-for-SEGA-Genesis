#include "mainmenu_scene_provider.c"
#include "../music/music_provider.c"
#include "../gameplay/tetris_gameplay.c"

#include <genesis.h>
#include <resources.h>

void initMainMenu();
void updateMainMenu();
void changeSceneToTetrisGameplay();

void onMainMenuJoypadInput(u16 joy, u16 changed, u16 state) {
    if (state || changed) {}
    
    if (joy == JOY_1) {
        playSoundFxRotation();
        changeSceneToTetrisGameplay();
    }
}

void initMainMenu() {
    currentGameState = MAINMENUSTATE;
    loadAndShowMainMenuGraphicsWithFadeIn();

    JOY_setEventHandler(&onMainMenuJoypadInput);
    playBGMusicMainMenu();

    VDP_setPaletteColor(15,RGB24_TO_VDPCOLOR(0xffffff));
    VDP_drawText("Press Any Button", 12, 15);
}

void updateMainMenu() {

}

void changeSceneToTetrisGameplay() {
    XGM_stopPlay();
    VDP_clearTextLine(15);

    VDP_fadeOutAll(40, FALSE);
    VDP_waitFadeCompletion();

    initTetrisGameplayScene();
    initGameplay();
}