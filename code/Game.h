#ifndef GAME_H
#define GAME_H

#include "../src/rsdl.hpp"
#include "utility.h"
#include "Player.h"
#include "Camera.h"
#include "Keyboard.h"
#include "Speaker.h"
#include "Background.h"
#include "Map.h"
#include "Mario.h"
#include "Block.h"
#include "Brick.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "Coin.h"
using namespace std;

class Game {
public:
    Game(Player* p, Camera* c, Speaker* s, Keyboard* k);
    void run();
    template <class Object> void findConjunctions(Object* object, ColliderType type, Fourside pos, Direction side);
    void constructMushroom(BrickType type, Fourside Brickpos);
    void constructCoin(Fourside Brickpos);
    Window* getWindow();
    Speaker* getSpeaker();
    Mario* getMario();
    Player* getPlayer();
    MarioType getMarioType();
    Background* getBackground();
    int getWindowHeight();
protected:
    void elapse();
    void show();
    void constructMario();
    void constructBlocks();
    void constructBricks();
    void constructNewColumns();
    void constructEnemyOfColumn(int c);
    void commandMario(char ch);
    void endCommandMario(char ch);
    double lengthOfConjonction(Fourside a, Fourside b, Direction sideB);

    Player* player;
    Camera* cam;
    Map map1;
    int windowHeight;
    Window win;
    Keyboard* keyboard;
    Speaker *speaker;
    Background background;

    Mario mario;
    vector<Block> blocks;
    vector<Brick> bricks;
    vector<Enemy> enemies;
    vector<Mushroom> mushrooms;
    vector<Coin> coins;

    int lastConstructedColumn;
    constexpr static double minConjunction = 8;
};


#endif
