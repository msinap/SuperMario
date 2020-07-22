#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "utility.h"
using namespace std;

class Camera;
class Game;

class Background {
public:
    Background(Game* g);
    void show(Camera* cam);

    const static int width = 2000;
    const static int height = 1000;
private:
    void makeNextImage();
    bool shouldMakeNextBackgroundImage(int camPosX);

    Game *game;
    int leftPosLo, leftPosHi;
    const string address = "assets/background_image.png";
};






#endif
