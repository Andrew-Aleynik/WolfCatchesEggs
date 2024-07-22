#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

//Для отрисовки текста
class Text
{
	//Размер символа на картинке
	const static int SRC_WIDTH = 20;
	const static int SRC_HEIGHT = 33;

	//Коды необходимых символов
	const static char _0 = '0';
	const static char _9 = '9';
	const static char A = 'а';
	const static char E = 'е';
	const static char IA = 'я';
	const static char SPACE = ' ';

	public:
	Text() {
	}

	//Отрисовка числа в виде "ХХХ"
	void drawNumbers(SDL_Renderer* renderer, SDL_Texture* texture, int number, int textSize, int x, int y) {
		std::string numbers;

		int i100 = number / 100 % 10;
		numbers += (_0 + i100);

		int i10 = number / 10 % 10;
		numbers += (_0 + i10);

		int i1 = number % 10;
		numbers += (_0 + i1);

		drawText(renderer, texture, numbers, textSize, x, y);
	}

	//Отрисовка текста
	void drawText(SDL_Renderer* renderer, SDL_Texture* texture, std::string text, int textSize, int x, int y) {
		int gap = textSize / 5;

		SDL_Rect pos;
		pos.w = textSize;
		pos.h = textSize * 3/2;
		pos.x = x;
		pos.y = y;

		SDL_Rect src_pos;
		src_pos.w = SRC_WIDTH;
		src_pos.h = SRC_HEIGHT;
		src_pos.y = SRC_HEIGHT;

		for (char c: text) {
			if (c >= _0 && c <= _9) {
				src_pos.y = 0;
				src_pos.x = (c - _0) * src_pos.w;
				SDL_RenderCopy(renderer, texture, &src_pos, &pos);
				pos.x += pos.w + gap;
			}
			if (c >= A && c <= E) {
				src_pos.y = SRC_HEIGHT;
				src_pos.x = (c - A) * src_pos.w;
				SDL_RenderCopy(renderer, texture, &src_pos, &pos);
				pos.x += pos.w + gap;
			}
			if (c > E && c <= IA) {
				c++;
				src_pos.y = SRC_HEIGHT;
				src_pos.x = (c - A) * src_pos.w;
				SDL_RenderCopy(renderer, texture, &src_pos, &pos);
				pos.x += pos.w + gap;
			}
			if (c == SPACE) {
				pos.x += pos.w + gap;
			}
		}
	}
};