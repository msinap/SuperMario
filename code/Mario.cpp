#include "Mario.h"
#include "Camera.h"
#include "Speaker.h"
#include "Game.h"
using namespace std;

const string Mario::baseAddress = "assets/sprites/mario/";

Mario::Mario() {}

Mario::Mario(double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + normalWidth, ylo + normalHeight), game(g) {
    type = MarioType::normal;
    speedX = speedY = lastSpeedX = 0.0;
    accelerationX = 0.0;
    animationWalkingPhase = 1;
    timeSpentInThisPhase = 0;
    shieldTimeRemaining = 0;
}

void Mario::walk(Direction dir) {
    switch (dir) {
        case Direction::left:
            accelerationX = -firstAccelerationX;
            if (abs(speedX) < lowSpeedX)
                speedX -= lowSpeedX;
            break;
        case Direction::right:
            accelerationX = firstAccelerationX;
            if (abs(speedX) < lowSpeedX)
                speedX += lowSpeedX;
            break;
    }
}

void Mario::stand() {
    accelerationX = 0;
}

void Mario::jump() {
    if (speedY != 0)
        return;
    game->getSpeaker()->play(SoundType::marioJump);
    speedY = firstSpeedY;
    speedX *= 1.5;
    if (abs(speedX) < lowSpeedX)
        speedX *= 2;
}

void Mario::elapse() {
    updateMoveArguments();
    updateImageAddress();
    if (shieldTimeRemaining > 0)
        shieldTimeRemaining --;
}

void Mario::updateMoveArguments() {
    speedX += accelerationX;
    if (abs(speedY - 0.0) < EPS) {
        if (speedX > 0) {
            speedX = max(speedX - friction, 0.0);
        }else if(speedX < 0) {
            speedX = min(speedX + friction, 0.0);
        }
    }
    if (speedX > maxSpeedX)
        speedX = maxSpeedX;
    if (speedX < -maxSpeedX)
        speedX = -maxSpeedX;

    speedY += accelerationY;
    pos.Xlo += speedX;
    pos.Xhi += speedX;
    pos.Ylo += speedY;
    pos.Yhi += speedY;

    if (pos.Xlo <= leftMostAvailablePos)
        updateOutofLeftMostPos();
    if (pos.Xhi >= rightMostAvailablePos)
        updateOutofRightMostPos();

    handleCollisions();

    if (speedX != 0)
        lastSpeedX = speedX;

    if (pos.Ylo > game->getWindowHeight()) {
        game->getSpeaker()->play(SoundType::marioDeath);
        throw LoseCondition();
    }
}

void Mario::handleCollisions() {
    game->findConjunctions <Mario> (this, ColliderType::mario, pos, Direction::down);
    game->findConjunctions <Mario> (this, ColliderType::mario, pos, Direction::up);
    game->findConjunctions <Mario> (this, ColliderType::mario, pos, Direction::right);
    game->findConjunctions <Mario> (this, ColliderType::mario, pos, Direction::left);
}

