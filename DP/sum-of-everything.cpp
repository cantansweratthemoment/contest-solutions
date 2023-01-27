/**
 * Дан случайный граф. Нужно для каждого множества вершин 𝐴 посчитать 𝑓(𝐴), количество независимых подмножеств вершин 𝐵:𝐵⊆𝐴.
 * Множество вершин 𝐵 называется независимым, если в графе нет ребра, оба конца которого лежат в множестве 𝐵.
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

int powerFast(int num, int deg) { //признаюсь честно я это скопировала из интернета
    int result = 1;
    while(deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
            num %= 1000000007;
        }
        else {
            deg--;
            result *= num;
            result %= 1000000007;
        }
    }
    return result;
}

signed main() {
    meow
    int n, m;
    cin >> n >> m;
    vector<int> graph(n, 0);
    int q, w;
    repeat(i, m) {
        cin >> q >> w;
        q--;
        w--;
        graph[q] = graph[q] | 1 << w;
        graph[w] = graph[w] | 1 << q;
    }
    vector<int> f(powerFast(2, n));
    f[0] = 1;
    for (int mask = 1; mask < f.size(); mask++) {
        int removedElement = __builtin_ctz(mask);
        int smallMask = mask & (~(1 << removedElement));
        f[mask] = f[smallMask];
        int anotherSmallMask = smallMask & (~graph[removedElement]);
        f[mask] += f[anotherSmallMask];
        f[mask] %= 1000000007;
    }
    int result = 0;
    repeat(i, f.size()) {
        result += (f[i] * powerFast(2, i)) % 1000000007;
        result %= 1000000007;
    }
    cout << result;
}