
#ifndef TETRIS_MUSICPROVIDER_
#define TETRIS_MUSICPROVIDER_

#include <genesis.h>
#include <resources.h>

#define SFX_TOUCHTHEGROUND 64
#define SFX_ROTATEPIECE    65
#define SFX_LINECLEAR      66
#define SFX_TETRIS_VOICE   67
#define SFX_DYING          68

void initSoundEffects() {
    XGM_setPCM(SFX_TOUCHTHEGROUND, sfx_touch, sizeof(sfx_touch));
    XGM_setPCM(SFX_ROTATEPIECE, sfx_rotation, sizeof(sfx_rotation));
    XGM_setPCM(SFX_LINECLEAR, sfx_lineclear, sizeof(sfx_lineclear));
    XGM_setPCM(SFX_TETRIS_VOICE, sfx_tetris_voice, sizeof(sfx_tetris_voice));
    XGM_setPCM(SFX_DYING, sfx_dying, sizeof(sfx_dying));
}

void playBGMusic(const u8 *song) {
    XGM_setLoopNumber(-1);
    XGM_startPlay(song);
}

void playBGMusicMainMenu() {
    playBGMusic(music_mainmenu);
}

void playBGMusicTetrisGameplay() {
    playBGMusic(music_gameplay);
}

void playSoundFxTouchTheGround() {
    XGM_startPlayPCM(SFX_TOUCHTHEGROUND, 1, SOUND_PCM_CH2);
}

void playSoundFxRotation() {
    XGM_startPlayPCM(SFX_ROTATEPIECE, 1, SOUND_PCM_CH2);
}

void playSoundFxLineClear() {
    XGM_startPlayPCM(SFX_LINECLEAR, 1, SOUND_PCM_CH2);
}

void playSoundFxTetrisVoice() {
    XGM_startPlayPCM(SFX_TETRIS_VOICE, 1, SOUND_PCM_CH3);
}

void playSoundDying() {
    XGM_startPlayPCM(SFX_DYING, 1, SOUND_PCM_CH3);
}

#endif