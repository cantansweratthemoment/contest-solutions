/**
 * Найдите максимальный вес золота, который можно унести в рюкзаке вместительностью S, если есть n золотых слитков с заданными весами.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

signed main() {
    meow
    int S, n;
    cin >> S >> n;
    vector<int> weights;
    repeat(i, n) {
        int weight;
        cin >> weight;
        weights.push_back(weight);
    }
    vector<vector<int>> f;
    f.resize(n);
    repeat(i, n) {
        f[i].resize(S + 1, 0);
    }
    repeat(i, n) {
        if (weights[i] <= S) {
            f[i][weights[i]] = 1;
        }
        f[i][0] = 1;
    }
    for (int w = 0; w < S + 1; w++) {
        for (int i = 1; i < n; i++) {
            if (f[i - 1][w]) {
                f[i][w] = 1;
            }
            if (w - weights[i] >= 0) {
                if (f[i - 1][w - weights[i]]) {
                    f[i][w] = 1;
                }
            }
        }
    }
    for (int w = S; w >= 0; w--) {
        repeat(i, n) {
            if (f[i][w]) {
                cout << w;
                return 0;
            }
        }
    }
}