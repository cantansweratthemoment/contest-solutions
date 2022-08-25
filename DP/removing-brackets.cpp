/**
 * Дана строка, составленная из круглых, квадратных и фигурных скобок. Определите, какое наименьшее количество символов необходимо удалить из этой строки, чтобы оставшиеся символы образовывали правильную скобочную последовательность.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

bool isGood(char q0, char qn) {
    return ((q0 == '[' && qn == ']') || (q0 == '(' && qn == ')') || (q0 == '{' && qn == '}'));
}

signed main() {
    meow
    string q;
    cin >> q;
    int n = q.size();
    vector<vector<int>> f(n, vector<int>(n));
    repeat(i, n) {
        repeat(j, i + 1) {
            f[i][j] = 0;
        }
    }
    for (int l = 2; l <= n; l++) {
        for (int i = 0; i + l <= n; i++) {
            int j = i + l - 1;
            f[i][j] = 0;
            if (isGood(q[i], q[j])) {
                f[i][j] = f[i + 1][j - 1] + 2;
            }
            for (int k = i; k < j; k++) {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }
    cout << f[0][n - 1];
}