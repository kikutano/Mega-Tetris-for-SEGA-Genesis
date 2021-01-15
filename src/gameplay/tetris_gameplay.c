#include "tetris_piece_mover.c"
#include "tetris_gfx_drawer.c"

u8 FALLING_STATE = 0;
u8 CLEARING_ROWS_STATE = 1;

u16 waitFramesForFalling = 10;
u16 currentFrameCount = 0;
bool tetrisPieceOnBottom;
u8 animationBlinkingFrameDur = 20;
u8 animationBlikingFrameCount = 0;
u8 gameState = 0;

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

void enterInClearingGameState(u16 rowStartPoint, u16 rowsToClear) {
    gameState = CLEARING_ROWS_STATE;
    animationBlikingFrameCount = 0;
    startClearRowsAnimation(rowStartPoint, rowsToClear);
}

void updateFallingGameState() {
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

            u16 linesToClear = getCompletedRowLinesCount();
            if (linesToClear > 0) {
                enterInClearingGameState(rowsCleared[3], linesToClear);
            }
        }
        else {
            moveCurrentTetrisPieceDown();
        }
    }
}

void updateClearingRowsGameState() {
    updateRowBlinkingAnimation();
    ++animationBlikingFrameCount;

    if (animationBlikingFrameCount >= animationBlinkingFrameDur) {
        gameState = FALLING_STATE;
        clearRows();
    }
}

void updateGameplay() {
    if (gameState == CLEARING_ROWS_STATE) {
        updateClearingRowsGameState();
    }
    else if (gameState == FALLING_STATE) {
        updateFallingGameState();
    }
}