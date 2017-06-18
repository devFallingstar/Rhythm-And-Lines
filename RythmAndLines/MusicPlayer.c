#include "TotalHeader.h"
#include "MusicPlayer.h"

void playMusic(int id) {
	if (id == 1) { //Evnas
		sndPlaySoundA("./MData/Song/song1.wav", SND_ASYNC | SND_NODEFAULT);
	}
	else if (id == 2) { //FLOWER
		sndPlaySoundA("./MData/Song/song2.wav", SND_ASYNC | SND_NODEFAULT);
	}
	
}