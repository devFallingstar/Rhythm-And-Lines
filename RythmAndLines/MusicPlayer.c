#include "MusicPlayer.h"

void playMusic(int id) {
	sndPlaySoundA("./MData/Song/song1.wav", SND_ASYNC | SND_NODEFAULT);
}