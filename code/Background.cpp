#include "Background.h"
#include "Camera.h"
using namespace std;

Background::Background(Game* g)
    : game(g) {
    leftPosLo = 0;
    leftPosHi = width;
}

void Background::show(Camera* cam) {
    if (shouldMakeNextBackgroundImage(cam->getPos()))
        makeNextImage();
    cam->displayBackground(address, leftPosLo, game);
    cam->displayBackground(address, leftPosHi, game);
}

bool Background::shouldMakeNextBackgroundImage(int camPosX) {
    int rightPosLo = leftPosLo + Background::width;
    return rightPosLo < camPosX - windowWitdth / 2;
}

void Background::makeNextImage() {
    leftPosLo = leftPosHi;
    leftPosHi += width;
}
