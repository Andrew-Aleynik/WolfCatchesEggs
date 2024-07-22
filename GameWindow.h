#pragma once
#define SDL_MAIN_HANDLED

#include "Wolf.h"
#include "Egg.h"
#include "Text.h"
#include "Button.h"
#include "Player.h"
#include "FileHandler.h"
#include "LeadersWindow.h"
#include "Sound.h"

#include <SDL.h>
#include <SDL_audio.h>
#include <random>
#include <list>

//Окно игры
class GameWindow
{
    //Окно
    SDL_Window* window;

    //Название окна
    const char* WINDOW_TITLE = "Wolf catches eggs";

    //Позиция окна
    const static int SCREEN_POS_X = 100;
    const static int SCREEN_POS_Y = 100;

    //Размеры окна
    const static int SCREEN_WIDTH = 1080;
    const static int SCREEN_HEIGHT = 682;

    //FPS
    const static int FPS = 15;

    //Игра не на паузе?
    bool isRunning = true;

    //Окно нужно закрыть?
    bool toClose = false;

    //Рендерер
    SDL_Renderer* renderer;

    //Волк
    Wolf wolf;
    SDL_Texture* wolfTextures[4];

    //Максимальное количество яиц
    const static int MAX_COUNT_EGGS = 8;

    //Яйца
    Egg eggs[MAX_COUNT_EGGS];

    //Текстура катящегося яйца
    SDL_Texture* eggTexture;

    //Текстура разбившегося яйца
    SDL_Texture* crackedEggTexture;


    //Время междду появлением яиц
    int timeBetweenEggs = 20;
    int timer = 0;

    //Счёт
    int maxScore;
    int score;

    //Размер и положение счёта на экране
    const static int SCORE_SIZE = 30;
    const static int SCORE_X = 500;
    const static int SCORE_Y = 200;

    //Размер и положение надписи "Пауза" на экране
    const static int PAUSE_SIZE = 15;
    const static int PAUSE_X = 500;
    const static int PAUSE_Y = 270;


    //Жизни
    const static int MAX_HEALTH = 3;
    int health = MAX_HEALTH;

    //Размер и положение жизней на экране
    const int HEALTH_WIDTH = 18;
    const int HEALTH_HEIGHT = 22;
    const int HEALTH_X = 370;
    const int HEALTH_Y = 200;

    //Расстояние между жизнями
    const int HEALTH_GAP = 10;

    //Фон
    SDL_Texture* backgroundTexture;

    //Игрок
    Player player;

    //Лидеры
    std::list<Player> leaders;

    //Размеры прямоугольных кнопок
    const int BTN_WIDTH = 72;
    const int BTN_HEIGHT = 27;

    //Текстуры не нажатой и нажатой прямоугольных кнопок
    SDL_Texture* rectangleBtnTexture;
    SDL_Texture* rectanglePressedBtnTexture;

    //Диаметр круглых кнопок
    const static int BTN_DIAMETER = 75;

    //Текстуры не нажатой и нажатой круглых кнопок
    SDL_Texture* roundBtnTexture;
    SDL_Texture* roundPressedBtnTexture;

    //Спецификация воспроизведения аудио (моно, стерео и т.п.)
    SDL_AudioSpec wavSpec;
    //Устройство, которое проигрывает аудио
    SDL_AudioDeviceID deviceId;

    //Звуки
    Sound tickSnd;
    Sound scoreSnd;
    Sound crackSnd;
    Sound loseSnd;

    //Кнопки и их положение на экране
    Button soundBtn;
    const int SOUND_BTN_X = 68;
    const int SOUND_BTN_Y = 60;
    bool isSoundPaused = false;
    void soundBtnAction() {
        if (!isSoundPaused) {
            SDL_PauseAudioDevice(deviceId, 1);
            SDL_ClearQueuedAudio(deviceId);
            isSoundPaused = true;
        }
        else {
            SDL_ClearQueuedAudio(deviceId);
            SDL_PauseAudioDevice(deviceId, 0);
            isSoundPaused = false;
        }
    }

    Button leadersBtn;
    const int LEADERS_BTN_X = 68;
    const int LEADERS_BTN_Y = 122;
    void leadersBtnAction() {
        pause();
        LeadersWindow leadersWindow = LeadersWindow(leaders);
    }

    Button exitBtn;
    const int EXIT_BTN_X = 68;
    const int EXIT_BTN_Y = 181;
    void exitBtnAction() {
        isRunning = false;
        close();
    }

    Button pauseBtn;
    const int PAUSE_BTN_X = 937;
    const int PAUSE_BTN_Y = 181;
    void pauseBtnAction() {
        if (isRunning) {
            pause();
        }
        else {
            resume();
        }
    }
    
