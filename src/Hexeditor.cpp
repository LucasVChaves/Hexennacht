#include "Hexeditor.hpp"
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

Hexeditor::Hexeditor(const std::string &filePath)
    : filePath(filePath), cursorPos(0), mode(Mode::NORMAL) {
  std::cout << "Initializing Hexeditor..." << std::endl;
  loadFile();
}

Hexeditor::~Hexeditor() {}

void Hexeditor::run() {
  while (true) {
    display();
    handleInput();
  }
}

void Hexeditor::loadFile() {
  std::ifstream file(filePath, std::ios::binary);
  if (file) {
    buffer = std::vector<char>((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
  } else {
    std::cerr << "ERROR: Could not open file" << std::endl;
  }
}

void Hexeditor::saveFile() {
  std::ofstream file(filePath, std::ios::binary);
  if (file) {
    file.write(buffer.data(), buffer.size());
  }
}

void Hexeditor::display() {
  system("clear");
  size_t start = cursorPos / 16 * 16;
  size_t end = start * 16 * 10;

  for (size_t i = start; i < end && i < buffer.size(); ++i) {
    if (i % 16 == 0) {
      std::cout << std::endl;
    }
    std::cout << std::hex << (unsigned int)(unsigned char)buffer[i] << " ";
  }

  std::cout << "\n\nCursor: " << cursorPos
            << "  Mode: " << (mode == Mode::NORMAL ? "NORMAL" : "INSERT")
            << std::endl;
}

void Hexeditor::handleInput() {
  char input = std::cin.get();

  if (mode == Mode::NORMAL) {
    handleNormalMode(input);
  } else if (mode == Mode::INSERT) {
    handleInsertMode(input);
  }
}

void Hexeditor::handleNormalMode(char input) {
  switch (input) {
  case 'q':
    saveFile();
    exit(0);
  case 'h':
    if (cursorPos > 0) {
      --cursorPos;
    }
    break;
  case 'l':
    if (cursorPos < buffer.size() - 1) {
      ++cursorPos;
    }
    break;
  case 'j':
    if (cursorPos + 16 < buffer.size()) {
      cursorPos += 16;
    }
    break;
  case 'k':
    if (cursorPos >= 16) {
      cursorPos -= 16;
    }
    break;
  case 'g':
    cursorPos = 0;
    break;
  case 'G':
    cursorPos = buffer.size() - 1;
    break;
  case 'i':
    mode = Mode::INSERT;
    break;
  default:
    break;
  }
}

void Hexeditor::handleInsertMode(char input) {
  if (input == '\x1b') {
    mode = Mode::NORMAL;
  } else {
    editByte(input);
  }
}

void Hexeditor::editByte(char input) {
  std::cout << "Edit byte (current: " << std::hex
            << (unsigned int)(unsigned char)buffer[cursorPos] << "): ";
  int newByte;
  std::cin >> std::hex >> newByte;
  buffer[cursorPos] = static_cast<char>(newByte);
  mode = Mode::NORMAL;
}
