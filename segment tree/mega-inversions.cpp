/**
Инверсией в перестановке 𝑝1,𝑝2,...,𝑝𝑁 называется пара (𝑖,𝑗) такая, что 𝑖<𝑗 и 𝑝𝑖>𝑝𝑗.
Назовем мега-инверсией в перестановке 𝑝1,𝑝2,...,𝑝𝑁 тройку (𝑖,𝑗,𝑘) такую, что 𝑖<𝑗<𝑘 и 𝑝𝑖>𝑝𝑗>𝑝𝑘.
Придумайте алгоритм для быстрого подсчета количества мега-инверсий в перестановке.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

#define N_ARR 100001

vector<int> segmentTree;

struct element {
    int value;
    int first = 0;
    int second = 0;
};

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int sumQuery(int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return 0;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return sumQuery(segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1) +
           sumQuery(mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2);
}

void build(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTree[i] = 0;
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    build(i * 2 + 1, segmentStart, middle);
    build(i * 2 + 2, middle + 1, segmentEnd);
    segmentTree[i] = min(segmentTree[i * 2 + 1], segmentTree[i * 2 + 2]);
}

void increment(int segmentStart, int segmentEnd, int i, int diff, int segmentIndex) {
    if (i < segmentStart || i > segmentEnd) {
        return;
    }
    segmentTree[segmentIndex] = segmentTree[segmentIndex] + diff;
    if (segmentEnd != segmentStart) {
        int mid = getMiddle(segmentStart, segmentEnd);
        increment(segmentStart, mid, i, diff, 2 * segmentIndex + 1);
        increment(mid + 1, segmentEnd, i, diff, 2 * segmentIndex + 2);
    }
}

signed main() {
    meow
    int N;
    vector<element> a;
    cin >> N;
    int q;
    segmentTree.resize(N_ARR * 4);
    repeat(i, N) {
        cin >> q;
        element element = {.value=q, .first=0, .second=0};
        a.push_back(element);
    }
    build(0, 0, N_ARR - 1);
    repeat(i, N) {
        a[i].first = sumQuery(0, N_ARR - 1, a[i].value + 1, N_ARR - 1, 0);
        increment(0, N_ARR - 1, a[i].value, 1, 0);
    }
    repeat(i, N) {
        a[i].second = sumQuery(0, N_ARR - 1, 0, a[i].value - 1, 0);
        increment(0, N_ARR - 1, a[i].value, -1, 0);
    }
    int sum = 0;
    repeat(i, N) {
        sum += a[i].first * a[i].second;
    }
    cout << sum;
}