/**
 * Дано подвешенное дерево с корнем в первой вершине. Вам нужно ответить на 𝑚 запросов вида "найти LCA двух вершин".
LCA вершин 𝑢 и 𝑣 в подвешенном дереве — это наиболее удалённая от корня дерева вершина, лежащая на обоих путях от 𝑢 и 𝑣 до корня.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

vector<int> arr;
vector<int> arrFirst;
vector<int> segmentTree;

const bool BLACK = true;
const bool WHITE = false;
const int NONE = -1;

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int minQuery(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return INT_MAX;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return min(minQuery(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
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
    segmentTree[i] = min(segmentTree[i * 2 + 1], segmentTree[i * 2 + 2]);
}

void DFS(vector<vector<int>> &graph, int i, vector<bool> &checked) {
    arr.push_back(i);
    checked[i] = BLACK;
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j]]) {
            DFS(graph, graph[i][j], checked);
            arr.push_back(i);
        }
    }
}

signed main() {
    meow
    int n;
    cin >> n;
    vector<vector<int>> graph(n);
    int x;
    repeat(i, n - 1) {
        cin >> x;
        graph[i + 1].push_back(x - 1);
        graph[x - 1].push_back(i + 1);
    }
    vector<bool> checked;
    repeat(i, n) {
        checked.push_back(WHITE);
    }
    DFS(graph, 0, checked);
    arrFirst.resize(n + 1);
    repeat(i, n + 1) {
        arrFirst[i] = NONE;
    }
    repeat(i, arr.size()) {
        arr[i]++;
    }
    repeat(i, arr.size()) {
        if (arrFirst[arr[i]] == NONE) {
            arrFirst[arr[i]] = i;
        }
    }
    segmentTree.resize(arr.size() * 4);
    build(0, 0, arr.size() - 1);
    int m, u, v;
    cin >> m;
    repeat(i, m) {
        cin >> u >> v;
        if (arrFirst[u] < arrFirst[v]) {
            cout << minQuery(0, arr.size() - 1, arrFirst[u], arrFirst[v], 0) << endl;
        } else {
            cout << minQuery(0, arr.size() - 1, arrFirst[v], arrFirst[u], 0) << endl;
        }
    }
}