    Button qBtn;
    const int Q_BTN_X = 69;
    const int Q_BTN_Y = 414;
    void qBtnAction() {
        if (isRunning) wolf.setPosition(UP_LEFT);
    }

    Button aBtn;
    const int A_BTN_X = 69;
    const int A_BTN_Y = 539;
    void aBtnAction() {
        if (isRunning) wolf.setPosition(DOWN_LEFT);
    }

    Button pBtn;
    const int P_BTN_X = 929;
    const int P_BTN_Y = 420;
    void pBtnAction() {
        if (isRunning) wolf.setPosition(UP_RIGHT);
    }

    Button lBtn;
    const int L_BTN_X = 929;
    const int L_BTN_Y = 540;
    void lBtnAction() {
        if (isRunning) wolf.setPosition(DOWN_RIGHT);
    }

    //Для работы с файлом
    FileHandler fileHandler;
    const char* FILE_PATH = "leaders.txt";

    //Для отрисовки текста
    Text text;

    //Текстура текста
    SDL_Texture* textTexture;

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
        SDL_Surface* backgroundBMP = SDL_LoadBMP("assets/background.bmp");
        backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundBMP);
        SDL_FreeSurface(backgroundBMP);

        SDL_Surface* eggBMP = SDL_LoadBMP("assets/egg.bmp");
        SDL_Surface* crackedEggBMP = SDL_LoadBMP("assets/cracked_egg.bmp");
        eggTexture = SDL_CreateTextureFromSurface(renderer, eggBMP);
        crackedEggTexture = SDL_CreateTextureFromSurface(renderer, crackedEggBMP);
        SDL_FreeSurface(eggBMP);
        SDL_FreeSurface(crackedEggBMP);

        SDL_Surface* wolf_u_l = SDL_LoadBMP("assets/wolf_u_l.bmp");
        SDL_Surface* wolf_u_r = SDL_LoadBMP("assets/wolf_u_r.bmp");
        SDL_Surface* wolf_d_l = SDL_LoadBMP("assets/wolf_d_l.bmp");
        SDL_Surface* wolf_d_r = SDL_LoadBMP("assets/wolf_d_r.bmp");
        wolfTextures[0] = SDL_CreateTextureFromSurface(renderer, wolf_u_l);
        wolfTextures[1] = SDL_CreateTextureFromSurface(renderer, wolf_u_r);
        wolfTextures[2] = SDL_CreateTextureFromSurface(renderer, wolf_d_l);
        wolfTextures[3] = SDL_CreateTextureFromSurface(renderer, wolf_d_r);
        SDL_FreeSurface(wolf_u_l);
        SDL_FreeSurface(wolf_u_r);
        SDL_FreeSurface(wolf_d_l);
        SDL_FreeSurface(wolf_d_r);

        SDL_Surface* textBMP = SDL_LoadBMP("assets/text.bmp");
        textTexture = SDL_CreateTextureFromSurface(renderer, textBMP);
        SDL_FreeSurface(textBMP);

        SDL_Surface* rectangleBtnBMP = SDL_LoadBMP("assets/rectangle_btn.bmp");
        SDL_Surface* rectanglePressedBtnBMP = SDL_LoadBMP("assets/rectangle_pressed_btn.bmp");
        rectangleBtnTexture = SDL_CreateTextureFromSurface(renderer, rectangleBtnBMP);
        rectanglePressedBtnTexture = SDL_CreateTextureFromSurface(renderer, rectanglePressedBtnBMP);
        SDL_FreeSurface(rectangleBtnBMP);
        SDL_FreeSurface(rectanglePressedBtnBMP);

        SDL_Surface* roundBtnBMP = SDL_LoadBMP("assets/round_btn.bmp");
        SDL_Surface* roundPressedBtnBMP = SDL_LoadBMP("assets/round_pressed_btn.bmp");
        roundBtnTexture = SDL_CreateTextureFromSurface(renderer, roundBtnBMP);
        roundPressedBtnTexture = SDL_CreateTextureFromSurface(renderer, roundPressedBtnBMP);
        SDL_FreeSurface(roundBtnBMP);
        SDL_FreeSurface(roundPressedBtnBMP);
    }

    //Получение стандартного устройства вывода звука
    void createAudioDevice() {
        deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    }

    //Создание звуков из заготовок
    void createSounds() {
        tickSnd = Sound("assets/sounds/tick.wav", wavSpec);
        scoreSnd = Sound("assets/sounds/score.wav", wavSpec);
        crackSnd = Sound("assets/sounds/crack.wav", wavSpec);
        loseSnd = Sound("assets/sounds/lose.wav", wavSpec);
    }

    //Отрисовка фона
    void drawBackground() {
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    //Отрисовка яиц
    void drawEggs() {
        for (Egg egg : eggs) {
            egg.draw(renderer, eggTexture, crackedEggTexture);
        }
    }

    //Отрисовка волка
    void drawWolf() {
        wolf.draw(renderer, wolfTextures);
    }

    //Отрисовка счета и жизней
    void drawScoresAndHealth() {
        text.drawNumbers(renderer, textTexture, score, SCORE_SIZE, SCORE_X, SCORE_Y);

        SDL_Rect pos;
        pos.x = HEALTH_X;
        pos.y = HEALTH_Y;
        pos.w = HEALTH_WIDTH;
        pos.h = HEALTH_HEIGHT;
        for (int i = 0; i < health; i++) {
            SDL_RenderCopy(renderer, eggTexture, NULL, &pos);
            pos.x += HEALTH_WIDTH + HEALTH_GAP;
        }
    }

    //Отрисовка кнопок
    void drawButtons() {
        soundBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        leadersBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        exitBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);
        pauseBtn.draw(renderer, rectangleBtnTexture, rectanglePressedBtnTexture);

        qBtn.draw(renderer, roundBtnTexture, roundPressedBtnTexture);
        aBtn.draw(renderer, roundBtnTexture, roundPressedBtnTexture);
        pBtn.draw(renderer, roundBtnTexture, roundPressedBtnTexture);
        lBtn.draw(renderer, roundBtnTexture, roundPressedBtnTexture);
    }

    //Отрисовка надписи "Пауза", если игра на паузе
    void drawPause() {
        if (!isRunning) {
            text.drawText(renderer, textTexture, "пауза", PAUSE_SIZE, PAUSE_X, PAUSE_Y);
        }
    }

    //Отрисовка окна
    void draw() {
        SDL_RenderClear(renderer);

        drawBackground();
        drawEggs();
        drawWolf();
        drawScoresAndHealth();
        drawButtons();
        drawPause();

        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / FPS);
    }

    //Перезапуск игры
    void restart() {
        maxScore = max(maxScore, score);
        score = 0;
        save();
        health = MAX_HEALTH;
        for (int i = 0; i < MAX_COUNT_EGGS; i++) {
            eggs[i].restart(rand() % 4);
            eggs[i].resetStageTime();
        }

        timeBetweenEggs = 20;
    }

    //Считывание событий нажатий кнопок и обновление значений переменных
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
                switch (e.key.keysym.sym) {
                case SDLK_p:
                    pBtnAction();
                    pBtn.press();
                    break;
                case SDLK_l:
                    lBtnAction();
                    lBtn.press();
                    break;
                case SDLK_q:
                    qBtnAction();
                    qBtn.press();
                    break;
                case SDLK_a:
                    aBtnAction();
                    aBtn.press();
                    break;
                case SDLK_SPACE:
                    pauseBtnAction();
                    pauseBtn.press();
                }
            }

            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_p:
                    pBtn.release();
                    break;
                case SDLK_l:
                    lBtn.release();
                    break;
                case SDLK_q:
                    qBtn.release();
                    break;
                case SDLK_a:
                    aBtn.release();
                    break;
                case SDLK_SPACE:
                    pauseBtn.release();
                }
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                if (soundBtn.inRect(x, y)) {
                    soundBtnAction();
                    soundBtn.press();
                }
                if (exitBtn.inRect(x, y)) {
                    exitBtnAction();
                    exitBtn.press();
                }
                if (leadersBtn.inRect(x, y)) {
                    leadersBtnAction();
                    leadersBtn.press();
                }
                if (pauseBtn.inRect(x, y)) {
                    pauseBtnAction();
                    pauseBtn.press();
                }

                if (qBtn.inRect(x, y)) {
                    qBtnAction();
                    qBtn.press();
                }
                if (aBtn.inRect(x, y)) {
                    aBtnAction();
                    aBtn.press();
                }
                if (pBtn.inRect(x, y)) {
                    pBtnAction();
                    pBtn.press();
                }
                if (lBtn.inRect(x, y)) {
                    lBtnAction();
                    lBtn.press();
                }
            }

            if (e.type == SDL_MOUSEBUTTONUP) {
                soundBtn.release();
                exitBtn.release();
                leadersBtn.release();
                pauseBtn.release();
                qBtn.release();
                aBtn.release();
                pBtn.release();
                lBtn.release();
            }
        }

        if (isRunning) {
            timer++;
            if (timer > timeBetweenEggs) {
                timer = 0;
                for (int i = 0; i < MAX_COUNT_EGGS; i++) {
                    if (!eggs[i].isMoving()) {
                        eggs[i].start();
                        break;
                    }
                }
                tickSnd.play(deviceId);
            }

            for (int i = 0; i < MAX_COUNT_EGGS; i++) {
                eggs[i].increaseStage();
                if (eggs[i].getPosition() == wolf.getPosition() && eggs[i].getStage() == 4) {

                    scoreSnd.play(deviceId);

                    score++;
                    eggs[i].restart(rand() % 4);
                    if (score % 10 == 0) increaseSpeed(1);
                    if (score == 200 || score == 500) {
                        health = MAX_HEALTH;
                        increaseSpeed(-5);
                    }
                    if (score == 999) {
                        maxScore = 999;
                    }
                    if (score == 1000) {
                        score = 0;
                    }
                }
                if (eggs[i].getStage() > 6) {
                    eggs[i].restart(rand() % 4);
                    health--;

                    increaseSpeed(-10);

                    crackSnd.play(deviceId);
                }
            }
        }

        if (health <= 0) {
            loseSnd.play(deviceId);
            restart();
        }
    }

    //Загрузка данных о лидерах из файла
    void load() {
        fileHandler.openToRead();
        char* str = fileHandler.readLine();
        while (str[0] != '\0') {
            char _0 = '0';
            char a = 'а';
            std::string name;
            int scr = 0;
            for (char c = *str; c; c = *++str) {
                if (c != '#') name += c;
                else {
                    *str++;
                    break;
                }
            }

            int digit = 100;
            for (char c = *str; c; c = *++str) {
                scr += (c - _0) * digit;
                digit /= 10;
            }

            if(leaders.size() < 10) leaders.push_back(Player(name, scr));
            str = fileHandler.readLine();
        }
        fileHandler.closeRead();
    }

    //Сохранение данных о лидерах в файл
    void save() {
        maxScore = max(maxScore, score);
        player.setScore(maxScore);
        leaders.push_back(player);
        leaders.sort();
        fileHandler.openToWrite();
        for (Player p : leaders) {
            fileHandler.writeLine(p.toString().c_str());
        }
        fileHandler.closeWrite();
    }

    int max(int left, int right) {
        if (left > right) return left;
        else return right;
    }

    public:
    //Конструктор
    GameWindow(std::string name) {
        createWindow();
        createRenderer();
        createTextures();

        createAudioDevice();
        createSounds();

        text = Text();
        wolf = Wolf(renderer);
        srand(time(NULL));
        for (int i = 0; i < MAX_COUNT_EGGS; i++) {
            eggs[i] = Egg(rand() % 4);
        }
        score = 0;
        player = Player(name);
        fileHandler = FileHandler(FILE_PATH);
        leaders = std::list<Player>();

        soundBtn = Button(SOUND_BTN_X, SOUND_BTN_Y, BTN_WIDTH, BTN_HEIGHT);
        leadersBtn = Button(LEADERS_BTN_X, LEADERS_BTN_Y, BTN_WIDTH, BTN_HEIGHT);
        exitBtn = Button(EXIT_BTN_X, EXIT_BTN_Y, BTN_WIDTH, BTN_HEIGHT);
        pauseBtn = Button(PAUSE_BTN_X, PAUSE_BTN_Y, BTN_WIDTH, BTN_HEIGHT);

        qBtn = Button(Q_BTN_X, Q_BTN_Y, BTN_DIAMETER, BTN_DIAMETER);
        aBtn = Button(A_BTN_X, A_BTN_Y, BTN_DIAMETER, BTN_DIAMETER);
        pBtn = Button(P_BTN_X, P_BTN_Y, BTN_DIAMETER, BTN_DIAMETER);
        lBtn = Button(L_BTN_X, L_BTN_Y, BTN_DIAMETER, BTN_DIAMETER);

        SDL_PauseAudioDevice(deviceId, 0);

        load();

        run();
    }

    //Освобождение текстур из памяти, закрытие окна и отчистка ранее инициализированной SDL системы
    void close() {
        save();
        for (int i = 0; i < 4; i++) {
            SDL_DestroyTexture(wolfTextures[i]);
        }
        SDL_DestroyTexture(crackedEggTexture);
        SDL_DestroyTexture(eggTexture);

        SDL_DestroyTexture(textTexture);

        SDL_DestroyTexture(backgroundTexture);

        SDL_DestroyTexture(rectangleBtnTexture);
        SDL_DestroyTexture(rectanglePressedBtnTexture);

        SDL_DestroyTexture(roundBtnTexture);
        SDL_DestroyTexture(roundPressedBtnTexture);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
        toClose = true;
    }

    //Запуск окна
    void run() {
        while (!toClose) {
            update();
            draw();
        }
    }

    //Пауза
    void pause() {
        isRunning = false;
    }

    //Продолжение
    void resume() {
        isRunning = true;
    }

    //Увеличить скорость игры
    void increaseSpeed(int delta) {
        for (int i = 0; i < MAX_COUNT_EGGS; i++) {
            eggs[i].decreaseStageTime(delta);
        }
        if(timeBetweenEggs > 8 || delta < 0) timeBetweenEggs -= delta;
    }
};