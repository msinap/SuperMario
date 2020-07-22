#ifndef PLAYER_H
#define PLAYER_H

#include "utility.h"
using namespace std;

class Camera;
class Game;

class Player {
public:
    Player(string _mapAddress);
    void showText(textType t, Camera* cam);
    void showMessage(textType t, Camera* cam);
    void showHeader(Camera* cam);
    string getMapAddress();
    void decreaseLiveCount();
    void increaseLiveCount();
    void increaseCoinCount();
    int getLiveCount();
    void setGame(Game *g);
protected:
    Game* game;
    int liveCount;
    int coinCount;
    string mapAddress;
    const static string gameOverImageAddress, winImageAddress;
};


#endif
