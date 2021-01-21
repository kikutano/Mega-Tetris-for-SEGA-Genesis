
#include "mainmenu/mainmenu_gameplay.c"
#include "gameplay/tetris_gameplay.c"

void initSceneManager() {
    initSoundEffects();
}

void startSceneManager() {
    initMainMenu();
}

void updateSceneManager() {
    if (currentState == MAINMENUSTATE) {
        updateMainMenu();
    }
    else if (currentState == GAMEPLAYSTATE) {
        updateGameplay();
    }
}