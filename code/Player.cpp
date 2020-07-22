#include "Player.h"
#include "Game.h"
#include "Camera.h"
using namespace std;

const string Player::winImageAddress = "assets/win.jpg";
const string Player::gameOverImageAddress = "assets/game_over.jpg";

Player::Player(string _mapAddress) {
    liveCount = 3;
    coinCount = 0;
    mapAddress = _mapAddress;
}

void Player::showText(textType t, Camera* cam) {
    string textString;
    int xlo, ylo;

    switch (t) {
        case textType::Coins:
            xlo = ylo = 20;
            textString += "Coins: " + intToString(coinCount);
            break;
        case textType::Lives:
            xlo = 300;
            ylo = 20;
            textString += "Lives: " + intToString(liveCount);
            break;
    }
    cam->displayText(textString, xlo, ylo, game);
}

void Player::showHeader(Camera* cam) {
    showText(textType::Coins, cam);
    showText(textType::Lives, cam);
}

void Player::showMessage(textType t, Camera* cam) {
    game->getWindow()->clear();
    cam->resetPos();
    string address = (t == textType::GameOver ? gameOverImageAddress : winImageAddress);
    Window win(1200, 720, "Message");
    win.draw_img(address);
    win.update_screen();
    delay(1500);
}

string Player::getMapAddress() {
    return mapAddress;
}

void Player::decreaseLiveCount() {
    liveCount --;
}

void Player::increaseLiveCount() {
    liveCount ++;
}

void Player::increaseCoinCount() {
    coinCount ++;
}

int Player::getLiveCount() {
    return liveCount;
}

void Player::setGame(Game* g) {
    game = g;
}
