/**
 * Дано подвешенное дерево с корнем в первой вершине. Все ребра имеют веса (стоимости).
 * Вам нужно ответить на 𝑀 запросов вида «найти у двух вершин минимум среди стоимостей ребер пути между ними».
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

const int maxK = 20;
const int maxN = 50000;
const int BLACK = 1;
const int WHITE = 0;

vector<array<int, maxK>> dp(maxN);
vector<array<int, maxK>> dp2(maxN);
vector<int> height(maxN);

struct input {
    int p;
    int e;

    //input(int p, int e) : p(p), e(e) {}
};

void DFS(vector<vector<int>> &graph, int i, vector<int> &checked, int length) {
    height[i] = length++;
    checked[i] = BLACK;
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j]]) {
            DFS(graph, graph[i][j], checked, length);
        }
    }
}

int minEdge(int q, int w) {
    int edge = INT_MAX;
    if (height[q] < height[w]) {
        swap(q, w);
    }
    for (int k = maxK - 1; k >= 0; k--) {
        if (height[dp[q][k]] > height[w]) {
            edge = min(dp2[q][k], edge);
            q = dp[q][k];
        }
    }
    if (dp[q][0] == w) {
        return min(edge, dp2[q][0]);
    }
    if (height[q] > height[w]) {
        edge = min(edge, dp2[q][0]);
        q = dp[q][0];
    }
    for (int k = maxK - 1; k >= 0; k--) {
        if (dp[q][k] != dp[w][k]) {
            edge = min(dp2[q][k], edge);
            edge = min(dp2[w][k], edge);
            q = dp[q][k];
            w = dp[w][k];
        }
    }
    return min(min(dp2[q][0], dp2[w][0]), edge);
}

signed main() {
    meow
    int n;
    cin >> n;
    vector<input> p(n);
    vector<vector<int>> graph(n);
    int q, w;
    repeat(i, n - 1) {
        cin >> q >> w;
        q--;
        input e = {.p = q, .e = w};
        p[i + 1] = e;
        graph[i + 1].emplace_back(q);
        graph[q].emplace_back(i + 1);
    }
    vector<int> checked;
    repeat(i, n) {
        checked.push_back(WHITE);
    }
    DFS(graph, 0, checked, 0);
    height.resize(n);
    for (int i = 1; i < n; i++) {
        dp[i][0] = p[i].p;
    }
    for (int k = 1; k < maxK; k++) {
        for (int i = 1; i < n; i++) {
            dp[i][k] = dp[dp[i][k - 1]][k - 1];
        }
    }
    for (int i = 1; i < n; i++) {
        dp2[i][0] = p[i].e;
    }
    for (int k = 1; k < maxK; k++) {
        for (int i = 1; i < n; i++) {
            dp2[i][k] = min(dp2[i][k - 1], dp2[dp[i][k - 1]][k - 1]);
        }
    }
    int m;
    cin >> m;
    int x, y;
    repeat(i, m) {
        cin >> x >> y;
        x--;
        y--;
        cout << minEdge(x, y) << endl;
    }
}