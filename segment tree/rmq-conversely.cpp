/**
Рассмотрим массив 𝑎[1..𝑛].
Пусть 𝑄(𝑖,𝑗) — ответ на запрос о нахождении минимума среди чисел 𝑎[𝑖],…,𝑎[𝑗].
Вам даны несколько запросов и ответы на них. Восстановите исходный массив.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

#define opened true
#define closed false

struct query {
    int i;
    int j;
    int q;
};

struct element {
    int value = INT_MAX;
};

struct event {
    bool type;
    int value;
};

vector<element> arr;
vector<int> segmentTree;
vector<list<event>> events;

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
        segmentTree[i] = arr[segmentStart].value;
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    build(i * 2 + 1, segmentStart, middle);
    build(i * 2 + 2, middle + 1, segmentEnd);
    segmentTree[i] = min(segmentTree[i * 2 + 1], segmentTree[i * 2 + 2]);
}

signed main() {
    meow
    int n, m, i, j, q;
    cin >> n >> m;
    vector<query> input;
    events.resize(n + 1);
    repeat(w, m) {
        cin >> i >> j >> q;
        query query{.i=i, .j=j, .q=q};
        input.push_back(query);
        event eventOpen = {.type = opened, .value = q};
        event eventClosed = {.type = closed, .value = q};
        events[i].push_back(eventOpen);
        events[j].push_back(eventClosed);
    }
    arr.resize(n + 1);
    map<int, int, greater<>> values;
    for (int w = 1; w <= n; w++) {
        for (event event: events[w]) {
            if (event.type == opened) {
                if (values.find(event.value) == values.end()) {
                    values.insert(make_pair(event.value, 1));
                } else {
                    values.find(event.value)->second += 1;
                }
            }
        }
        if (!values.empty()) {
            arr[w].value = values.begin()->first;
        }
        for (event event: events[w]) {
            if (event.type == closed) {
                values.find(event.value)->second -= 1;
                if (values.find(event.value)->second < 1) {
                    values.erase(values.find(event.value));
                }
            }
        }
    }
    segmentTree.resize(n * 4);
    build(0, 0, n);
    repeat(w, m) {
        i = input[w].i;
        j = input[w].j;
        q = input[w].q;
        if (q != minQuery(0, n, i, j, 0)) {
            cout << "inconsistent";
            return 0;
        }
    }
    cout << "consistent\n";
    repeat(w, n + 1) {
        if (w == 0) {
            continue;
        }
        cout << arr[w].value << " ";
    }
}