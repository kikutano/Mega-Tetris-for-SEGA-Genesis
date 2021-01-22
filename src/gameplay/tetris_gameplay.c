#ifndef _TETRIS_GAMEPLAY_
#define _TETRIS_GAMEPLAY_

#include "tetris_piece_mover.c"
#include "tetris_gameplay_scene_provider.c"
#include "../scenemanager/scenechanger.h"
#include "../music/music_provider.c"

const u8 FALLING_STATE       = 0;
const u8 CLEARING_ROWS_STATE = 1;
const u8 GAMEOVER_STATE      = 2;
const u8 OPENING_STATE       = 3;
const u8 CLOSING_STATE       = 4;

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
u32 highScore          = 0;
u16 linesCleared       = 0;
u16 currentLevel       = 1;
u16 nextLinesToLevelUp = 10;

bool rightPressed                 = FALSE;
bool leftPressed                  = FALSE;
bool downPressed                  = FALSE;
bool rotationAntiClockwisePressed = FALSE;
bool rotationClockwisePressed     = FALSE;
bool goToMainMenu;

void clearGameplayTetrisScene() {
    VDP_clearTileMapRect(BG_A, 0, 0, 40, 28);
    VDP_clearTileMapRect(BG_B, 0, 0, 40, 28);
    JOY_setEventHandler(NULL);
    clearMatrixSlot();
}

void performGoBackToMainMenu() {
    goToMainMenu = TRUE;

    VDP_fadeOut(0, (4 * 16) - 1, 40, FALSE);
    VDP_waitFadeCompletion();

    clearGameplayTetrisScene();
}

void onJoypadInput(u16 joy, u16 changed, u16 state) {
    if (state || changed) {}

	if (joy == JOY_1) {
        if (gameState == GAMEOVER_STATE) {
            performGoBackToMainMenu();
        }

		if (state & BUTTON_Y) {
            deleteSpritesOnRow(10);

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

void initGameplay() {
    VDP_fadeInAll(tetris_scene_background.palette->data, 40, FALSE);
    VDP_waitFadeCompletion();

    currentScore = 0;
    linesCleared = 0;
    currentLevel = 1;
    currentGameState = GAMEPLAYSTATE;
    gameState = OPENING_STATE;

    initTetrisGameplayScene();
    updateUICurrentHighScore(highScore);
}

void startGameplay() {
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

void enterInPlayerDyingState() {
    if (currentScore > highScore) {
        highScore = currentScore;
    }

    XGM_stopPlay();
    playSoundDying();
    gameState = CLOSING_STATE;
    startAnimationWallClosingTetrisGrid();
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
            
            if ( isCurrentTetrisPieceOnGameOverZone() ) {
                enterInPlayerDyingState();
            }
            else {
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
        }
        else {
            moveCurrentTetrisPieceDown();
        }
    }

    updateInputControls();
}

void enterInGameOverState() {
    gameState = GAMEOVER_STATE;
    VDP_drawText("Game Over!", 6, 16 );
    VDP_drawText("Press Any Button To Restart", 6, 18 );
}

void updateClearingRowsGameState() {
    updateRowBlinkingAnimation();
    ++animationBlikingFrameCount;

    if (animationBlikingFrameCount >= animationBlinkingFrameDur) {
        gameState = FALLING_STATE;
        clearRows();
    }
}

void updateOpeningWallState() {
    updateAnimationWallOpeningTetrisGrid();

    if (openingAnimationEnded) {
        gameState = FALLING_STATE;
        startGameplay();
    }
}

void updateGameOverPresentationState() {
    updateAnimationWallClosingTetrisGrid();

    if (closingAnimationEnded) {
        enterInGameOverState();
    }
}

void updateGameplay() {
    if (gameState == CLEARING_ROWS_STATE) {
        updateClearingRowsGameState();
    }
    else if (gameState == FALLING_STATE) {
        updateFallingGameState();
    }
    else if (gameState == GAMEOVER_STATE) {
        
    }
    else if (gameState == OPENING_STATE) {
        updateOpeningWallState();
    }
    else if (gameState == CLOSING_STATE) {
        updateGameOverPresentationState();
    }
}

#endif