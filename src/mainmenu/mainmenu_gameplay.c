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
    loadAndShowMainMenuGraphicsWithFadeIn();

    JOY_setEventHandler(&onMainMenuJoypadInput);
    playBGMusicMainMenu();
}

void updateMainMenu() {

}

void changeSceneToTetrisGameplay() {
    XGM_stopPlay();
    VDP_fadeOutAll(40, FALSE);
    VDP_waitFadeCompletion();

    initTetrisGameplayScene();
    initGameplay();
}