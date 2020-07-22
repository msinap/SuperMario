#include "Game.h"
using namespace std;

Game::Game(Player* p, Camera* c, Speaker* s, Keyboard* k)
    : cam(c), player(p), speaker(s), keyboard(k), map1(player->getMapAddress()), background(this),
      windowHeight(cellSize * map1.getRow()), win(windowWitdth, windowHeight, windowName) {
    lastConstructedColumn = -1;

    speaker->setWindow(&win);
    speaker->playThemeMusic();
    constructMario();
    constructBlocks();
    constructBricks();
}

void Game::run() {
    while (true){
        constructNewColumns();

        commandMario(keyboard->getPressedChar(&win));
        endCommandMario(keyboard->getReleasedChar(&win));
        elapse();

        win.clear();
        show();

        win.update_screen();
        delay(1000.0 / 120.0);
    }
}

void Game::commandMario(char ch) {
    switch(ch) {
        case rightChar:
            mario.walk(Direction::right);
            break;
        case leftChar:
            mario.walk(Direction::left);
            break;
        case upChar:
            mario.jump();
            break;
    }
}

void Game::endCommandMario(char ch) {
    switch (ch) {
        case rightChar:
        case leftChar:
            mario.stand();
    }
}

void Game::elapse() {
    mario.elapse();
    for (Brick &brick: bricks)
        brick.elapse();
    for (Enemy &enemy: enemies)
        enemy.elapse();
    for (Mushroom &mushroom: mushrooms)
        mushroom.elapse();
    for (Coin &coin: coins)
        coin.elapse();
    cam->elapse(this);
}

void Game::show() {
    background.show(cam);
    for (Block &block: blocks)
        block.show(cam);
    for (Brick &brick: bricks)
        brick.show(cam);
    for (Enemy &enemy: enemies)
        enemy.show(cam);
    for (Mushroom &mushroom: mushrooms)
        mushroom.show(cam);
    for (Coin &coin: coins)
        coin.show(cam);
    mario.show(cam);

    player->showHeader(cam);
}

void Game::constructNewColumns() {
    for (int c = lastConstructedColumn + 1; c < map1.getColumn(); c++) {
        if (c * cellSize <= cam->getPos() + windowWitdth/2 + cellSize) {
            constructEnemyOfColumn(c);
            lastConstructedColumn = c;
        }else{
            break;
        }
    }
}

void Game::constructEnemyOfColumn(int c) {
    map<Cell, EnemyType> cellToEnemyType = map1.getEnemyCells();
    for (int r = 0; r < map1.getRow(); r++) {
        Cell cell(c, r);
        if (cellToEnemyType.find(cell) != cellToEnemyType.end()) {
            enemies.push_back(Enemy(cellToEnemyType[cell], c * cellSize, r * cellSize, this));
        }
    }
}

void Game::constructMario() {
    Cell marioFirstCell = map1.findMarioFirstCell();
    mario = Mario(marioFirstCell.first * cellSize, marioFirstCell.second * cellSize, this);
    mario.setRightMostAvailablePos(map1.getColumn() * cellSize);
}

void Game::constructBlocks() {
    for (pair<Cell, BlockType> x : map1.getBlockCells()) {
        Cell cell = x.first;
        BlockType type = x.second;
        blocks.push_back(Block(type, cell.first * cellSize, cell.second * cellSize, this));
    }
}

void Game::constructBricks() {
    for (pair<Cell, BrickType> x : map1.getBrickCells()) {
        Cell cell = x.first;
        BrickType type = x.second;
        bricks.push_back(Brick(type, cell.first * cellSize, cell.second * cellSize, this));
    }
}

void Game::constructMushroom(BrickType type, Fourside brickPos) {
    if (type == BrickType::redQuestion)
        mushrooms.push_back(Mushroom(MushroomType::red, brickPos.Xlo, brickPos.Ylo - cellSize, this));
    else
        mushrooms.push_back(Mushroom(MushroomType::green, brickPos.Xlo, brickPos.Ylo - cellSize, this));
}

void Game::constructCoin(Fourside brickPos) {
    coins.push_back(Coin(brickPos.Xlo, brickPos.Ylo - cellSize, this));
}

