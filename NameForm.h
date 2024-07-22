#pragma once
#define SDL_MAIN_HANDLED

#include "Text.h"
#include "Button.h"
#include <SDL.h>

//Окно ввода имени
class NameForm
{
    //Окно
    SDL_Window* window;

    //Название окна
    const char* WINDOW_TITLE = "Wolf catches eggs";

    //Позиция окна
    const static int SCREEN_POS_X = 100;
    const static int SCREEN_POS_Y = 100;

    //Размеры окна
    const static int SCREEN_WIDTH = 400;
    const static int SCREEN_HEIGHT = 250;

    //FPS
    const static int FPS = 15;

    //Нужно ли закрыть окно?
    bool toClose = false;

    //Для отрисовки текста
    Text text;

    //Текстура текста
    SDL_Texture* textTexture;

    //Рззмер текста
    int TEXT_SIZE = 10;

    //Положение надписи "Введите свое имя"
    int LABEL_X = 20;
    int LABEL_Y = 40;

    //Имя игрока
    std::string name;

    //Положение имени
    int TEXT_X = 20;
    int TEXT_Y = 80;

    //Рендерер
    SDL_Renderer* renderer;

    //Фон
    SDL_Texture* backgroundTexture;

    //Кнопка, ее положение и размеры
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

    //Текстуры не нажатой и нажатой кнопок
    SDL_Texture* rectangleBtnTexture;
    SDL_Texture* rectanglePressedBtnTexture;

    //Создание окна, если случилась ошибка при создании, то возвращает 1
    bool createWindow() {
        window = SDL_CreateWindow(WINDOW_TITLE, SCREEN_POS_X, SCREEN_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            return 1;
        }
        return 0;
    }

    //Создание рендерера, если случилась ошибка при создании, то возвращает 1
    bool createRenderer() {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer == nullptr) {
            return 1;
        }
        return 0;
    }

    //Создание текстур из заготовленых картинок
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

    //Отрисовка кнопок
    void drawButtons() {
        okBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        text.drawText(renderer, textTexture, "ок", TEXT_SIZE,
            OK_BTN_X + OK_BTN_WIDTH / 2 - TEXT_SIZE,
            OK_BTN_Y + OK_BTN_HEIGHT / 2 - TEXT_SIZE
        );
    }
    
    //Отрисовка фона
    void drawBackground() {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    //Отрисовка надписи и имени
    void drawTextes() {
        text.drawText(renderer, textTexture, "смените раскладку на английскую", TEXT_SIZE, LABEL_X, 10);
        text.drawText(renderer, textTexture, "введите имя минимум 2 символа", TEXT_SIZE, LABEL_X, LABEL_Y);
        text.drawText(renderer, textTexture, name, TEXT_SIZE * 2, TEXT_X, TEXT_Y);
    }

    //Отрисовка окна
    void draw() {
        SDL_RenderClear(renderer);
        drawBackground();
        drawTextes();
        drawButtons();

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / FPS);
    }

    //Считывание событий нажатий кнопок и обновление значений переменных
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

    //Перевод из латиницы в кирилицу
    char toCyrylic(char c) {
        switch (c) {
        case 'q': return 'й';
        case 'w': return 'ц';
        case 'e': return 'у';
        case 'r': return 'к';
        case 't': return 'е';
        case 'y': return 'н';
        case 'u': return 'г';
        case 'i': return 'ш';
        case 'o': return 'щ';
        case 'p': return 'з';
        case '[': return 'х';
        case ']': return 'ъ';
        case 'a': return 'ф';
        case 's': return 'ы';
        case 'd': return 'в';
        case 'f': return 'а';
        case 'g': return 'п';
        case 'h': return 'р';
        case 'j': return 'о';
        case 'k': return 'л';
        case 'l': return 'д';
        case ';': return 'ж';
        case '\'': return 'э';
        case 'э': return 'э';
        case 'z': return 'я';
        case 'x': return 'ч';
        case 'c': return 'с';
        case 'v': return 'м';
        case 'b': return 'и';
        case 'n': return 'т';
        case 'm': return 'ь';
        case ',': return 'б';
        case '.': return 'ю';
        }
    }

    public:
    //Конструктор
    NameForm() {
        createWindow();
        createRenderer();
        createTextures();

        okBtn = Button(OK_BTN_X, OK_BTN_Y, OK_BTN_WIDTH, OK_BTN_HEIGHT);
        text = Text();

        run();
    }

    //Освобождение текстур и закрытие окна
    void close() {
        SDL_DestroyTexture(textTexture);

        SDL_DestroyTexture(backgroundTexture);

        SDL_DestroyTexture(rectangleBtnTexture);
        SDL_DestroyTexture(rectanglePressedBtnTexture);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);


        toClose = true;
    }

    //Запуск окна
    void run() {
        while (!toClose) {
            update();
            draw();
        }
    }
};

