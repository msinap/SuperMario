#ifndef BRICK_H
#define BRICK_H

#include "utility.h"
using namespace std;

class Game;
class Camera;

enum class BrickType {normal, redQuestion, greenQuestion, coinQuestion, emptyQuestion, broken};

class Brick {
public:
    Brick(BrickType t, double xlo, double ylo, Game* g);
    void show(Camera* cam);
    void elapse();
    bool isCollision(ColliderType t, Fourside colliderPos, Direction side);
    void hasCollisionWith(ColliderType t, Fourside pos, Direction side);
    Fourside getPos();
    BrickType getType();
protected:
    void hit();
    void updateImageAddress();
    void updateMoveArguments();

    Game *game;
    BrickType type;
    Fourside pos;
    string address;
    double speedY, downMostHeight;
    int animationPhase, timeSpentInThisPhase;
    bool outOfGame;

    const static string baseAddress;
    constexpr static double accelerationY = 0.23, firstSpeedY = -2;
};


#endif
