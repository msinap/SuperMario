#include "Camera.h"
#include "Game.h"
using namespace std;

const string Camera::fontAddress = "assets/FreeSans.ttf";

Camera::Camera() {
    resetPos();
}

void Camera::displayImage(string address, Fourside fourside, Game* game) {
    double onScreenXlo = fourside.Xlo - posX + windowWitdth/2;
    double width = fourside.Xhi - fourside.Xlo;

    if (onScreenXlo > windowWitdth || onScreenXlo + width < 0)
        return;

    game->getWindow()->draw_img(address, Rectangle(onScreenXlo, fourside.Ylo, fourside.Xhi - fourside.Xlo, fourside.Yhi - fourside.Ylo));
}

void Camera::displayBackground(string address, int leftPos, Game* game) {
    game->getWindow()->draw_img(address, Rectangle(leftPos - posX + windowWitdth/2, 0, Background::width, game->getWindowHeight()),
                                Rectangle(0, 0, Background::width, Background::height));
}

void Camera::displayText(string text, int xlo, int ylo, Game* game) {
    game->getWindow()->show_text(text, Point(xlo, ylo), RGB(255, 255, 255), fontAddress, 36);
}

void Camera::elapse(Game* game) {
    posX = max(posX, game->getMario()->getPos().Xlo);
    game->getMario()->setLeftMostAvailablePos(posX - windowWitdth / 2);
}

double Camera::getPos() {
    return posX;
}

void Camera::resetPos() {
    posX = windowWitdth / 2;
}
