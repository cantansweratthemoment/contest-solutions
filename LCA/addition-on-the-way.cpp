/**
 * Задано дерево. В каждой вершине есть значение, изначально все значения равны нулю.
 * Требуется обработать запрос прибавления на пути и запрос значения в вершине.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

vector<vector<int>> graph;
vector<int> arrHeight;
vector<int> euler;
vector<int> arrFirst;
vector<int> segmentTreeEuler;
vector<int> segmentTreeTIn;
vector<int> checked;
vector<int> tIn;
vector<int> sz;
vector<int> values;
vector<int> p;
int t = 0;

const int BLACK = 1;
const int WHITE = 0;
const int NONE = -1;

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int customMin(int q, int w) {
    if (q == INT_MAX) {
        return w;
    }
    if (w == INT_MAX) {
        return q;
    }
    if (arrHeight[q] < arrHeight[w]) {
        return q;
    } else {
        return w;
    }
}

int minQuery(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTreeEuler[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return INT_MAX;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return customMin(minQuery(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
                     minQuery(mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2));
}

int sumQuery(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTreeTIn[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return 0;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return sumQuery(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1) +
           sumQuery(mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2);
}

void setValue(int segmentStart, int segmentEnd, int index, int value, int node) {
    if (segmentStart == segmentEnd) {
        values[index] = value;
        segmentTreeTIn[node] += value;
    } else {
        int mid = getMiddle(segmentStart, segmentEnd);
        if (index >= segmentStart && index <= mid) {
            setValue(segmentStart, mid, index, value, 2 * node + 1);
        } else {
            setValue(mid + 1, segmentEnd, index, value, 2 * node + 2);
        }
        segmentTreeTIn[node] = segmentTreeTIn[2 * node + 1] + segmentTreeTIn[2 * node + 2];
    }
}

void buildEuler(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTreeEuler[i] = euler[segmentStart];
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    buildEuler(i * 2 + 1, segmentStart, middle);
    buildEuler(i * 2 + 2, middle + 1, segmentEnd);
    segmentTreeEuler[i] = customMin(segmentTreeEuler[i * 2 + 1], segmentTreeEuler[i * 2 + 2]);
}

void buildTIn(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTreeTIn[i] = values[segmentStart];
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    buildTIn(i * 2 + 1, segmentStart, middle);
    buildTIn(i * 2 + 2, middle + 1, segmentEnd);
    segmentTreeTIn[i] = segmentTreeTIn[i * 2 + 1] + segmentTreeTIn[i * 2 + 2];
}

void DFS(int i, int length) {
    sz[i] = 1;
    arrHeight[i] = length++;
    euler.push_back(i);
    tIn[i] = t;
    t++;
    checked[i] = BLACK;
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j]]) {
            p[graph[i][j]] = i;
            DFS(graph[i][j], length);
            euler.push_back(i);
            sz[i] += sz[graph[i][j]];
        }
    }
}

int LCA(int q, int w) {
    if (arrFirst[q] < arrFirst[w]) {
        return minQuery(0, euler.size() - 1, arrFirst[q], arrFirst[w], 0);
    } else {
        return minQuery(0, euler.size() - 1, arrFirst[w], arrFirst[q], 0);
    }
}

signed main() {
    meow
    int n, v, u;
    cin >> n;
    graph.resize(n);
    repeat(i, n - 1) {
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    checked.resize(n);
    repeat(i, n) {
        checked[i] = WHITE;
    }
    arrHeight.resize(n);
    arrFirst.resize(n);
    sz.resize(n);
    tIn.resize(n);
    repeat(i, n) {
        arrFirst[i] = NONE;
    }
    p.resize(n);
    DFS(0, 0);
    p[0] = NONE;
    values.resize(tIn.size());
    repeat(i, values.size()) {
        values[i] = 0;
    }
    repeat(i, euler.size()) {
        if (arrFirst[euler[i]] == NONE) {
            arrFirst[euler[i]] = i;
        }
    }
    segmentTreeEuler.resize(euler.size() * 4);
    buildEuler(0, 0, euler.size() - 1);
    segmentTreeTIn.resize(tIn.size() * 4);
    buildTIn(0, 0, tIn.size() - 1);
    int m;
    cin >> m;
    int d;
    string q;
    repeat(i, m) {
        cin >> q;
        if (q == "+") {
            cin >> v >> u >> d;
            v--;
            u--;
            int lca = LCA(v, u);
            setValue(0, values.size() - 1, tIn[v], d, 0);
            setValue(0, values.size() - 1, tIn[u], d, 0);
            setValue(0, values.size() - 1, tIn[lca], d * (-1), 0);
            if (p[lca] != NONE) {
                setValue(0, values.size() - 1, tIn[p[lca]], d * (-1), 0);
            }
        } else {
            cin >> v;
            v--;
            cout << sumQuery(0, values.size() - 1, tIn[v], tIn[v] + sz[v] - 1, 0) << endl;
        }
    }
}