/**
Итальянский художник-абстракционист Ф. Мандарино увлекся рисованием одномерных черно-белых картин. Он пытается найти оптимальное местоположение и количество черных участков картины. Для этого он проводит на прямой белые и черные отрезки, и после каждой из таких операций хочет знать количество черных отрезков на получившейся картине и их суммарную длину.
Изначально прямая — белая. Ваша задача — написать программу, которая после каждой из таких операций выводит в выходной файл интересующие художника данные.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

#define N_MAX 1000002
#define BLACK 1
#define WHITE 0

struct node {
    int colorValue = WHITE;
    int lazy = 0;
    bool isLazy = false;
    int segmentValue = 0;
};

struct input {
    string c;
    int x;
    int l;
};

node segmentTree[N_MAX * 4];

int getMiddle(int start, int end) {
    return start + (end - start) / 2;
}

void push(int i, int segmentStart, int segmentEnd) {
    if (segmentTree[i].isLazy) {
        segmentTree[i].colorValue = (segmentEnd - segmentStart + 1) * segmentTree[i].lazy;
        segmentTree[i].segmentValue = segmentTree[i].lazy;
        if (segmentStart != segmentEnd) {
            segmentTree[i * 2].lazy = segmentTree[i].lazy;
            segmentTree[i * 2].isLazy = true;
            segmentTree[i * 2 + 1].lazy = segmentTree[i].lazy;
            segmentTree[i * 2 + 1].isLazy = true;
        }
        segmentTree[i].isLazy = false;
    }
}

bool isLeftSegmentBlack(int i, int segmentStart, int segmentEnd) {
    push(i, segmentStart, segmentEnd);
    if (segmentStart == segmentEnd) {
        return segmentTree[i].colorValue == BLACK;
    }
    int middle = getMiddle(segmentStart, segmentEnd);
    return isLeftSegmentBlack(i * 2, segmentStart, middle);
}

bool isRightSegmentBlack(int i, int segmentStart, int segmentEnd) {
    push(i, segmentStart, segmentEnd);
    if (segmentStart == segmentEnd) {
        return segmentTree[i].colorValue == BLACK;
    }
    int middle = getMiddle(segmentStart, segmentEnd);
    return isRightSegmentBlack(i * 2 + 1, middle + 1, segmentEnd);
}

void update(int i, int segmentStart, int segmentEnd, int queryStart, int queryEnd, int value) {
    if (queryStart > segmentEnd || queryEnd < segmentStart) {
        return;
    }

    if (segmentStart >= queryStart && segmentEnd <= queryEnd) {
        push(i, segmentStart, segmentEnd);
        segmentTree[i].lazy = value;
        segmentTree[i].isLazy = true;
        return;
    }

    push(i, segmentStart, segmentEnd);

    int middle = getMiddle(segmentStart, segmentEnd);
    update(i * 2, segmentStart, middle, queryStart, queryEnd, value);
    update(i * 2 + 1, middle + 1, segmentEnd, queryStart, queryEnd, value);
    bool isLBlack = isLeftSegmentBlack(i * 2 + 1, middle + 1, segmentEnd);
    bool isRBlack = isRightSegmentBlack(i * 2, segmentStart, middle);
    segmentTree[i].segmentValue = segmentTree[i * 2].segmentValue + segmentTree[i * 2 + 1].segmentValue;
    segmentTree[i].colorValue = segmentTree[i * 2].colorValue + segmentTree[i * 2 + 1].colorValue;
    if (isLBlack && isRBlack) {
        if (segmentTree[i].segmentValue != 0) {
            segmentTree[i].segmentValue--;
        }
    }
}

void build(int i, int segmentStart, int segmentEnd) {
    if (segmentStart == segmentEnd) {
        segmentTree[i].colorValue = 0;
        segmentTree[i].lazy = 0;
        segmentTree[i].isLazy = false;
        segmentTree[i].segmentValue = 0;
        return;
    }

    int middle = getMiddle(segmentStart, segmentEnd);
    build(i * 2, segmentStart, middle);
    build(i * 2 + 1, middle + 1, segmentEnd);
    segmentTree[i].colorValue = segmentTree[i * 2].colorValue + segmentTree[i * 2 + 1].colorValue;
}


signed main() {
    meow
    int N, x, l;
    string c;
    cin >> N;
    build(1, 1, N_MAX);
    input input[N];
    repeat(i, N) {
        cin >> input[i].c;
        cin >> input[i].x;
        cin >> input[i].l;
    }
    repeat(i, N) {
        c = input[i].c;
        x = input[i].x;
        l = input[i].l;
        if (c == "W") {
            update(1, 1, N_MAX, x + 500001, x + 500001 + l - 1, WHITE);
        } else {
            update(1, 1, N_MAX, x + 500001, x + 500001 + l - 1, BLACK);
        }
        cout << segmentTree[1].segmentValue << " " << segmentTree[1].colorValue << endl;

    }
}