bool Mario::isCollision(ColliderType t, Fourside colliderPos, Direction side) {
    double currentWidth = pos.Xhi - pos.Xlo;
    double currentHeight = pos.Yhi - pos.Ylo;
    switch (t) {
        case ColliderType::brick:
        case ColliderType::block:
            switch (side) {
                case Direction::down:
                    pos.Yhi = colliderPos.Ylo;
                    pos.Ylo = pos.Yhi - currentHeight;
                    speedY = min(speedY, 0.0);
                    return true;
                case Direction::up:
                    pos.Ylo = colliderPos.Yhi;
                    pos.Yhi = pos.Ylo + currentHeight;
                    speedY *= -0.25;
                    return true;
                case Direction::right:
                    pos.Xhi = colliderPos.Xlo;
                    pos.Xlo = pos.Xhi - currentWidth;
                    if (speedX != 0)
                        lastSpeedX = speedX;
                    speedX = min(speedX, 0.0);
                    return true;
                case Direction::left:
                    pos.Xlo = colliderPos.Xhi;
                    pos.Xhi = pos.Xlo + currentWidth;
                    if (speedX != 0)
                        lastSpeedX = speedX;
                    speedX = max(speedX, 0.0);
                    return true;
            }
        case ColliderType::flag:
            game->getSpeaker()->play(SoundType::win);
            throw WinCondition();
            return false;
        case ColliderType::enemy:
            if (shieldTimeRemaining > 0)
                return false;
            switch (side) {
                case Direction::down:
                    pos.Yhi = colliderPos.Ylo;
                    pos.Ylo = pos.Yhi - currentHeight;
                    speedY = firstSpeedYAfterCollidingEnemy;
                    return true;
                default:
                    if (type == MarioType::normal){
                        game->getSpeaker()->play(SoundType::marioDeath);
                        throw LoseCondition();
                    }else {
                        type = MarioType::normal;
                        currentHeight = pos.Yhi - pos.Ylo;
                        currentWidth = pos.Xhi - pos.Xlo;
                        currentHeight = normalHeight;
                        currentWidth = normalWidth;
                        pos.Ylo = pos.Yhi - currentHeight;
                        pos.Xlo = pos.Xhi - currentWidth;
                        shieldTimeRemaining = shieldTime;
                    }

                    return false;
            }
        case ColliderType::redMushroom:
            if (type == MarioType::normal) {
                game->getSpeaker()->play(SoundType::marioPowerUp);
                type = MarioType::big;
                currentHeight = pos.Yhi - pos.Ylo;
                currentWidth = pos.Xhi - pos.Xlo;
                currentHeight = bigHeight;
                currentWidth = bigWidth;
                pos.Ylo = pos.Yhi - currentHeight;
                pos.Xlo = pos.Xhi - currentWidth;
            }
            return true;
        case ColliderType::greenMushroom:
            return true;
    }
}

void Mario::updateOutofLeftMostPos() {
    double currentWidth = pos.Xhi - pos.Xlo;
    double currentHeight = pos.Yhi - pos.Ylo;
    speedX = 0;
    pos.Xlo = max(pos.Xlo, leftMostAvailablePos);
    pos.Xhi = pos.Xlo + currentWidth;
}

void Mario::updateOutofRightMostPos() {
    double currentWidth = pos.Xhi - pos.Xlo;
    double currentHeight = pos.Yhi - pos.Ylo;
    speedX = 0;
    pos.Xhi = min(pos.Xhi, rightMostAvailablePos);
    pos.Xlo = pos.Xhi - currentWidth;

}

void Mario::updateImageAddress() {
    imageAddress = baseAddress + (type == MarioType::normal ? "normal/" : "big/");
    if (abs(speedY - 0.0) < EPS) {
        if (abs(speedX - 0.0) < EPS) {
            imageAddress += "standing-";
            imageAddress += (lastSpeedX >= 0 ? "right" : "left");
        }else if(accelerationX * speedX < 0){
            imageAddress += "sliding-";
            if (speedX > 0)
                imageAddress += "right";
            else
                imageAddress += "left";
        }else {
            imageAddress += "walking-";
            if (speedX > 0) {
                imageAddress += "right-";
            }else if(speedX < 0) {
                imageAddress += "left-";
            }else {
                imageAddress += (lastSpeedX >= 0 ? "right-" : "left-");
            }
            timeSpentInThisPhase ++;
            if (timeSpentInThisPhase >= 14) {
                animationWalkingPhase ++;
                if (animationWalkingPhase == 4)
                    animationWalkingPhase = 1;
                timeSpentInThisPhase = 0;
            }
            imageAddress += char('0' + animationWalkingPhase);
        }
    }else {
        imageAddress += "jumping-";
        if (speedX > 0) {
            imageAddress += "right";
        }else if(speedX < 0){
            imageAddress += "left";
        }else {
            imageAddress += (lastSpeedX >= 0 ? "right" : "left");
        }
    }
    imageAddress += ".png";
}

void Mario::show(Camera* cam) {
    if (shieldTimeRemaining % 2 == 0)
        cam->displayImage(imageAddress, pos, game);
}

Fourside Mario::getPos() {
    return pos;
}

MarioType Mario::getType() {
    return type;
}

void Mario::setLeftMostAvailablePos(double newValue) {
    leftMostAvailablePos = newValue;
}

void Mario::setRightMostAvailablePos(double newValue) {
    rightMostAvailablePos = newValue;
}