double Game::lengthOfConjonction(Fourside a, Fourside b, Direction sideB) {
    if (sideB == Direction::left || sideB == Direction::right) {
        if (sideB == Direction::left) {
            if (b.Xlo <= a.Xlo || b.Xlo >= a.Xhi)
                return 0.0;
        }else {
            if (b.Xhi <= a.Xlo || b.Xhi >= a.Xhi)
                return 0.0;
        }
        return max(min(a.Yhi - b.Ylo, b.Yhi - a.Ylo), 0.0);
    }else {
        if (sideB == Direction::up) {
            if (b.Ylo <= a.Ylo || b.Ylo >= a.Yhi)
                return 0.0;
        }else {
            if (b.Yhi <= a.Ylo || b.Yhi >= a.Yhi)
                return 0.0;
        }
        return max(min(a.Xhi - b.Xlo, b.Xhi - a.Xlo), 0.0);
    }
}

template <class Object>
void Game::findConjunctions(Object* object, ColliderType type, Fourside pos, Direction side) {
    for (Block &block : blocks) {
        double l = lengthOfConjonction(block.getPos(), pos, side);
        if (l > minConjunction || l > 1 && side == Direction::down) {
            if (block.getType() == BlockType::flagBody || block.getType() == BlockType::flagHead)
                object->isCollision(ColliderType::flag, block.getPos(), side);
            else
                object->isCollision(ColliderType::block, block.getPos(), side);
        }
    }

    for (Brick &brick : bricks) {
        double l = lengthOfConjonction(brick.getPos(), pos, side);
        if (brick.getType() == BrickType::broken)
            continue;
        if (l > minConjunction || l > 1 && side == Direction::down) {
            if (brick.getType() == BrickType::emptyQuestion) {
                object->isCollision(ColliderType::block, brick.getPos(), side);
            }else {
                if (object->isCollision(ColliderType::brick, brick.getPos(), side))
                    brick.hasCollisionWith(type, pos, side);
            }
        }
    }

    for (Enemy &enemy : enemies) {
        double l = lengthOfConjonction(enemy.getPos(), pos, side);
        if (enemy.getType() == EnemyType::gombaDead || enemy.getType() == EnemyType::troopaDead)
            continue;
        if ((l > minConjunction || l > 1 && side == Direction::down) && object->isCollision(ColliderType::enemy, enemy.getPos(), side))
            enemy.hasCollisionWith(type, pos, side);
    }

    for (Mushroom &mushroom : mushrooms) {
        double l = lengthOfConjonction(mushroom.getPos(), pos, side);
        if (mushroom.getType() == MushroomType::eaten)
            continue;
        if (l > minConjunction || l > 1 && side == Direction::down) {
            if (mushroom.getType() == MushroomType::red) {
                if (object->isCollision(ColliderType::redMushroom, mushroom.getPos(), side))
                    mushroom.hasCollisionWith(type, pos, side);
            }else {
                if (object->isCollision(ColliderType::greenMushroom, mushroom.getPos(), side))
                    mushroom.hasCollisionWith(type, pos, side);
            }
        }
    }
}

Mario* Game::getMario() {
    return &mario;
}

Background* Game::getBackground() {
    return &background;
}

MarioType Game::getMarioType() {
    return mario.getType();
}

Window* Game::getWindow() {
    return &win;
}

int Game::getWindowHeight() {
    return windowHeight;
}

Player* Game::getPlayer() {
    return player;
}

Speaker* Game::getSpeaker() {
    return speaker;
}





void temporaryFunction() {
    Camera c;
    Speaker s;
    Keyboard k;
    Player p("");
    Game g(&p, &c, &s, &k);
    Mario m(0, 0, &g);
    Brick b(BrickType::normal, 0, 0, &g);
    Enemy e(EnemyType::gomba, 0, 0, &g);
    Mushroom r(MushroomType::red, 0, 0, &g);
    g.findConjunctions <Mario> (&m, ColliderType::mario, Fourside(), Direction::left);
    g.findConjunctions <Enemy> (&e, ColliderType::mario, Fourside(), Direction::left);
    g.findConjunctions <Brick> (&b, ColliderType::mario, Fourside(), Direction::left);
    g.findConjunctions <Mushroom> (&r, ColliderType::mario, Fourside(), Direction::left);
}
