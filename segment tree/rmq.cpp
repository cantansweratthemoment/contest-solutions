/*
Дан массив 𝚊[𝟷..𝚗]
Требуется написать программу, обрабатывающую два типа запросов.
"𝚖𝚊𝚡𝑙𝑟 Найти максимум в массиве 𝚊 от 𝑙-ой ячейки до 𝑟-ой включительно.
"𝚊𝚍𝚍𝑙𝑟𝑣 Прибавить значение 𝑣 к каждой ячейке 𝚊 от 𝑙-ой до 𝑟-ой включительно.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

#define N 100001

struct node {
    int value = 0;
    int lazy = 0;
};
int arr[N];
vector<node> segmentTree(N * 4);

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

void update(int i, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int value) {
    if (segmentTree[i].lazy != 0) {
        segmentTree[i].value += segmentTree[i].lazy;
        if (segmentStart != segmentEnd) {
            segmentTree[i * 2].lazy += segmentTree[i].lazy;
            segmentTree[i * 2 + 1].lazy += segmentTree[i].lazy;
        }
        segmentTree[i].lazy = 0;
    }
    if (queryStart > segmentEnd || queryEnd < segmentStart) {
        return;
    }

    if (segmentStart >= queryStart && segmentEnd <= queryEnd) {
        segmentTree[i].value += value;
        if (segmentStart != segmentEnd) {
            segmentTree[i * 2].lazy += value;
            segmentTree[i * 2 + 1].lazy += value;
        }
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    update(i * 2, segmentStart, middle, queryStart, queryEnd, value);
    update(i * 2 + 1, middle + 1, segmentEnd, queryStart, queryEnd, value);
    segmentTree[i].value = max(segmentTree[i * 2].value, segmentTree[i * 2 + 1].value);
}

int query(int i, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int value = 0) {
    if (queryStart > segmentEnd || queryEnd < segmentStart || queryEnd < queryStart) {
        return INT_MIN;
    }

    if (segmentTree[i].lazy != 0) {
        segmentTree[i].value += segmentTree[i].lazy;
        if (segmentStart != segmentEnd) {
            segmentTree[i * 2].lazy += segmentTree[i].lazy;
            segmentTree[i * 2 + 1].lazy += segmentTree[i].lazy;
        }
        segmentTree[i].lazy = 0;
    }

    if (segmentStart >= queryStart && segmentEnd <= queryEnd) {
        return segmentTree[i].value;
    }

    int middle = getMiddle(segmentStart, segmentEnd);

    int left = query(i * 2, segmentStart, middle, queryStart, queryEnd);
    int right = query(i * 2 + 1, middle + 1, segmentEnd, queryStart, queryEnd);

    return max(left, right);
}

void build(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTree[i].value = arr[segmentStart];
        segmentTree[i].lazy = 0;
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    build(i * 2, segmentStart, middle);
    build(i * 2 + 1, middle + 1, segmentEnd);
    segmentTree[i].value = max(segmentTree[i * 2].value, segmentTree[i * 2 + 1].value);
}


signed main() {
    meow
    int n, q;
    cin >> n >> q;
    int w;
    repeat(i, n) {
        cin >> w;
        arr[i + 1] = w;
    }
    build(1, 1, n);
    string e;
    int l, r, v;
    repeat(i, q) {
        cin >> e;
        if (e == "max") {
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << endl;
        } else {
            cin >> l >> r >> v;
            update(1, 1, n, l, r, v);
        }
    }
}

