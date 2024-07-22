#pragma once
#define SDL_MAIN_HANDLED

#include <SDL.h>

class Button
{
	bool isPressed = false;

	SDL_Rect position;

public:
	Button(){
	}

	Button(int x, int y, int width, int height) {
		position.x = x;
		position.y = y;
		position.w = width;
		position.h = height;
	}
	

	void press() {
		if (!isPressed) {
			isPressed = true;
		}
	}

	bool inRect(int clickX, int clickY) {
		return 
			position.x <= clickX && 
			clickX <= position.x + position.w &&
			position.y <= clickY && 
			clickY <= position.y + position.h;
	}

	void release() {
		if (isPressed) {
			isPressed = false;
		}
	}

	void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Texture* texturePressed) {
		if (isPressed) {
			SDL_RenderCopy(renderer,texturePressed, NULL, &position);
		}
		else {
			SDL_RenderCopy(renderer, texture, NULL, &position);
		}
	}
};

