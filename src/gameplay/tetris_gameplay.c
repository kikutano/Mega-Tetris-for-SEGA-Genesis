#ifndef _TETRIS_GAMEPLAY_
#define _TETRIS_GAMEPLAY_

#include "tetris_piece_mover.c"
#include "tetris_gfx_drawer.c"
#include "tetris_gameplay_scene_provider.c"
#include "../music/music_provider.c"

u8 FALLING_STATE       = 0;
u8 CLEARING_ROWS_STATE = 1;

u16 waitWithDownPressed      = 5;
u16 waitWithNormalFallSpeed  = 60;
u16 waitFramesForFalling     = 60;

u16 currentFallingFrameCount = 0;
u16 waitFrameForHorzMovement = 5;
u16 currentFrameHorzMovCount = 0;
bool tetrisPieceOnBottom;
u8 animationBlinkingFrameDur = 20;
u8 animationBlikingFrameCount = 0;
u8 gameState = 0;

u32 currentScore       = 0;
u16 linesCleared       = 0;
u16 currentLevel       = 1;
u16 nextLinesToLevelUp = 10;

bool rightPressed                 = FALSE;
bool leftPressed                  = FALSE;
bool downPressed                  = FALSE;
bool rotationAntiClockwisePressed = FALSE;
bool rotationClockwisePressed     = FALSE;

void onJoypadInput(u16 joy, u16 changed, u16 state) {
	if (joy == JOY_1) {
		if (state & BUTTON_Y) {
            playSoundFxRotation();
            rotateAntiClockwiseCurrentTetrisPiece();
        }
        else if (state & BUTTON_X) {
            playSoundFxRotation();
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
    currentState = GAMEPLAYSTATE;
    JOY_setEventHandler(&onJoypadInput);
    putNextPieceOnTop();
    playBGMusicTetrisGameplay();
}

void enterInClearingGameState(u16 rowStartPoint, u16 rowsToClear) {
    gameState = CLEARING_ROWS_STATE;
    animationBlikingFrameCount = 0;
    startClearRowsAnimation(rowStartPoint, rowsToClear);
}

void updateGameScoreWhenDownPressed() {
    currentScore += POINTS_PER_LINES;
}

void updateGameScoreScore(u8 lines) {
    if (lines == 1) {
        currentScore += POINTS_SINGLE;
    }
    else if (lines == 2) {
        currentScore += POINTS_DOUBLE;
    }
    else if (lines == 3) {
        currentScore += POINTS_TRIPLE;
    }
    else if (lines == 4) {
        currentScore += POINTS_TETRIS;
    }
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
            updateGameScoreWhenDownPressed();
            updateUICurrentScore(currentScore);
            
        }
        else if (!downPressed) {
            waitFramesForFalling = waitWithNormalFallSpeed;
        }
    }
}

void updateLinesCleared(u16 lines) {
    linesCleared += lines;
    updateUICurrentLines(linesCleared);
}

void increaseFallingSpeedAfterLevelUp() {
    if (waitWithNormalFallSpeed > 2) {
        waitWithNormalFallSpeed--;
        waitWithNormalFallSpeed--;
        waitFramesForFalling = waitWithNormalFallSpeed;
    }
}

void checkIfMustUpdateLevel() {
    if (linesCleared >= nextLinesToLevelUp) {
        currentLevel++;
        updateUICurrentLevel(currentLevel);
        increaseFallingSpeedAfterLevelUp();

        nextLinesToLevelUp = 10 * currentLevel;
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
                updateGameScoreScore(linesToClear);
                updateUICurrentScore(currentScore);
                updateLinesCleared(linesToClear);
                checkIfMustUpdateLevel();

                if (linesToClear >= 4) {
                    playSoundFxTetrisVoice();
                }
                else {
                    playSoundFxLineClear();
                }
            }
            else {
                playSoundFxTouchTheGround();
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

#endif