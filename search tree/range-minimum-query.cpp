/*
 * Компания Giggle открывает свой новый офис в Судиславле, и вы приглашены на собеседование. Ваша задача — решить поставленную задачу.
 * Вам нужно создать структуру данных, которая представляет из себя массив целых чисел. Изначально массив пуст. Вам нужно поддерживать две операции:
 * запрос: «? i j» — возвращает минимальный элемент между 𝑖-ым и 𝑗-м, включительно;
 * изменение: «+ i x» — добавить элемент 𝑥 после 𝑖-го элемента списка. Если 𝑖=0, то элемент добавляется в начало массива.
 * Конечно, эта структура должна быть достаточно хорошей.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

struct decartes {
    int x, y, size, min;
    decartes *left, *right;

    decartes(int x, int min) : x(x), y(rand()), left(nullptr), right(nullptr), size(1), min(min) {}
};

int size(decartes *tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->size;
    }
}

int minValue(decartes *tree) {
    if (tree == nullptr) {
        return INT_MAX;
    } else {
        return tree->min;
    }
}

decartes *update(decartes *tree) {
    if (tree == nullptr) {
        return tree;
    }
    tree->size = size(tree->left) + size(tree->right) + 1;
    tree->min = min(min(minValue(tree->left), minValue(tree->right)), tree->x);
    return tree;
}

decartes *merge(decartes *A, decartes *B) {
    if (A == nullptr) {
        return B;
    }
    if (B == nullptr) {
        return A;
    }
    if (A->y > B->y) {
        A->right = merge(update(A->right), update(B));
        return update(A);
    } else {
        B->left = merge(update(A), update(B->left));
        return update(B);
    }
}

pair<decartes *, decartes *> split(decartes *tree, int k) {
    if (tree == nullptr) {
        return {tree, tree};
    }
    if (k <= size(tree->left)) {
        auto splitTree = split(tree->left, k);
        tree->left = update(splitTree.second);
        return {update(splitTree.first), update(tree)};
    } else {
        auto splitTree = split(tree->right, k - size(tree->left) - 1);
        tree->right = update(splitTree.first);
        return {update(tree), update(splitTree.second)};
    }
}

void insert(decartes *&tree, int i, int x) {
    auto splitTree1 = split(tree, i);
    tree = merge(merge(splitTree1.first, new decartes(x, x)), splitTree1.second);
}

int findMin(decartes *tree, int left, int right) {
    auto splitTree1 = split(tree, left - 1);
    auto splitTree2 = split(splitTree1.second, right - left + 1);
    int answer = minValue(splitTree2.first);
    merge(splitTree1.first, merge(splitTree2.first, splitTree2.second));
    return answer;
}

signed main() {
    meow
    decartes *first = nullptr;
    int n;
    cin >> n;
    string command;
    int i, j, x;
    repeat(q, n) {
        cin >> command;
        if (command == "?") {
            cin >> i >> j;
            cout << findMin(first, i, j) << "\n";
        } else {
            cin >> i >> x;
            insert(first, i, x);
        }
    }
}