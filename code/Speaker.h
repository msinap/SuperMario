#ifndef SPEAKER_H
#define SPEAKER_H

#include "../src/rsdl.hpp"
#include "utility.h"

class Speaker {
public:
    Speaker();
    void play(SoundType s);
    void setWindow(Window* w);
    void playThemeMusic();
private:
    Window* win;

    const static string baseAddress, themeMusicAddress;
};






#endif
