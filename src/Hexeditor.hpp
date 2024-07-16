#ifndef HEXEDITOR_HPP
#define HEXEDITOR_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>

enum class Mode {
    NORMAL,
    INSERT
};

class Hexeditor {
public:
    Hexeditor(const std::string &filePath);
    ~Hexeditor();

    void run();

private:
    std::string filePath;
    std::vector<char> buffer;
    size_t cursorPos;
    Mode mode;

    void loadFile();
    void saveFile();

    void display();
    void handleInput();
    void handleNormalMode(char input);
    void handleInsertMode(char input);
    void editByte(char input);
};

#endif // HEXEDITOR_HPP
