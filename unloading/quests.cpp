/**
 * У вас есть возможность выполнять 𝑛 квестов. Если вы выполняете 𝑖-й квест, вы получаете 𝑎𝑖 монет. Вы можете выполнить не больше одного квеста в день.
 * Однако, после того как вы выполнили квест, вы не можете выполнить его снова в течение следующих 𝑘 дней.
 * Заданы два целых числа 𝑐 и 𝑑. Найдите максимальный 𝑘 такой, что возможно получить как минимум 𝑐 монет за 𝑑 дней. Если таких 𝑘 не существует, выведите Impossible. Если 𝑘 может быть бесконечно большим, выведите Infinity.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

bool isCReachable(const vector<int> &sums, int i, int c, int d) {
    i++;
    int chastnoe = d / i;
    int ostatok = d - chastnoe * i;
    int ii;
    if (i - 1 > sums.size() - 1) {
        ii = sums.size() - 1;
    } else {
        ii = i - 1;
    }
    int ostatokI;
    if (ostatok - 1 > sums.size() - 1) {
        ostatokI = sums.size() - 1;
    } else {
        ostatokI = ostatok - 1;
    }
    return (chastnoe * sums[ii] + (ostatok > 0 ? sums[ostatokI] : 0)) >= c;
}

signed main() {
    meow
    int t, n, c, d;
    cin >> t;
    repeat(i, t) {
        cin >> n >> c >> d;
        vector<int> a(n);
        repeat(ii, n) {
            cin >> a[ii];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int sum = 0;
        repeat(ii, min(d, n)) {
            sum += a[ii];
        }
        if (sum >= c) {
            cout << "Infinity\n";
            continue;
        }
        if (a[0] * d < c) {
            cout << "Impossible\n";
            continue;
        }
        vector<int> sums(n);
        sums[0] = a[0];
        for (int ii = 1; ii < n; ii++) {
            sums[ii] = sums[ii - 1] + a[ii];
        }
        int q = 0;
        int left = 0;
        int right = d + 1000;
        int middle;
        while (left < right - 1) {
            middle = (right + left) / 2;
            if (isCReachable(sums, middle, c, d)) {
                left = middle;
            } else {
                right = middle;
            }
        }
        cout << left << "\n";
    }
}