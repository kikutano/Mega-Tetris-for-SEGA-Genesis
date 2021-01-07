#include "tetris_piece_mover.c"

int waitFramesForFalling = 10;
int currentFrameCount = 0;
bool tetrisPieceOnBottom;
bool tetris;

void startGameplay() {
    putNextPieceOnTop();
}

void updateGameplay() {
    if (tetris) {
        return;
    }

    if (tetrisPieceOnBottom) {
        putNextPieceOnTop();
        tetrisPieceOnBottom = FALSE;
    }

    ++currentFrameCount;

    if (currentFrameCount >= waitFramesForFalling) {
        currentFrameCount = 0;

        moveCurrentTetrisPieceDown();

        if (isCurrentTetrisPieceOnBottom() 
            || isCurrentTetrisPieceTouchingAnotherPieceOnBottom()) {
            lockTetrisPieceOnBackground();
            tetrisPieceOnBottom = TRUE;

            if ( getCompletedLinesCountAfterPieceTouchBottom() > 0 ) {
                tetris = TRUE;
            }
        }
    }
}