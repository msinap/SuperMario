#include "Brick.h"
#include "Camera.h"
#include "Game.h"
using namespace std;

const string Brick::baseAddress = "assets/sprites/objects/bricks_blocks/";

Brick::Brick(BrickType t, double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + cellSize, ylo + cellSize), type(t), game(g) {
    outOfGame = false;
    downMostHeight = pos.Yhi;
    timeSpentInThisPhase = 0;
    speedY = 0;
    animationPhase = 1;
}

void Brick::show(Camera* cam) {
    if (outOfGame)
        return;
    cam->displayImage(address, pos, game);
}

void Brick::elapse() {
    if (outOfGame)
        return;
    updateMoveArguments();
    updateImageAddress();
}

void Brick::updateMoveArguments() {
    speedY += accelerationY;
    pos.Ylo += speedY;
    pos.Yhi += speedY;

    if (pos.Yhi > downMostHeight) {
        double currentHeight = pos.Yhi - pos.Ylo;
        pos.Yhi = downMostHeight;
        pos.Ylo = pos.Yhi - currentHeight;
        speedY = 0;
    }

    if (abs(speedY) > EPS)
        game->findConjunctions <Brick> (this, ColliderType::brick, pos, Direction::up);
}

void Brick::updateImageAddress() {
    address = baseAddress;
    switch (type) {
        case BrickType::normal:
            address += "brick";
            break;
        case BrickType::emptyQuestion:
            address += "question-empty";
            break;
        default:
            address += "question-";
            if (timeSpentInThisPhase >= 18) {
                animationPhase ++;
                timeSpentInThisPhase = 0;
                if (animationPhase == 4)
                    animationPhase = 1;
            }
            timeSpentInThisPhase ++;
            address += char('0' + animationPhase);
    }
    address += ".png";
}

bool Brick::isCollision(ColliderType t, Fourside colliderPos, Direction side) {
    return (t == ColliderType::enemy);
}

void Brick::hasCollisionWith(ColliderType t, Fourside pos, Direction side) {
    if (t == ColliderType::mario && side == Direction::up)
        hit();
}

void Brick::hit() {
    if (game->getMarioType() == MarioType::normal) {
        speedY = firstSpeedY;
    }else {
        if (type == BrickType::normal) {
            type = BrickType::broken;
            game->getSpeaker()->play(SoundType::brickBroken);
            outOfGame = true;
        }else if(type != BrickType::emptyQuestion){
            speedY = firstSpeedY;
        }
    }

    if (type == BrickType::redQuestion || type == BrickType::greenQuestion) {
        game->constructMushroom(type, pos);
        type = BrickType::emptyQuestion;
    }
    if (type == BrickType::coinQuestion) {
        game->constructCoin(pos);
        type = BrickType::emptyQuestion;
    }
}

BrickType Brick::getType() {
    return type;
}

Fourside Brick::getPos() {
    return pos;
}
