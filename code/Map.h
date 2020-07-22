#ifndef MAP_H
#define MAP_H

#include "utility.h"
#include "Block.h"
#include "Brick.h"
#include "Enemy.h"
using namespace std;

enum class Exception {notSameSizeLines, invalidCharachter, noFlags, notOneMario};

class Map {
public:
    Map(string a);
    void readFile();
    void setMaps();
    Cell findMarioFirstCell();
    map<Cell, BlockType> getBlockCells();
    map<Cell, BrickType> getBrickCells();
    map<Cell, EnemyType> getEnemyCells();
    int getRow();
    int getColumn();
protected:
    bool isValid(char ch);

    int row, column;
    vector<vector<char>> charMap;
    map<Cell, BlockType> cellToBlockType;
    map<Cell, BrickType> cellToBrickType;
    map<Cell, EnemyType> cellToEnemyType;

    string address;
    const static vector<char> validChars;
};


#endif
