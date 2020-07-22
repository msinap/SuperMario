#ifndef COIN_H
#define COIN_H

#include "utility.h"
using namespace std;

class Game;
class Camera;

class Coin {
public:
    Coin(double xlo, double ylo, Game* g);
    void show(Camera* cam);
    void elapse();
protected:
    void updateMoveArguments();

    Game* game;
    Fourside pos;
    double speedY, downMostHeight;
    bool outOfGame;

    const static string address;
    constexpr static double accelerationY = 0.23, firstSpeedY = -6;
};

#endif
