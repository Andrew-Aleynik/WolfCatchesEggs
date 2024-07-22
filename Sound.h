#pragma once
#define SDL_MAIN_HANDLED

#include <SDL_audio.h>

class Sound
{
	//����������������� �������������� �����
	Uint32 wavLength;
	//����� �������������� �����
	Uint8* wavBuffer;

	public:
	Sound() {

	}

	Sound(const char* pathToFile, SDL_AudioSpec wavSpec) {
		SDL_LoadWAV(pathToFile, &wavSpec, &wavBuffer, &wavLength);
	}

	//��������� ����
	void play(SDL_AudioDeviceID deviceId) {
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
	//������� ������
	void clear() {
		delete wavBuffer;
	}
};

