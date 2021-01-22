
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "mainmenu/mainmenu_gameplay.c"
#include "gameplay/tetris_gameplay.c"

void initSceneManager() {
    initSoundEffects();
}

void startSceneManager() {
    initMainMenu();
}

void updateSceneManager() {
    if (currentGameState == MAINMENUSTATE) {
        updateMainMenu();
    }
    else if (currentGameState == GAMEPLAYSTATE) {
        updateGameplay();

        if (goToMainMenu) {
            goToMainMenu = FALSE;
            JOY_setEventHandler(NULL);
            initMainMenu();
        }
    }
}

#endif