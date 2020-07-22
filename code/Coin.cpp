#include "Coin.h"
#include "Camera.h"
#include "Speaker.h"
#include "Game.h"
using namespace std;

const string Coin::address = "assets/sprites/objects/coin.png";

Coin::Coin(double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + cellSize, ylo + cellSize), game(g) {
    game->getPlayer()->increaseCoinCount();
    outOfGame = false;
    downMostHeight = pos.Yhi;
    speedY = firstSpeedY;
    game->getSpeaker()->play(SoundType::coinAppear);
}

void Coin::show(Camera* cam) {
    if (outOfGame)
        return;
    cam->displayImage(address, pos, game);
}

void Coin::elapse() {
    if (outOfGame)
        return;
    updateMoveArguments();
}

void Coin::updateMoveArguments() {
    speedY += accelerationY;
    pos.Ylo += speedY;
    pos.Yhi += speedY;

    if (pos.Yhi > downMostHeight) {
        outOfGame = true;
    }
}
