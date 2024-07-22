#pragma once
#define SDL_MAIN_HANDLED

#include <SDL_audio.h>

class Sound
{
	//Продолжительность проигрываемого звука
	Uint32 wavLength;
	//Буфер проигрываемого звука
	Uint8* wavBuffer;

	public:
	Sound() {

	}

	Sound(const char* pathToFile, SDL_AudioSpec wavSpec) {
		SDL_LoadWAV(pathToFile, &wavSpec, &wavBuffer, &wavLength);
	}

	//Проиграть звук
	void play(SDL_AudioDeviceID deviceId) {
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	//Очистка памяти
	void clear() {
		delete wavBuffer;
	}
};

