#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>


//��� ��������� ������ � ������
class FileHandler
{
    //���� � �����
    const char* filePath;

    //����� ��������� ������
    char buffer[50];

    //����� ������
    std::ofstream out;

    //����� ������
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

    //������� ���� ��� ������
    void openToRead() {
        if(!out.is_open()) in.open(filePath);
    };

    //������� ���� ��� ������
    void openToWrite() {
        if (!in.is_open()) out.open(filePath);
    };

    //������� ����� ������
    void closeRead() {
        in.close();
    }

    //������� ����� ������
    void closeWrite() {
        out.close();
    }

    //������� ������
    char* readLine() {
        if (in.is_open()) in.getline(buffer, 50, '\n');
        return buffer;
    }

    //�������� ������
    void writeLine(const char* str) {
        if (out.is_open()) out << str << "\n";
    }

    //�������� ������
    void clear() {
        delete buffer;
        delete filePath;
    }
};

