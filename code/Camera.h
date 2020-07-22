#ifndef CAMERA_H
#define CAMERA_H

#include "../src/rsdl.hpp"
#include "utility.h"
using namespace std;

class Game;

class Camera {
public:
    Camera();
    void elapse(Game* game);
    void displayImage(string address, Fourside fourside, Game* game);
    void displayBackground(string address, int leftPos, Game* game);
    void displayText(string text, int xlo, int ylo, Game* game);
    double getPos();
    void resetPos();
protected:
    double posX;
    const static string fontAddress;
};

#endif
