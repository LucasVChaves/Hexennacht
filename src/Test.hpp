#include <ncurses.h>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class HD {
public:
    HD(const std::string& filePath) : filePath(filePath) {
        // Initialize ncurses
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();

        // Open the file
        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                buffer.push_back(line);
            }
            file.close();
        }

        // Start the editor loop
        runEditor();
    }

    ~HD() {
        // Clean up ncurses
        endwin();
    }

private:
    std::string filePath;
    std::vector<std::string> buffer;
    int cursorX, cursorY;

    void runEditor() {
        bool running = true;
        while (running) {
            clear();
            displayBuffer();

            int ch = getch();
            switch (ch) {
                case 'q':
                    running = false;
                    break;
                case KEY_UP:
                    moveCursorUp();
                    break;
                case KEY_DOWN:
                    moveCursorDown();
                    break;
                case KEY_LEFT:
                    moveCursorLeft();
                    break;
                case KEY_RIGHT:
                    moveCursorRight();
                    break;
                default:
                    // Handle other key presses
                    break;
            }
        }
    }

    void displayBuffer() {
        for (int i = 0; i < buffer.size(); i++) {
            mvprintw(i, 0, buffer[i].c_str());
        }
        move(cursorY, cursorX);
        refresh();
    }

    void moveCursorUp() {
        if (cursorY > 0) {
            cursorY--;
        }
    }

    void moveCursorDown() {
        if (cursorY < buffer.size() - 1) {
            cursorY++;
        }
    }

    void moveCursorLeft() {
        if (cursorX > 0) {
            cursorX--;
        }
    }

    void moveCursorRight() {
        if (cursorX < buffer[cursorY].size() - 1) {
            cursorX++;
        }
    }
};