/**
Изначально имеется дерево состоящее только из корня (вершина с номером 1). Требуется научиться отвечать на следующие запросы:
ADD 𝑎 𝑏 — подвесить вершину 𝑏 за вершину 𝑎 (гарантируется, что вершина 𝑎 уже существует).
GET 𝑎 𝑏 — вернуть LCA вершин 𝑎 и 𝑏.
Все номера вершин от 1 до 𝑁.
В каждый момент времени у нас есть одно дерево.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

const bool BLACK = true;
const bool WHITE = false;
const int NONE = -1;
const bool ADD = true;
const bool GET = false;

vector<int> arrLength;
vector<int> arr;
vector<int> arrFirst;
vector<int> segmentTree;

struct input {
    bool type;
    int q;
    int w;

    input(bool type, int q, int w) : type(type), q(q), w(w) {}
};

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

int findN(vector<input> &inputs) {
    int max = INT_MIN;
    repeat(i, inputs.size()) {
        if (inputs[i].q > max) {
            max = inputs[i].q;
        }
        if (inputs[i].w > max) {
            max = inputs[i].w;
        }
    }
    return ++max;
}

signed main() {
    meow
    int k;
    cin >> k;
    vector<input> inputs;
    string typeS;
    int q, w;
    repeat(i, k) {
        cin >> typeS >> q >> w;
        q--;
        w--;
        bool type;
        type = typeS == "ADD";
        auto e = new input(type, q, w);
        inputs.push_back(*e);
    }
    int n = findN(inputs);
    vector<vector<int>> graph(n);
    repeat(i, inputs.size()) {
        if (inputs[i].type) {
            q = inputs[i].q;
            w = inputs[i].w;
            graph[q].push_back(w);
            graph[w].push_back(q);
        }
    }
    vector<bool> checked;
    repeat(i, n) {
        checked.push_back(WHITE);
    }
    arrLength.resize(n);
    DFS(graph, 0, checked, 0);
    arrFirst.resize(n);
    repeat(i, n) {
        arrFirst[i] = NONE;
    }
    repeat(i, arr.size()) {
        if (arrFirst[arr[i]] == NONE) {
            arrFirst[arr[i]] = i;
        }
    }
    segmentTree.resize(arr.size() * 4);
    build(0, 0, arr.size() - 1);
    repeat(i, inputs.size()) {
        if (!inputs[i].type) {
            q = inputs[i].q;
            w = inputs[i].w;
            if (arrFirst[q] < arrFirst[w]) {
                cout << minQuery(0, arr.size() - 1, arrFirst[q], arrFirst[w], 0) + 1 << endl;
            } else {
                cout << minQuery(0, arr.size() - 1, arrFirst[w], arrFirst[q], 0) + 1 << endl;
            }
        }
    }
}