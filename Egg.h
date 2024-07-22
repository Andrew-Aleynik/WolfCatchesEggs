#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Constants.h"

class Egg{
	//Положения яиц
	const static int EGG_UP_LEFT_X = 312;
	const static int EGG_UP_LEFT_Y = 274;

	const static int EGG_UP_RIGHT_X = 749;
	const static int EGG_UP_RIGHT_Y = 272;
		
	const static int EGG_DOWN_LEFT_X = 312;
	const static int EGG_DOWN_LEFT_Y = 352;

	const static int EGG_DOWN_RIGHT_X = 749;
	const static int EGG_DOWN_RIGHT_Y = 349;

	const static int EGG_CRACKED_LEFT_X = 377;
	const static int EGG_CRACKED_LEFT_Y = 462;

	const static int EGG_CRACKED_RIGHT_X = 662;
	const static int EGG_CRACKED_RIGHT_Y = 462;

	//Размеры яиц
	const static int EGG_WIDTH = 19;
	const static int EGG_HEIGHT = 19;

	const static int EGG_CRACKED_WIDTH = 46;
	const static int EGG_CRACKED_HEIGHT = 20;

	//Стадия у яиц, от 0 до 4 - катится, 5 - стадия ловли, и 6 - разбившееся яйцо 
	int stage;

	//Время стадии
	int stageTime;

	//Позиция
	int position;

	//Разрешено ли сейчас двигаться?
	bool canMove;

	//Время одной стадии
	int maxStageTime = 20;

	//Время стадии ловли
	int maxCatchTime = maxStageTime / 2;

	public:
	Egg() {
	}

	Egg(int position) {
		this->position = position;
		stage = 0;
		stageTime = 0;
		canMove = false;
	}

	void increaseStage() {
		if (canMove) {
			stageTime++;
			if (stage == 4) {
				if (stageTime > maxCatchTime) {
					stage += 1;
					stageTime = 0;
				}
			}
			else {
				if (stageTime > maxStageTime) {
					stage += 1;
					stageTime = 0;
				}
			}
		}
	}

	//Перезапуск яйца
	void restart(int position) {
		canMove = false;
		stage = 0;
		stageTime = 0;
		this->position = position;
	}

	int getStage() {
		return stage;
	}

	int getPosition() {
		return position;
	}

	bool isMoving() {
		return canMove;
	}

	//Запуск движения яйца
	void start() {
		canMove = true;
	}

	void draw(SDL_Renderer* renderer, SDL_Texture* eggTexture, SDL_Texture* crackedEggTexture) {
		if (canMove) {
			SDL_Rect pos;
			if (stage < 5) {
				switch (position) {
				case UP_LEFT:
					pos.x = EGG_UP_LEFT_X + stage * 20;
					pos.y = EGG_UP_LEFT_Y + stage * 10;
					break;
				case DOWN_LEFT:
					pos.x = EGG_DOWN_LEFT_X + stage * 20;
					pos.y = EGG_DOWN_LEFT_Y + stage * 10;
					break;
				case UP_RIGHT:
					pos.x = EGG_UP_RIGHT_X - stage * 20;
					pos.y = EGG_UP_RIGHT_Y + stage * 10;
					break;
				case DOWN_RIGHT:
					pos.x = EGG_DOWN_RIGHT_X - stage * 20;
					pos.y = EGG_DOWN_RIGHT_Y + stage * 10;
					break;
				}
				pos.w = EGG_WIDTH;
				pos.h = EGG_HEIGHT;
				SDL_RenderCopy(renderer, eggTexture, NULL, &pos);
			}
			if (stage >= 5) {
				switch (position) {
				case UP_LEFT:
				case DOWN_LEFT:
					pos.x = EGG_CRACKED_LEFT_X;
					pos.y = EGG_CRACKED_LEFT_Y;
					break;
				case UP_RIGHT:
				case DOWN_RIGHT:
					pos.x = EGG_CRACKED_RIGHT_X;
					pos.y = EGG_CRACKED_RIGHT_Y;
					break;
				}
				pos.w = EGG_CRACKED_WIDTH;
				pos.h = EGG_CRACKED_HEIGHT;
				SDL_RenderCopy(renderer, crackedEggTexture, NULL, &pos);
			}
		}
	}

	//Уменьшить время стадии у яйца (ускорение игры)
	void decreaseStageTime(int delta) {
		if (maxStageTime > 8 || delta < 0) {
			maxStageTime -= delta;
			maxCatchTime = maxStageTime / 2;
		}
	}

	//Установить стандартное время стадии у яйца
	void resetStageTime() {
		maxStageTime = 20;
		maxCatchTime = maxStageTime / 2;
	}
};

