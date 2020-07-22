#include "Keyboard.h"
#include "Game.h"
using namespace std;

Keyboard::Keyboard() {
}

char Keyboard::getPressedChar(Window* win) {
    flushInputs(win);
    if (lastEvent.get_type() != Event::KEY_PRESS)
        return 0;
    return lastEvent.get_pressed_key();
}

char Keyboard::getReleasedChar(Window* win) {
    flushInputs(win);
    if (lastEvent.get_type() != Event::KEY_RELEASE)
        return 0;
    return lastEvent.get_pressed_key();
}

void Keyboard::flushInputs(Window* win) {
    if (win->has_pending_event())
        lastEvent = win->poll_for_event();
}
