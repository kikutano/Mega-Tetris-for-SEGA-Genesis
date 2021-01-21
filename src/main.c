#include <genesis.h>
#include <resources.h>
#include "scenemanager/scenemanager.c"

int main() {
    initSceneManager();
    startSceneManager();
 
    while(1) {  
        //VDP_showFPS(TRUE); 
        updateSceneManager();  
        VDP_waitVSync();
    } 
            
    return 0;    
} 