#pragma once
#define SDL_MAIN_HANDLED

#include "Text.h"
#include "Button.h"
#include <SDL.h>
#include <list>

//���� � ��������
class LeadersWindow
{
    //����
    SDL_Window* window;

    //�������� ����
    const char* WINDOW_TITLE = "Leaders";

    //������� ����
    const static int SCREEN_POS_X = 100;
    const static int SCREEN_POS_Y = 100;

    //������� ����
    const static int SCREEN_WIDTH = 400;
    const static int SCREEN_HEIGHT = 600;

    //FPS
    const static int FPS = 15;

    //���� ����� �������?
    bool toClose = false;

    //��� ��������� ������
    Text text;

    //�������� ������
    SDL_Texture* textTexture;

    //������ � ��������� ��������� ������
    const static int TEXT_SIZE = 14;
    const static int TEXT_X = 40;
    const static int TEXT_Y = 80;

    //��������
    SDL_Renderer* renderer;

    //���
    SDL_Texture* backgroundTexture;

    //������� �� ������� � ������� �������
    SDL_Texture* rectangleBtnTexture;
    SDL_Texture* rectanglePressedBtnTexture;

    //������, �� ��������� � �������
    Button okBtn;
    const static int OK_BTN_X = 40;
    const static int OK_BTN_Y = 500;
    const static int OK_BTN_WIDTH = 320;
    const static int OK_BTN_HEIGHT = 60;
    void okBtnAction() {
        this->close();
    }
    
    //������
    std::list<Player> leaders;

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

    //��������� ����
    void drawBackground() {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    //��������� ������
    void drawButtons() {
        okBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        text.drawText(renderer, textTexture, "��", TEXT_SIZE,
            OK_BTN_X + OK_BTN_WIDTH / 2 - TEXT_SIZE,
            OK_BTN_Y + OK_BTN_HEIGHT / 2 - TEXT_SIZE
        );
    }

    //��������� �������
    void drawLeaders() {
        int x = TEXT_X;
        int y = TEXT_Y;
        for (Player leader : leaders) {
            text.drawText(renderer, textTexture, leader.getName(), TEXT_SIZE, x, y);
            text.drawNumbers(renderer, textTexture, leader.getScore(), TEXT_SIZE, x + 250, y);
            y += 40;
        }
    }

    //��������� ����
    void draw() {
        SDL_RenderClear(renderer);
        drawBackground();
        drawLeaders();
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
                close();
            }

            if (e.type == SDL_KEYDOWN)
            {
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

    public:
    //�����������
    LeadersWindow(std::list<Player> leaders) {
        createWindow();
        createRenderer();
        createTextures();

        this->leaders = leaders;

        okBtn = Button(OK_BTN_X, OK_BTN_Y, OK_BTN_WIDTH, OK_BTN_HEIGHT);
        text = Text();

        run();
    }

    //�������� ����
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

