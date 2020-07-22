#ifndef UTILITY_H
#define UTILITY_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

typedef pair<int, int> Cell;

enum textType {Win, GameOver, Coins, Lives};

enum class Direction {left, right, up, down};
enum class ColliderType {none, mario, block, brick, enemy, greenMushroom, redMushroom, flag};
enum class SoundType {marioJump, gameOver, marioPowerUp, mushroomAppear, win, brickBroken, enemyHit, coinAppear, marioDeath};

class LoseCondition {};
class WinCondition {};

constexpr double EPS = 1e-6;

const char rightChar = 'd';
const char leftChar = 'a';
const char upChar = 'w';

const int cellSize = 48;
const int windowWitdth = 25 * cellSize;
const string windowName = "Super Mario Bros.";

struct Fourside {
    double Xlo, Xhi, Ylo, Yhi;
    Fourside();
    Fourside(double xlo, double ylo, double xhi, double yhi);
};

string intToString (int x);


#endif
