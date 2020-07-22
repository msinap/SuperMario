#ifndef BLOCK_H
#define BLOCK_H

#include "utility.h"
using namespace std;

class Game;
class Camera;

enum class BlockType {normal, clay, flagBody, flagHead, pipeLeft, pipeRight, pipeHeadLeft, pipeHeadRight};

class Block {
public:
    Block(BlockType t, double xlo, double ylo, Game* g);
    void show(Camera* cam);
    Fourside getPos();
    BlockType getType();
protected:
    void completeAddress();
    Game *game;
    BlockType type;
    Fourside pos;
    string address;
    const static string baseAddress;
};


#endif
