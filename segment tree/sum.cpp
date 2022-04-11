/**
 *
Дан массив из N элементов, нужно научиться находить сумму чисел на отрезке.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int buildSegmentTreeUtil(int arr[], int segmentStart, int segmentEnd, int *segmentTree, int segmentIndex) {
    if (segmentStart == segmentEnd) {
        segmentTree[segmentIndex] = arr[segmentStart];
        return arr[segmentStart];
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    segmentTree[segmentIndex] = buildSegmentTreeUtil(arr, segmentStart, mid, segmentTree, segmentIndex * 2 + 1) +
                                buildSegmentTreeUtil(arr, mid + 1, segmentEnd, segmentTree, segmentIndex * 2 + 2);
    return segmentTree[segmentIndex];
}

int *buildSegmentTree(int arr[], int n) {
    int *segmentTree = new int[n * 4 + 1];
    buildSegmentTreeUtil(arr, 0, n - 1, segmentTree, 0);
    return segmentTree;
}

int sumUtil(int *segmentTree, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return 0;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return sumUtil(segmentTree, segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1) +
           sumUtil(segmentTree, mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2);
}

int sum(int *segmentTree, int n, int queryStart, int queryEnd) {
    return sumUtil(segmentTree, 0, n - 1, queryStart, queryEnd, 0);
}

void setUtil(int *segmentTree, int segmentStart, int segmentEnd, int i, int diff, int segmentIndex) {
    if (i < segmentStart || i > segmentEnd) {
        return;
    }
    segmentTree[segmentIndex] = segmentTree[segmentIndex] + diff;
    if (segmentEnd != segmentStart) {
        int mid = getMiddle(segmentStart, segmentEnd);
        setUtil(segmentTree, segmentStart, mid, i, diff, 2 * segmentIndex + 1);
        setUtil(segmentTree, mid + 1, segmentEnd, i, diff, 2 * segmentIndex + 2);
    }
}

void setVal(int arr[], int *segmentTree, int n, int i, int val) {
    int diff = val - arr[i];
    arr[i] = val;
    setUtil(segmentTree, 0, n - 1, i, diff, 0);
}

signed main() {
    meow
    int N, K;
    cin >> N >> K;
    int *arr = new int[N];
    repeat(i, N) {
        arr[i] = 0;
    }
    int *segmentTree = buildSegmentTree(arr, N);
    string q;
    int i, x, l, r;
    repeat(w, K) {
        cin >> q;
        if (q == "A") {
            cin >> i >> x;
            setVal(arr, segmentTree, N, i - 1, x);
        } else {
            cin >> l >> r;
            cout << sum(segmentTree, N, l - 1, r - 1) << endl;
        }
    }
    delete[] arr;
    delete[] segmentTree;
}