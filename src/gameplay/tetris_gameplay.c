#include "tetris_piece_mover.c"
#include "tetris_gfx_drawer.c"

u8 FALLING_STATE       = 0;
u8 CLEARING_ROWS_STATE = 1;

u16 waitWithDownPressed      = 5;
u16 waitFramesForFalling     = 30;
u16 waitFrameForFallingLvl1  = 30;

u16 currentFallingFrameCount = 0;
u16 waitFrameForHorzMovement = 5;
u16 currentFrameHorzMovCount = 0;
bool tetrisPieceOnBottom;
u8 animationBlinkingFrameDur = 20;
u8 animationBlikingFrameCount = 0;
u8 gameState = 0;

bool rightPressed                 = FALSE;
bool leftPressed                  = FALSE;
bool downPressed                  = FALSE;
bool rotationAntiClockwisePressed = FALSE;
bool rotationClockwisePressed     = FALSE;

void onJoypadInput( u16 joy, u16 changed, u16 state) {
	if (joy == JOY_1) {
		if (state & BUTTON_Y) {
            rotateAntiClockwiseCurrentTetrisPiece();
        }
        else if (state & BUTTON_X) {
            rotateClockwiseCurrentTetrisPiece();
        }

        if (state & BUTTON_RIGHT) {
            moveCurrentTetrisPieceRight();
            currentFrameHorzMovCount = 0;
        }
        else if (state & BUTTON_LEFT) {
            moveCurrentTetrisPieceLeft();
            currentFrameHorzMovCount = 0;
        }
	}
}

void startGameplay() {
    JOY_setEventHandler(&onJoypadInput);
    putNextPieceOnTop();
}

void enterInClearingGameState(u16 rowStartPoint, u16 rowsToClear) {
    gameState = CLEARING_ROWS_STATE;
    animationBlikingFrameCount = 0;
    startClearRowsAnimation(rowStartPoint, rowsToClear);
}

void updateDirectionalInputControls() {
    u16 value = JOY_readJoypad(JOY_1);

    downPressed  = value & BUTTON_DOWN;
    rightPressed = value & BUTTON_RIGHT;
    leftPressed  = value & BUTTON_LEFT;
    rotationAntiClockwisePressed = value & BUTTON_X;
    rotationClockwisePressed     = value & BUTTON_Y;
}

void updateInputControls() {
    ++currentFrameHorzMovCount;
    if (currentFrameHorzMovCount > waitFrameForHorzMovement) {
        currentFrameHorzMovCount = 0;

        updateDirectionalInputControls();

        if (rightPressed) {
            moveCurrentTetrisPieceRight();
        }
        else if (leftPressed) {
            moveCurrentTetrisPieceLeft();
        }
        
        if (downPressed) {
            waitFramesForFalling = waitWithDownPressed;
        }
        else if (!downPressed) {
            waitFramesForFalling = waitFrameForFallingLvl1;
        }
    }
}

void updateFallingGameState() {
    if (tetrisPieceOnBottom) {
        putNextPieceOnTop();
        tetrisPieceOnBottom = FALSE;
    }

    ++currentFallingFrameCount;

    if (currentFallingFrameCount >= waitFramesForFalling) {
        currentFallingFrameCount = 0;

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

    updateInputControls();
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