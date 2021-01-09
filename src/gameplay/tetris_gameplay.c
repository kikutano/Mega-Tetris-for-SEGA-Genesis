#include "tetris_piece_mover.c"

u16 waitFramesForFalling = 10;
u16 currentFrameCount = 0;
bool tetrisPieceOnBottom;
bool tetris;

void startGameplay() {
    putNextPieceOnTop();
}

void updateGameplay() {
    //return;

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

            if (getCompletedRowLinesCount() > 0) {
                //tetris = TRUE;

                clearRows();
            }
        }
    }
}