/**
 * Определим по индукции множество R правильных скобочных последовательностей:
 * ε ∈ R (пустая строка)
 * A ∈ R ⇒ (A) ∈ R
 * A ∈ R, B ∈ R ⇒ AB ∈ R
 * Пусть теперь R𝑛 — это множество правильных скобочных последовательностей из 2𝑛 символов — 𝑛 открывающих и 𝑛 закрывающих скобок.
 * Упорядочим элементы множества R𝑛 лексикографически с порядком символов ′(′<′)′.
 * По данным числам 𝑛 и 𝑝 найдите 𝑝-ый в этом порядке элемент множества R𝑛.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

signed main() {
    meow
    int n, p;
    cin >> n >> p;
    if (n == 0) {
        if (p != 0) {
            cout << "N/A";
            return 0;
        } else {
            return 0;
        }
    }
    vector<vector<int>> f(4 * n, vector<int>(4 * n));
    f[0][0] = 1;
    repeat(j, 2 * n) {
        if (j == 0) {
            continue;
        }
        f[0][j] = 0;
    }
    repeat(i, 2 * n) {
        if (i == 0) {
            continue;
        }
        repeat(j, 2 * n) {
            if (j <= 0) {
                f[i][j] = f[i - 1][j + 1];
            } else {
                f[i][j] = f[i - 1][j - 1] + f[i - 1][j + 1];
            }
        }
    }
    int id = 0;
    p++;
    string answer;
    repeat(i, 2 * n) {
        if (id + 1 < 4 * n) {
            if (f[2 * n - (i + 1)][id + 1] >= p) {
                id++;
                answer += "(";
            } else {
                p -= f[2 * n - (i + 1)][id + 1];
                id--;
                answer += ")";
            }
        }
    }
    int balance = 0;
    repeat(i, answer.size()) {
        if (answer[i] == ')') {
            balance--;
        } else {
            balance++;
        }
        if (balance < 0) {
            cout << "N/A";
            return 0;
        }
    }
    if (balance == 0) {
        cout << answer;
    } else {
        cout << "N/A";
    }
}