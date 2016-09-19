#include "sound.h"

SoundInfo Sound::sound_list[2];

void Sound::loadSounds() {

}

void Sound::setPlay(SoundList sound) {
	Sound::sound_list[(int)sound].validation = true;
}

void Sound::playAll() {
	for each (SoundInfo var in Sound::sound_list)
	{
		if (var.validation == false) continue;


	}
}