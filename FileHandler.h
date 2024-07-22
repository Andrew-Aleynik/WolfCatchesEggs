#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>


//Для упрощения работы с файлом
class FileHandler
{
    //Путь к файлу
    const char* filePath;

    //Буфер считанных данных
    char buffer[50];

    //Поток записи
    std::ofstream out;

    //Поток чтения
    std::ifstream in;

    public:
    FileHandler() {
    }

    FileHandler(const char* filePath) {
        if (!std::ifstream(filePath)) {
            std::ofstream file(filePath);
        }
        this->filePath = filePath;

    }

    //Открыть файл для чтения
    void openToRead() {
        if(!out.is_open()) in.open(filePath);
    };

    //Открыть файл для записи
    void openToWrite() {
        if (!in.is_open()) out.open(filePath);
    };

    //Закрыть поток чтения
    void closeRead() {
        in.close();
    }

    //Закрыть поток записи
    void closeWrite() {
        out.close();
    }

    //Считать строку
    char* readLine() {
        if (in.is_open()) in.getline(buffer, 50, '\n');
        return buffer;
    }

    //Записать строку
    void writeLine(const char* str) {
        if (out.is_open()) out << str << "\n";
    }

    //Отчистка памяти
    void clear() {
        delete buffer;
        delete filePath;
    }
};

