/**
 * Назовём натуральное число плавным, если разность любых двух его соседних цифр не превосходит по модулю единицы.
 * Определите количество N-значных плавных чисел. Запись числа не может начинаться с цифры 0.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

const int N = 10;

signed main() {
    meow
    int n;
    cin >> n;
    vector<int> horse0 = {0, 1};
    vector<int> horse1 = {0, 1, 2};
    vector<int> horse2 = {1, 2, 3};
    vector<int> horse3 = {2, 3, 4};
    vector<int> horse4 = {3, 4, 5};
    vector<int> horse5 = {4, 5, 6};
    vector<int> horse6 = {5, 6, 7};
    vector<int> horse7 = {6, 7, 8};
    vector<int> horse8 = {7, 8, 9};
    vector<int> horse9 = {8, 9};
    vector<vector<int>> horses = {horse0, horse1, horse2, horse3, horse4, horse5, horse6, horse7, horse8, horse9};
    vector<vector<int>> f(N);
    repeat(i, N) {
        f[i].resize(n, 0);
    }
    f[0][0] = 0;
    repeat(i, N) {
        if (i == 0) {
            continue;
        }
        f[i][0] = 1;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < horses[i].size(); k++) {
                f[i][j] += f[horses[i][k]][j - 1];
            }
        }
    }
    int sum = 0;
    repeat(i, N) {
        sum += f[i][n - 1];
    }
    cout << sum;
}