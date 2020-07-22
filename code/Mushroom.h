#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "utility.h"
using namespace std;

class Camera;
class Game;

enum class MushroomType {green, red, eaten};

class Mushroom {
public:
    Mushroom(MushroomType t, double xlo, double ylo, Game* g);
    void show(Camera* cam);
    void elapse();
    void hasCollisionWith(ColliderType t, Fourside pos, Direction side);
    bool isCollision(ColliderType t, Fourside colliderPos, Direction side);
    Fourside getPos();
    MushroomType getType();
protected:
    void updateMoveArguments();
    void handleCollisions();

    Game *game;
    MushroomType type;
    Fourside pos;
    string address;
    double speedX, speedY;
    bool outOfGame;

    const static string baseAddress;
    constexpr static double firstSpeedX = 1, accelerationY = 0.23;
};

#endif
