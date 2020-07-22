#include "Enemy.h"
#include "Camera.h"
#include "Game.h"
using namespace std;

const string Enemy::baseAddress = "assets/sprites/enemies/";

Enemy::Enemy(EnemyType t, double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + cellSize, ylo + cellSize), type(t), game(g) {

    if (type == EnemyType::troopa) {
        pos.Ylo = pos.Yhi - troopaNormalHeight;
    }
    outOfGame = false;
    timeSpentDying = timeSpentInThisPhase = 0;
    animationPhase = 1;

    speedX = firstSpeedX;
}

void Enemy::show(Camera* cam) {
    if (outOfGame)
        return;
    cam->displayImage(address, pos, game);
}

void Enemy::elapse() {
    if (outOfGame)
        return;
    updateMoveArguments();
    updateImageAddress();
}

void Enemy::updateMoveArguments() {
    speedY += accelerationY;
    pos.Xlo += speedX;
    pos.Xhi += speedX;
    pos.Ylo += speedY;
    pos.Yhi += speedY;

    handleCollisions();
    if (pos.Ylo > game->getWindowHeight())
        outOfGame = true;
}

void Enemy::handleCollisions() {
    game->findConjunctions <Enemy> (this, ColliderType::enemy, pos, Direction::down);
    game->findConjunctions <Enemy> (this, ColliderType::enemy, pos, Direction::right);
    game->findConjunctions <Enemy> (this, ColliderType::enemy, pos, Direction::left);
}

void Enemy::updateImageAddress() {
    address = baseAddress;
    switch (type) {
        case EnemyType::gomba:
            address += "little_goomba/walking-";
            timeSpentInThisPhase ++;
            if (timeSpentInThisPhase >= phaseShowTime) {
                timeSpentInThisPhase = 0;
                animationPhase ++;
                if (animationPhase == 3)
                    animationPhase = 1;
            }
            address += char('0' + animationPhase);
            break;
        case EnemyType::gombaDead:
            address += "little_goomba/dead";
            timeSpentDying ++;
            if (timeSpentDying >= dyingTime)
                outOfGame = true;
            break;

        case EnemyType::troopa:
            address += "koopa_troopa/walking-";
            if (speedX >= 0)
                address += "right-";
            else
                address += "left-";
            timeSpentInThisPhase ++;
            if (timeSpentInThisPhase >= phaseShowTime) {
                timeSpentInThisPhase = 0;
                animationPhase ++;
                if (animationPhase == 3)
                    animationPhase = 1;
            }
            address += char('0' + animationPhase);
            break;
        case EnemyType::troopaDead:
            timeSpentDying ++;
            if (timeSpentDying >= dyingTime)
                outOfGame = true;
        case EnemyType::troopaSemiDead:
        case EnemyType::troopaSemiDeadStatic:
            address += "koopa_troopa/dead";
            break;
    }
    address += ".png";
}

bool Enemy::isCollision(ColliderType t, Fourside colliderPos, Direction side) {
    if (t != ColliderType::block && t != ColliderType::brick)
        return false;
    double currentWidth = pos.Xhi - pos.Xlo;
    double currentHeight = pos.Yhi - pos.Ylo;

    switch (side) {
        case Direction::down:
            pos.Yhi = colliderPos.Ylo;
            pos.Ylo = pos.Yhi - currentHeight;
            speedY = 0;
            return true;
        case Direction::left:
            pos.Xlo = colliderPos.Xhi;
            pos.Xhi = pos.Xlo + currentWidth;
            speedX *= -1;
            return true;
        case Direction::right:
            pos.Xhi = colliderPos.Xlo;
            pos.Xlo = pos.Xhi - currentWidth;
            speedX *= -1;
            return true;
    }
}

void Enemy::hasCollisionWith(ColliderType t, Fourside colliderPos, Direction side) {
    switch (t) {
        case ColliderType::mario:
            if (side == Direction::down)
                die(colliderPos);
            break;
        case ColliderType::brick:
            if (side == Direction::up)
                die(colliderPos);
            break;
    }
}

void Enemy::die(Fourside colliderPos) {
    game->getSpeaker()->play(SoundType::enemyHit);
    double currentHeight = pos.Yhi - pos.Ylo;
    switch (type) {
        case EnemyType::gomba:
            type = EnemyType::gombaDead;
            speedX = 0;
            break;
        case EnemyType::troopa:
            type = EnemyType::troopaSemiDeadStatic;
            pos.Ylo = pos.Yhi - troopaSemiDeadHeight;
            speedX = 0;
            break;
        case EnemyType::troopaSemiDeadStatic:
            type = EnemyType::troopaSemiDead;
            speedX = (colliderPos.Xlo < pos.Xlo ? 1 : -1) * firstSpeedXTroopaSemiDead;
            break;
        case EnemyType::troopaSemiDead:
            type = EnemyType::troopaDead;
            speedX = 0;
            break;
    }
}

Fourside Enemy::getPos() {
    return pos;
}

EnemyType Enemy::getType() {
    return type;
}
