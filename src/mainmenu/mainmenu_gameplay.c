#include "mainmenu_scene_provider.c"
#include "../music/music_provider.c"
#include "../gameplay/tetris_gameplay.c"

#include <genesis.h>
#include <resources.h>

void changeSceneToTetrisGameplay();

void onMainMenuJoypadInput(u16 joy, u16 changed, u16 state) {
    if (joy == JOY_1) {
        changeSceneToTetrisGameplay();
    }
}

void initMainMenu() {
    loadMainMenuGraphics();
    playBGMusicMainMenu();

    JOY_setEventHandler(&onMainMenuJoypadInput);
}

void updateMainMenu() {

}

void changeSceneToTetrisGameplay() {
    playSoundFxTouchTheGround();
    XGM_stopPlay();
    initTetrisGameplayScene();
    startGameplay();
}