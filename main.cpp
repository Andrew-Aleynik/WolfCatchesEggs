#define SDL_MAIN_HANDLED

#include <tchar.h>
#include "GameWindow.h"
#include "NameForm.h"
#include <iostream>
#include <Windows.h>

int main(int argc, char* args[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    //��������� ���������
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(CP_ACP);
    SetConsoleOutputCP(CP_ACP);

    //������������� SDL �������
    SDL_Init(SDL_INIT_EVERYTHING);

    //�������� � ������ ���� � ������ �����
    NameForm form = NameForm();

    return 0;
}
