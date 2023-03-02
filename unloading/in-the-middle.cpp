/**
 * Даны три различных целых числа 𝑎, 𝑏, и 𝑐.
 * Найдите среднее из них. Другими словами, найдите среди заданных трёх чисел число не являющееся ни минимумом, ни максимумом.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

int findAverage(int a, int b, int c) {
    if (a > b && b > c || a < b && b < c) {
        return b;
    }
    if (b > a && a > c || b < a && a < c) {
        return a;
    }
    if (a < c && c < b || a > c && c > b) {
        return c;
    }
}

signed main() {
    meow
    int n, a, b, c;
    cin >> n;
    repeat(i, n) {
        cin >> a >> b >> c;
        cout << findAverage(a, b, c) << "\n";
    }
}