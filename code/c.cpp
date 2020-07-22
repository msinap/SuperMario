#include <bits/stdc++.h>
using namespace std;

#define int long long

int const M = 1e9 + 7;

int seq(int start, int end) {
    cnt = (end - start) % M;
    start %= M;
    end %= M;
    return cnt * ((end + start) / 2) % M;
}

int ans(int n) {
    int sum = 0;

    int firstOdd = 1;
    int firstEven = 2;
    int step = 1;
    bool oddTurn = true;

    while (n > 0) {
        if (oddTurn) {
            int nextOdd;
            if (n >= step) {
                nextOdd = firstOdd + step * 2;
                n -= step;
            }else {
                nextOdd = firstOdd + (n - step) * 2;
                n -= (n - step);
            }
            sum = (sum + seq(firstOdd, nextOdd - 2) ) % M;
            firstOdd = nextOdd;
        }else {
            int nextEven;
            if (n >= step) {
                nextEven = firstEven + step * 2;
                n -= step;
            }else {
                nextEven = firstEven + (n - step) * 2;
                n -= (n - step);
            }
            sum = (sum + seq(firstEven, nextEven - 2) ) % M;
            firstEven = nextEven;
        }

        step *= 2;
        oddTurn = 1 - oddTurn;
    }

    return sum;
}



int32_t main() {
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int l, r;
    cin >> l >> r;
    cout << ( ans(r) - ans(l-1) + M ) % M << '\n';
}
