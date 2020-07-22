#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../src/rsdl.hpp"
using namespace std;

class Game;

class Keyboard {
public:
    Keyboard();
    char getPressedChar(Window* win);
    char getReleasedChar(Window* win);
protected:
    void flushInputs(Window* win);
    Game* game;
    Event lastEvent;
};

#endif
