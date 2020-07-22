#include "Block.h"
#include "Camera.h"
using namespace std;

const string Block::baseAddress = "assets/sprites/objects/";

Block::Block(BlockType t, double xlo, double ylo, Game* g)
    : pos(xlo, ylo, xlo + cellSize, ylo + cellSize), type(t), game(g) {
    completeAddress();
}

void Block::show(Camera* cam) {
    cam->displayImage(address, pos, game);
}

void Block::completeAddress() {
    address = baseAddress;
    switch (type) {
        case BlockType::normal:        address += "bricks_blocks/block"; break;
        case BlockType::clay:          address += "bricks_blocks/clay";  break;
        case BlockType::flagBody:      address += "flag/body";           break;
        case BlockType::flagHead:      address += "flag/head";           break;
        case BlockType::pipeLeft:      address += "pipe/left";           break;
        case BlockType::pipeRight:     address += "pipe/right";          break;
        case BlockType::pipeHeadLeft:  address += "pipe/head-left";      break;
        case BlockType::pipeHeadRight: address += "pipe/head-right";     break;
    }
    address += ".png";
}

Fourside Block::getPos() {
    return pos;
}

BlockType Block::getType() {
    return type;
}
