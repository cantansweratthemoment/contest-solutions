/*
В начальный момент времени последовательность 𝑎𝑛 задана следующей формулой: 𝑎𝑛=𝑛2mod12345+𝑛3mod23456
Требуется много раз отвечать на запросы следующего вида:
Найти разность между максимальным и минимальным значениями среди элементов 𝑎𝑖,𝑎𝑖+1,…,𝑎𝑗
Присвоить элементу 𝑎𝑖 значение 𝑗
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

int buildMaxSegmentTreeUtil(int arr[], int segmentStart, int segmentEnd, int *segmentTree, int segmentIndex) {
    if (segmentStart == segmentEnd) {
        segmentTree[segmentIndex] = arr[segmentStart];
        return arr[segmentStart];
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    segmentTree[segmentIndex] = max(buildMaxSegmentTreeUtil(arr, segmentStart, mid, segmentTree, segmentIndex * 2 + 1),
                                    buildMaxSegmentTreeUtil(arr, mid + 1, segmentEnd, segmentTree,
                                                            segmentIndex * 2 + 2));
    return segmentTree[segmentIndex];
}

int *buildMaxSegmentTree(int arr[], int n) {
    int *segmentTree = new int[n * 4];
    buildMaxSegmentTreeUtil(arr, 0, n - 1, segmentTree, 0);
    return segmentTree;
}

int buildMinSegmentTreeUtil(int arr[], int segmentStart, int segmentEnd, int *segmentTree, int segmentIndex) {
    if (segmentStart == segmentEnd) {
        segmentTree[segmentIndex] = arr[segmentStart];
        return arr[segmentStart];
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    segmentTree[segmentIndex] = min(buildMinSegmentTreeUtil(arr, segmentStart, mid, segmentTree, segmentIndex * 2 + 1),
                                    buildMinSegmentTreeUtil(arr, mid + 1, segmentEnd, segmentTree,
                                                            segmentIndex * 2 + 2));
    return segmentTree[segmentIndex];
}

int *buildMinSegmentTree(int arr[], int n) {
    int *segmentTree = new int[n * 4];
    buildMinSegmentTreeUtil(arr, 0, n - 1, segmentTree, 0);
    return segmentTree;
}

int maxUtil(int *segmentTree, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return INT_MIN;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return max(maxUtil(segmentTree, segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
               maxUtil(segmentTree, mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2));
}

int maxVal(int *segmentTree, int n, int queryStart, int queryEnd) {
    return maxUtil(segmentTree, 0, n - 1, queryStart, queryEnd, 0);
}

int minUtil(int *segmentTree, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int segmentIndex) {
    if (queryStart <= segmentStart && queryEnd >= segmentEnd) {
        return segmentTree[segmentIndex];
    }
    if (segmentEnd < queryStart || segmentStart > queryEnd) {
        return INT_MAX;
    }
    int mid = getMiddle(segmentStart, segmentEnd);
    return min(minUtil(segmentTree, segmentStart, mid, queryStart, queryEnd, 2 * segmentIndex + 1),
               minUtil(segmentTree, mid + 1, segmentEnd, queryStart, queryEnd, 2 * segmentIndex + 2));
}

int minVal(int *segmentTree, int n, int queryStart, int queryEnd) {
    return minUtil(segmentTree, 0, n - 1, queryStart, queryEnd, 0);
}

void setMaxValue(int arr[], int *segmentTree, int segmentStart, int segmentEnd, int index, int value, int node) {
    if (segmentStart == segmentEnd) {
        arr[index] = value;
        segmentTree[node] = value;
    } else {
        int mid = getMiddle(segmentStart, segmentEnd);
        if (index >= segmentStart && index <= mid) {
            setMaxValue(arr, segmentTree, segmentStart, mid, index, value, 2 * node + 1);
        } else {
            setMaxValue(arr, segmentTree, mid + 1, segmentEnd, index, value, 2 * node + 2);
        }
        segmentTree[node] = max(segmentTree[2 * node + 1], segmentTree[2 * node + 2]);
    }
}

void setMinValue(int arr[], int *segmentTree, int segmentStart, int segmentEnd, int index, int value, int node) {
    if (segmentStart == segmentEnd) {
        arr[index] = value;
        segmentTree[node] = value;
    } else {
        int mid = getMiddle(segmentStart, segmentEnd);
        if (index >= segmentStart && index <= mid) {
            setMinValue(arr, segmentTree, segmentStart, mid, index, value, 2 * node + 1);
        } else {
            setMinValue(arr, segmentTree, mid + 1, segmentEnd, index, value, 2 * node + 2);
        }
        segmentTree[node] = min(segmentTree[2 * node + 1], segmentTree[2 * node + 2]);
    }
}

signed main() {
    meow
    int n = 100001;
    int *minArr = new int[n];
    int *maxArr = new int[n];
    repeat(i, n) {
        minArr[i] = ((i) * (i)) % 12345 + ((i) * (i) * (i)) % 23456;
        maxArr[i] = ((i) * (i)) % 12345 + ((i) * (i) * (i)) % 23456;
    }
    int *segmentMinTree = buildMinSegmentTree(minArr, n);
    int *segmentMaxTree = buildMaxSegmentTree(maxArr, n);
    int k;
    cin >> k;
    int x, y;
    repeat(i, k) {
        cin >> x >> y;
        if (x > 0) {
            int max = maxVal(segmentMaxTree, n, x, y);
            int min = minVal(segmentMinTree, n, x, y);
            cout << max - min << endl;
        } else {
            x = abs(x);
            setMinValue(minArr, segmentMinTree, 0, n-1, x, y, 0);
            setMaxValue(maxArr, segmentMaxTree, 0, n-1, x, y, 0);
        }
    }
    delete[] minArr;
    delete[] maxArr;
    delete[] segmentMinTree;
    delete[] segmentMaxTree;
}