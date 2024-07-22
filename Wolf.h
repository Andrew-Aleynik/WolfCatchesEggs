#pragma once
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "Constants.h"

class Wolf{
	//Положения волка
	const static int UP_LEFT_X = 395;
	const static int UP_LEFT_Y = 306;

	const static int UP_RIGHT_X = 530;
	const static int UP_RIGHT_Y = 317;

	const static int DOWN_LEFT_X = 395;
	const static int DOWN_LEFT_Y = 306;

	const static int DOWN_RIGHT_X = 530;
	const static int DOWN_RIGHT_Y = 317;

	//Размеры текстуры
	const static int WIDTH = 150;
	const static int HEIGHT = 150;

	//Положение волка
	int position;

	public:
	Wolf() {
	}

	Wolf(SDL_Renderer* renderer) {
		position = UP_LEFT;
	}

	void setPosition(int position) {
		this->position = position;
	}

	int getPosition() {
		return position;
	}

	void draw(SDL_Renderer* renderer, SDL_Texture* textures[]) {
		int x = 0;
		int y = 0;
		switch (position)
		{
		case UP_LEFT:
			x = UP_LEFT_X;
			y = UP_LEFT_Y;
			break;
		case UP_RIGHT:
			x = UP_RIGHT_X;
			y = UP_RIGHT_Y;
			break;
		case DOWN_LEFT:
			x = DOWN_LEFT_X;
			y = DOWN_LEFT_Y;
			break;
		case DOWN_RIGHT:
			x = DOWN_RIGHT_X;
			y = DOWN_RIGHT_Y;
			break;
		}
		SDL_Rect pos;
		pos.x = x;
		pos.y = y;
		pos.w = WIDTH;
		pos.h = HEIGHT;

		SDL_RenderCopy(renderer, textures[position], NULL, &pos);
	}
};




