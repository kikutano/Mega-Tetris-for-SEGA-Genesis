#include "mainmenu_scene_provider.c"
#include "../music/music_provider.c"
#include "../gameplay/tetris_gameplay.c"

#include <genesis.h>
#include <resources.h>

void changeSceneToTetrisGameplay();

void onMainMenuJoypadInput(u16 joy, u16 changed, u16 state) {
    if (state || changed) {}
    
    if (joy == JOY_1) {
        changeSceneToTetrisGameplay();
    }
}

void initMainMenu() {
    currentGameState = MAINMENUSTATE;

    loadMainMenuGraphics();
    playBGMusicMainMenu();
    JOY_setEventHandler(&onMainMenuJoypadInput);
    
    VDP_fadeInAll(mainmenu_scene_background.palette->data, 40, FALSE);
    VDP_waitFadeCompletion();
}

void updateMainMenu() {

}

void changeSceneToTetrisGameplay() {
    VDP_fadeOut(0, (4 * 16) - 1, 40, FALSE);
    VDP_waitFadeCompletion();

    playSoundFxTouchTheGround();
    XGM_stopPlay();
    initTetrisGameplayScene();
    initGameplay();
}