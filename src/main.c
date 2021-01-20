#include <genesis.h>
#include <resources.h>
#include "gameplay/tetris_gameplay.c"
 
int main() {
 
    initTetrisGameplayScene();
    startGameplay();            

    while(1) {  
        VDP_showFPS(TRUE);
        updateGameplay(); 
        VDP_waitVSync(); 
    }    
          
    return 0;   
}