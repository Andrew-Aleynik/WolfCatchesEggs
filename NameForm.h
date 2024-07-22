#pragma once
#define SDL_MAIN_HANDLED

#include "Text.h"
#include "Button.h"
#include <SDL.h>

//���� ����� �����
class NameForm
{
    //����
    SDL_Window* window;

    //�������� ����
    const char* WINDOW_TITLE = "Wolf catches eggs";

    //������� ����
    const static int SCREEN_POS_X = 100;
    const static int SCREEN_POS_Y = 100;

    //������� ����
    const static int SCREEN_WIDTH = 400;
    const static int SCREEN_HEIGHT = 250;

    //FPS
    const static int FPS = 15;

    //����� �� ������� ����?
    bool toClose = false;

    //��� ��������� ������
    Text text;

    //�������� ������
    SDL_Texture* textTexture;

    //������ ������
    int TEXT_SIZE = 10;

    //��������� ������� "������� ���� ���"
    int LABEL_X = 20;
    int LABEL_Y = 40;

    //��� ������
    std::string name;

    //��������� �����
    int TEXT_X = 20;
    int TEXT_Y = 80;

    //��������
    SDL_Renderer* renderer;

    //���
    SDL_Texture* backgroundTexture;

    //������, �� ��������� � �������
    Button okBtn;
    int OK_BTN_X = 40;
    int OK_BTN_Y = 160;
    int OK_BTN_WIDTH = 320;
    int OK_BTN_HEIGHT = 60;
    void okBtnAction() {
        if (name.size() >= 2) {
            this->close();
            GameWindow game = GameWindow(name);
        }
    }

    //�������� �� ������� � ������� ������
    SDL_Texture* rectangleBtnTexture;
    SDL_Texture* rectanglePressedBtnTexture;

    //�������� ����, ���� ��������� ������ ��� ��������, �� ���������� 1
    bool createWindow() {
        window = SDL_CreateWindow(WINDOW_TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            return 1;
        }
        return 0;
    }

    //�������� ���������, ���� ��������� ������ ��� ��������, �� ���������� 1
    bool createRenderer() {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            return 1;
        }
        return 0;
    }

    //�������� ������� �� ������������ ��������
    void createTextures() {
        SDL_Surface* backgroundBMP = SDL_LoadBMP("assets/background_white.bmp");
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundBMP);
        SDL_FreeSurface(backgroundBMP);

        SDL_Surface* textBMP = SDL_LoadBMP("assets/text.bmp");
        textTexture = SDL_CreateTextureFromSurface(renderer, textBMP);
        SDL_FreeSurface(textBMP);

        SDL_Surface* rectangleBtnBMP = SDL_LoadBMP("assets/rectangle_btn.bmp");
        SDL_Surface* rectanglePressedBtnBMP = SDL_LoadBMP("assets/rectangle_pressed_btn.bmp");
        rectangleBtnTexture = SDL_CreateTextureFromSurface(renderer, rectangleBtnBMP);
        rectanglePressedBtnTexture = SDL_CreateTextureFromSurface(renderer, rectanglePressedBtnBMP);
        SDL_FreeSurface(rectangleBtnBMP);
        SDL_FreeSurface(rectanglePressedBtnBMP);
    }

    //��������� ������
    void drawButtons() {
        okBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        text.drawText(renderer, textTexture, "��", TEXT_SIZE,
            OK_BTN_X + OK_BTN_WIDTH / 2 - TEXT_SIZE,
            OK_BTN_Y + OK_BTN_HEIGHT / 2 - TEXT_SIZE
        );
    }
    
    //��������� ����
    void drawBackground() {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    //��������� ������� � �����
    void drawTextes() {
        text.drawText(renderer, textTexture, "������� ��������� �� ����������", TEXT_SIZE, LABEL_X, 10);
        text.drawText(renderer, textTexture, "������� ��� ������� 2 �������", TEXT_SIZE, LABEL_X, LABEL_Y);
        text.drawText(renderer, textTexture, name, TEXT_SIZE * 2, TEXT_X, TEXT_Y);
    }

    //��������� ����
    void draw() {
        SDL_RenderClear(renderer);
        drawBackground();
        drawTextes();
        drawButtons();

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / FPS);
    }

    //���������� ������� ������� ������ � ���������� �������� ����������
    void update() {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                this->close();
            }

            if (e.type == SDL_TEXTINPUT) {
                name += toCyrylic(*e.text.text);
            }

            if (e.type == SDL_KEYDOWN)
            {
                if (!name.empty() && e.key.keysym.sym == SDLK_BACKSPACE) {
                    name.pop_back();
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    okBtnAction();
                    okBtn.press();
                }
            }

            if (e.type == SDL_KEYUP) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    okBtn.release();
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                if (okBtn.inRect(x, y)) {
                    okBtnAction();
                    okBtn.press();
                }
            }


            if (e.type == SDL_MOUSEBUTTONUP) {
                okBtn.release();
            }
        }
    }

    //������� �� �������� � ��������
    char toCyrylic(char c) {
        switch (c) {
        case 'q': return '�';
        case 'w': return '�';
        case 'e': return '�';
        case 'r': return '�';
        case 't': return '�';
        case 'y': return '�';
        case 'u': return '�';
        case 'i': return '�';
        case 'o': return '�';
        case 'p': return '�';
        case '[': return '�';
        case ']': return '�';
        case 'a': return '�';
        case 's': return '�';
        case 'd': return '�';
        case 'f': return '�';
        case 'g': return '�';
        case 'h': return '�';
        case 'j': return '�';
        case 'k': return '�';
        case 'l': return '�';
        case ';': return '�';
        case '\'': return '�';
        case '�': return '�';
        case 'z': return '�';
        case 'x': return '�';
        case 'c': return '�';
        case 'v': return '�';
        case 'b': return '�';
        case 'n': return '�';
        case 'm': return '�';
        case ',': return '�';
        case '.': return '�';
        }
    }

    public:
    //�����������
    NameForm() {
        createWindow();
        createRenderer();
        createTextures();

        okBtn = Button(OK_BTN_X, OK_BTN_Y, OK_BTN_WIDTH, OK_BTN_HEIGHT);
        text = Text();

        run();
    }

    //������������ ������� � �������� ����
    void close() {
        SDL_DestroyTexture(textTexture);

        SDL_DestroyTexture(backgroundTexture);

        SDL_DestroyTexture(rectangleBtnTexture);
        SDL_DestroyTexture(rectanglePressedBtnTexture);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);


        toClose = true;
    }

    //������ ����
    void run() {
        while (!toClose) {
            update();
            draw();
        }
    }
};

