#ifndef MARIO_H
#define MARIO_H

#include "utility.h"
using namespace std;

class Camera;
class Game;

enum class MarioType {normal, big};

class Mario {
public:
    Mario();
    Mario(double xlo, double ylo, Game* g);
    void walk(Direction dir);
    void jump();
    void stand();
    void elapse();
    void show(Camera* cam);
    void handleCollisions();
    bool isCollision(ColliderType t, Fourside colliderPos, Direction side);
    void setLeftMostAvailablePos(double newValue);
    void setRightMostAvailablePos(double newValue);
    Fourside getPos();
    MarioType getType();

protected:
    void updateMoveArguments();
    void updateImageAddress();
    void updateOutofLeftMostPos();
    void updateOutofRightMostPos();

    Game* game;
    MarioType type;
    Fourside pos;
    double speedX, speedY, lastSpeedX;
    double accelerationX;
    double leftMostAvailablePos, rightMostAvailablePos;
    int animationWalkingPhase, timeSpentInThisPhase, timeSpentInWalking;
    int shieldTimeRemaining;
    string imageAddress;

    const static int normalHeight = cellSize, normalWidth = cellSize * 3 / 4, bigHeight = normalHeight * 2, bigWidth = normalWidth * 7 / 6;
    const static int shieldTime = 300;
    constexpr static double firstAccelerationX = 0.06, accelerationY = 0.23, friction = 0.03;
    constexpr static double firstSpeedY = -10, maxSpeedX = 3.5, lowSpeedX = 0.25, firstSpeedYAfterCollidingEnemy = -3;
    const static string baseAddress;
};


#endif
