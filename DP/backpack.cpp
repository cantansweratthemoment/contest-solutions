/**
 * Дано n предметов массой m1, ..., mn и стоимостью c1, ..., cn соответственно.
 * Ими наполняют рюкзак, который выдерживает вес не более m. Определите набор предметов, который можно унести в рюкзаке, имеющий наибольшую стоимость.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

signed main() {
    meow
    int m, n;
    cin >> n >> m;
    vector<int> weights;
    vector<int> c;
    repeat(i, n) {
        int weight;
        cin >> weight;
        weights.push_back(weight);
    }
    repeat(i, n) {
        int ci;
        cin >> ci;
        c.push_back(ci);
    }
    vector<vector<int>> f;
    f.resize(n + 1);
    repeat(i, n + 1) {
        f[i].resize(m + 1, 0);
    }
    repeat(i, n + 1) {
        f[i][0] = 0;
    }
    for (int w = 0; w < m + 1; w++) {
        for (int i = 1; i < n + 1; i++) {
            f[i][w] = f[i - 1][w];
            if (w - weights[i - 1] >= 0) {
                f[i][w] = max(f[i - 1][w - weights[i - 1]] + c[i - 1], f[i][w]);
            }
        }
    }
    /*repeat(i, n) {
        repeat(j, m + 1) {
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }*/
    int gold = INT_MIN;
    int goldI = 0;
    int goldJ = 0;
    for (int i = n; i >= 0; i--) {
        for (int j = m; j >= 0; j--) {
            if (f[i][j] > gold) {
                gold = f[i][j];
                goldI = i;
                goldJ = j;
            }
        }
    }
    //cout << gold;
    //return 0;
    set<int> bag;
    while (goldI > 0 && goldJ >= 0) {
        if (f[goldI][goldJ] == 0) {
            break;
        }
        if (f[goldI - 1][goldJ] != f[goldI][goldJ]) {
            bag.insert(goldI);
            goldJ = goldJ - weights[goldI - 1];
        }
        goldI--;
    }
    cout << bag.size() << "\n";
    for (auto element: bag) {
        cout << element << " ";
    }
}