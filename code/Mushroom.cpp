#include "Mushroom.h"
#include "Camera.h"
#include "Speaker.h"
#include "Game.h"
using namespace std;

const string Mushroom::baseAddress = "assets/sprites/objects/mushroom/";

Mushroom::Mushroom(MushroomType t, double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + cellSize, ylo + cellSize), type(t), game(g) {

    outOfGame = false;
    speedX = firstSpeedX;
    address = baseAddress + (type == MushroomType::red ? "red" : "health") + ".png";
    game->getSpeaker()->play(SoundType::mushroomAppear);
}

void Mushroom::show(Camera* cam) {
    if (outOfGame)
        return;
    cam->displayImage(address, pos, game);
}

void Mushroom::elapse() {
    if (outOfGame)
        return;
    updateMoveArguments();
}

void Mushroom::updateMoveArguments() {
    speedY += accelerationY;
    pos.Xlo += speedX;
    pos.Xhi += speedX;
    pos.Ylo += speedY;
    pos.Yhi += speedY;

    handleCollisions();
    if (pos.Ylo > game->getWindowHeight())
        outOfGame = true;
}

void Mushroom::handleCollisions() {
    if (type == MushroomType::red) {
        game->findConjunctions <Mushroom> (this, ColliderType::redMushroom, pos, Direction::down);
        game->findConjunctions <Mushroom> (this, ColliderType::redMushroom, pos, Direction::right);
        game->findConjunctions <Mushroom> (this, ColliderType::redMushroom, pos, Direction::left);
    }else {
        game->findConjunctions <Mushroom> (this, ColliderType::greenMushroom, pos, Direction::down);
        game->findConjunctions <Mushroom> (this, ColliderType::greenMushroom, pos, Direction::right);
        game->findConjunctions <Mushroom> (this, ColliderType::greenMushroom, pos, Direction::left);
    }
}

bool Mushroom::isCollision(ColliderType t, Fourside colliderPos, Direction side) {
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

void Mushroom::hasCollisionWith(ColliderType t, Fourside colliderPos, Direction side) {
    if (t != ColliderType::mario)
        return;
    if (type == MushroomType::green)
        game->getPlayer()->increaseLiveCount();
    outOfGame = true;
    type = MushroomType::eaten;
}

Fourside Mushroom::getPos() {
    return pos;
}

MushroomType Mushroom::getType() {
    return type;
}
