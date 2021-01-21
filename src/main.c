#include <genesis.h>
#include <resources.h>
#include "gameplay/tetris_gameplay.c"
#include "music/music_provider.c"
 
int main() {
    
    initSoundEffects();
    initTetrisGameplayScene();
    startGameplay();            

    while(1) {  
        VDP_showFPS(TRUE);
        updateGameplay();  
        VDP_waitVSync();
    }    
            
    return 0;  
}