#include "utility.h"
using namespace std;

Fourside::Fourside(double xlo, double ylo, double xhi, double yhi)
    : Xlo(xlo), Ylo(ylo), Xhi(xhi), Yhi(yhi) {}

Fourside::Fourside() {}

string intToString (int x) {
    string ret = "";
    while (x) {
        ret += char(x % 10 + '0');
        x /= 10;
    }
    for (int i = 0; i < ret.size()/2 ;i++)
        swap(ret[i], ret[ret.size()-i-1]);
    if (ret.size() == 0)
        ret += '0';
    return ret;
}
