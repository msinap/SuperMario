#include "Map.h"
using namespace std;

const vector<char> Map::validChars = {'.', 'b', '?', 'm', 'h', '@', '#', 'M', 'l', 'k', '|', 'f'};

Map::Map(string a) {
    address = a;
    readFile();
    setMaps();
}

void Map::readFile() {
    ifstream file;
    file.open(address);

    row = 0, column = -1;
    try {
        int flagCount = 0, marioCount = 0;
        string line;
        while (file >> line) {
            if (column == -1) {
                column = line.size();
                for (int i = 0; i < column; i++)
                    charMap.push_back(vector<char>());
            }
            if (column != line.size())
                throw Exception::notSameSizeLines;

            for (int i = 0; i < line.size(); i++) {
                if (!isValid(line[i]))
                    throw Exception::invalidCharachter;
                if (line[i] == 'M')
                    marioCount ++;
                if (line[i] == 'f')
                    flagCount ++;
                charMap[i].push_back(line[i]);
            }
            row ++;
        }
        if (flagCount < 1)
            throw Exception::noFlags;
        if (marioCount != 1)
            throw Exception::notOneMario;
    }catch (Exception e) {
        switch (e) {
            case Exception::notSameSizeLines:
                cerr << "Not Same Size Lines In Map!\n";
                break;
            case Exception::invalidCharachter:
                cerr << "Invalid Charachter In Map!\n";
                break;
            case Exception::notOneMario:
                cerr << "Not One Mario In Map!\n";
                break;
            case Exception::noFlags:
                cerr << "No Flags In Map!\n";
        }
    }

    file.close();
}

void Map::setMaps() {
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            char ch = charMap[i][j];
            Cell cell(i, j);
            switch (ch) {
                case 'b': cellToBrickType[cell] = BrickType::normal;        break;
                case '?': cellToBrickType[cell] = BrickType::coinQuestion;  break;
                case 'm': cellToBrickType[cell] = BrickType::redQuestion;   break;
                case 'h': cellToBrickType[cell] = BrickType::greenQuestion; break;

                case 'l': cellToEnemyType[cell] = EnemyType::gomba;  break;
                case 'k': cellToEnemyType[cell] = EnemyType::troopa; break;

                case '@': cellToBlockType[cell] = BlockType::normal; break;
                case '#': cellToBlockType[cell] = BlockType::clay;   break;
                case 'f':
                    if (charMap[i][j-1] == 'f')
                        cellToBlockType[cell] = BlockType::flagBody;
                    else
                        cellToBlockType[cell] = BlockType::flagHead;
                    break;
                case '|':
                    if (charMap[i][j-1] == '|')
                        if (charMap[i+1][j] == '|')
                            cellToBlockType[cell] = BlockType::pipeLeft;
                        else
                            cellToBlockType[cell] = BlockType::pipeRight;
                    else
                        if (charMap[i+1][j] == '|')
                            cellToBlockType[cell] = BlockType::pipeHeadLeft;
                        else
                            cellToBlockType[cell] = BlockType::pipeHeadRight;
                    break;


            }

        }
    }
}

Cell Map::findMarioFirstCell() {
    Cell marioCell;
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < row; j++) {
            if (charMap[i][j] == 'M') {
                marioCell = Cell(i, j);
                break;
            }
        }
    }
    return marioCell;
}

bool Map::isValid(char ch) {
    for (char valid : validChars)
        if (ch == valid)
            return true;
    return false;
}

int Map::getRow() {
    return row;
}

int Map::getColumn() {
    return column;
}

map<Cell, BlockType> Map::getBlockCells() {
    return cellToBlockType;
}

map<Cell, BrickType> Map::getBrickCells() {
    return cellToBrickType;
}

map<Cell, EnemyType> Map::getEnemyCells() {
    return cellToEnemyType;
}
