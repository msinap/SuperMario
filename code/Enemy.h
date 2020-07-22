#ifndef ENEMY_H
#define ENEMY_H

#include "utility.h"
using namespace std;

class Camera;
class Game;

enum class EnemyType {gomba, troopa, troopaSemiDead, troopaSemiDeadStatic, troopaDead, gombaDead};

class Enemy {
public:
    Enemy(EnemyType t, double xlo, double ylo, Game* g);
    void show(Camera* cam);
    void elapse();
    bool isCollision(ColliderType t, Fourside colliderPos, Direction side);
    void hasCollisionWith(ColliderType t, Fourside pos, Direction side);
    Fourside getPos();
    EnemyType getType();

protected:
    void die(Fourside colliderPos);
    void updateImageAddress();
    void updateMoveArguments();
    void handleCollisions();

    Game* game;
    EnemyType type;
    Fourside pos;
    string address;
    int animationPhase, timeSpentInThisPhase, timeSpentDying;
    double speedX, speedY;
    bool outOfGame;

    const static string baseAddress;
    constexpr static double firstSpeedX = -1, accelerationY = 0.23, firstSpeedXTroopaSemiDead = 4;
    const static int dyingTime = 30, phaseShowTime = 9;
    const static int troopaNormalHeight = cellSize * 3 / 2, troopaSemiDeadHeight = cellSize * 3 / 4;
};




#endif
