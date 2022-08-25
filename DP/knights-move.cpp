/**
 * Шахматная ассоциация решила оснастить всех своих сотрудников такими телефонными номерами, которые бы набирались на кнопочном телефоне ходом коня. Например, ходом коня набирается телефон 340-49-27. При этом телефонный номер не может начинаться ни с цифры 0, ни с цифры 8.
 * Напишите программу, определяющую количество телефонных номеров длины n, набираемых ходом коня. Поскольку таких номеров может быть очень много, выведите ответ по модулю 10^9.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int unsigned long long

const int N = 10;

signed main() {
    meow
    int n;
    cin >> n;
    vector<int> horse0 = {4, 6};
    vector<int> horse1 = {6, 8};
    vector<int> horse2 = {7, 9};
    vector<int> horse3 = {4, 8};
    vector<int> horse4 = {0, 3, 9};
    vector<int> horse5 = {};
    vector<int> horse6 = {0, 1, 7};
    vector<int> horse7 = {2, 6};
    vector<int> horse8 = {1, 3};
    vector<int> horse9 = {2, 4};
    vector<vector<int>> horses = {horse0, horse1, horse2, horse3, horse4, horse5, horse6, horse7, horse8, horse9};
    vector<vector<int>> f(N);
    repeat(i, N) {
        f[i].resize(n, 0);
    }
    f[0][0] = f[8][0] = 0;
    repeat(i, N) {
        if (i == 0 || i == 8) {
            continue;
        }
        f[i][0] = 1;
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < horses[i].size(); k++) {
                f[i][j] += f[horses[i][k]][j - 1];
                if (f[i][j] >= 1000000000) {
                    f[i][j] = f[i][j] % 1000000000;
                }
            }
        }
    }
    int sum = 0;
    repeat(i, N) {
        sum += f[i][n - 1];
        if (sum >= 1000000000) {
            sum = sum % 1000000000;
        }
    }
    cout << sum;
}
