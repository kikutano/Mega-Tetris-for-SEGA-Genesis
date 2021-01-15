#include "tetris_piece_mover.c"

u16 waitFramesForFalling = 10;
u16 currentFrameCount = 0;
bool tetrisPieceOnBottom;

void onJoystickInput( u16 joy, u16 changed, u16 state) {
	if (joy == JOY_1) {
		if (state & BUTTON_LEFT) {
            moveCurrentTetrisPieceLeft();
        }
        else if (state & BUTTON_RIGHT) {
            moveCurrentTetrisPieceRight();
        }
        else if (state & BUTTON_X) {
            rotateAntiClockwiseCurrentTetrisPiece();
        }
        else if (state & BUTTON_Y) {
            rotateClockwiseCurrentTetrisPiece();
        }
	}
}

void startGameplay() {
    putNextPieceOnTop();
}

void updateGameplay() {
    if (tetrisPieceOnBottom) {
        putNextPieceOnTop();
        tetrisPieceOnBottom = FALSE;
    }

    ++currentFrameCount;

    if (currentFrameCount >= waitFramesForFalling) {
        currentFrameCount = 0;

        if (isCurrentTetrisPieceOnBottom() 
            || isCurrentTetrisPieceTouchingAnotherPieceOnBottom()) {
            lockTetrisPieceOnBackground();
            tetrisPieceOnBottom = TRUE;

            if (getCompletedRowLinesCount() > 0) {
                clearRows();
            }
        }
        else {
            moveCurrentTetrisPieceDown();
        }
    }
}