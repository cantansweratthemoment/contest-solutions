/**
 * Сочетанием из 𝑛 элементов по 𝑘 назовём возрастающую последовательность из 𝑘 целых чисел от 1 до 𝑛, включительно.
 * Упорядочим все сочетания из 𝑛 по 𝑘 лексикографически как векторы из 𝑘 чисел.
 * По заданным числам 𝑛, 𝑘 и 𝑝 выведите 𝑝-е в лексикографическом порядке сочетание из 𝑘 натуральных чисел от 1 до 𝑛.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

signed main() {
    meow
    int n, k, p;
    cin >> n >> k >> p;
    vector<int> used(n, false);
    vector<vector<int>> f(n, vector<int>(n));
    f[0][0] = 1;
    for (int i = 1; i < n; i++) {
        f[i][0] = 0;
    }
    for (int i = 1; i < n; i++) {
        f[0][i] = i + 1;
    }
    repeat(i, n) {
        if (i == 0) {
            continue;
        }
        repeat(j, n) {
            if (j == 0) {
                continue;
            }
            f[j][i] = f[j][i - 1] + f[j - 1][i - 1];
        }
    }
    vector<int> result(k);
    int lastValue = 0;
    repeat(position, k) {
        repeat(value, n) {
            if (used[value] || value < lastValue) {
                continue;
            }
            if (position == k - 1) {
                if (p >= 1) {
                    p -= 1;
                } else {
                    used[value] = true;
                    result[position] = value + 1;
                    break;
                }
            } else {
                if (p >= f[k - (position + 2)][n - 2 - value]) {
                    p -= f[k - (position + 2)][n - 2 - value];
                } else {
                    used[value] = true;
                    result[position] = value + 1;
                    lastValue = value;
                    break;
                }
            }
        }
    }
    sort(result.begin(), result.end());
    repeat(i, result.size()) {
        cout << result[i] << " ";
    }
}