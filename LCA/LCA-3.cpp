/**
 * Дан набор подвешенных деревьев. Требуется выполнять следующие операции:
 * 0 u v Для двух заданных вершин 𝑢 и 𝑣 выяснить, лежат ли они в одном дереве. Если это так, вывести вершину, являющуюся их наименьшим общим предком, иначе вывести 0.
 * 1 u v Для корня 𝑢 одного из деревьев и произвольной вершины 𝑣 другого дерева добавить ребро (𝑣,𝑢).
 * В результате эти два дерева соединятся в одно.
 * Вам необходимо выполнять все операции online, т.е. вы сможете узнать следующий запрос только выполнив предыдущий.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

const int maxK = 20;
const int maxN = 60000;

vector<int> p;
vector<array<int, maxK>> dp(maxN);

int getDp(int v, int i) {
    if (dp[v][i] != -1) {
        return dp[v][i];
    }
    if (i == 0) {
        return -1;
    }
    int half = getDp(v, i - 1);
    if (half != -1) {
        dp[v][i] = getDp(half, i - 1);
    }
    return dp[v][i];
}

int getHeight(int v) {
    /*if (v == -1) {
        return -1;
    }*/
    int count = 0;
    for (int k = maxK - 1; k >= 0; k--) {
        if (getDp(v, k) != -1) {
            count += 1 << k;
            v = getDp(v, k);
        }
    }
    return count;
}

int getRoot(int v) {
    for (int k = maxK - 1; k >= 0; k--) {
        if (getDp(v, k) != -1) {
            v = getDp(v, k);
        }
    }
    return v;
}

int LCA(int u, int v) {
    if (getHeight(u) < getHeight(v)) {
        swap(u, v);
    }
    int heightV = getHeight(v);
    for (int k = maxK - 1; k >= 0; k--) {
        int dp = getDp(u, k);
        if ((dp != -1) && getHeight(dp) >= heightV) {
            u = getDp(u, k);
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = maxK - 1; k >= 0; k--) {
        if (getDp(u, k) != getDp(v, k)) {
            u = getDp(u, k);
            v = getDp(v, k);
        }
    }
    return getDp(u, 0);
}

bool isSameTree(int u, int v) {
    int rootU = getRoot(u);
    int rootV = getRoot(v);
    return rootU == rootV;
}

signed main() {
    meow
    int n;
    cin >> n;
    p.resize(n + 1);
    int q;
    for (int i = 1; i <= n; i++) {
        cin >> q;
        if (q == 0) {
            p[i] = -1;
        } else {
            p[i] = q;
        }
    }
    for (int k = 0; k < maxK; k++) {
        for (int i = 0; i < maxN; i++) {
            dp[i][k] = -1;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i][0] = p[i];
    }
    int k;
    cin >> k;
    int type, x, y, u, v;
    int ans = 0;
    repeat(i, k) {
        cin >> type >> x >> y;
        u = (x - 1 + ans) % n + 1;
        v = (y - 1 + ans) % n + 1;
        if (type == 0) {
            if (isSameTree(u, v)) {
                int lca = LCA(u, v);
                cout << lca << endl;
                ans = lca;
            } else {
                cout << 0 << endl;
                ans = 0;
            }
        } else {
            dp[u][0] = v;
        }
    }
}