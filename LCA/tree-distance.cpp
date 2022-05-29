/**
 * Вам дано неориентированное дерево (связный граф без циклов) на 𝑁 вершинах.
 * Требуется отвечать на запросы вида «найти длину кратчайшего пути между данной парой вершин».
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

const bool BLACK = true;
const bool WHITE = false;
const int NONE = -1;

vector<int> arrLength;
vector<int> arr;
vector<int> arrFirst;
vector<int> segmentTree;

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int minLimitedEditionOfficial(int q, int w) {
    if (q == INT_MAX) {
        return w;
    }
    if (w == INT_MAX) {
        return q;
    }
    if (arrLength[q] < arrLength[w]) {
        return q;
    } else {
        return w;
    }
}

int minQuery(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return INT_MAX;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return minLimitedEditionOfficial(minQuery(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
                                     minQuery(mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2));
}

void build(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTree[i] = arr[segmentStart];
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    build(i * 2 + 1, segmentStart, middle);
    build(i * 2 + 2, middle + 1, segmentEnd);
    segmentTree[i] = minLimitedEditionOfficial(segmentTree[i * 2 + 1], segmentTree[i * 2 + 2]);
}

void DFS(vector<vector<int>> &graph, int i, vector<bool> &checked, int length) {
    arrLength[i] = length++;
    arr.push_back(i);
    checked[i] = BLACK;
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j]]) {
            DFS(graph, graph[i][j], checked, length);
            arr.push_back(i);
        }
    }
}

signed main() {
    meow
    int N;
    cin >> N;
    N++;
    vector<vector<int>> graph(N);
    int u, v;
    graph[1].push_back(0);
    graph[0].push_back(1);
    repeat(i, N - 2) {
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool> checked;
    repeat(i, N) {
        checked.push_back(WHITE);
    }
    arrLength.resize(N);
    DFS(graph, 0, checked, 0);
    arrFirst.resize(N);
    repeat(i, N) {
        arrFirst[i] = NONE;
    }
    repeat(i, arr.size()) {
        if (arrFirst[arr[i]] == NONE) {
            arrFirst[arr[i]] = i;
        }
    }
    segmentTree.resize(arr.size() * 4);
    build(0, 0, arr.size() - 1);
    int M, lca;
    cin >> M;
    repeat(i, M) {
        cin >> u >> v;
        if (u == v) {
            cout << 0 << endl;
            continue;
        }
        if (arrFirst[u] < arrFirst[v]) {
            lca = minQuery(0, arr.size() - 1, arrFirst[u], arrFirst[v], 0);
        } else {
            lca = minQuery(0, arr.size() - 1, arrFirst[v], arrFirst[u], 0);
        }
        cout << arrLength[u] + arrLength[v] - 2 * arrLength[lca] << endl;
    }
}