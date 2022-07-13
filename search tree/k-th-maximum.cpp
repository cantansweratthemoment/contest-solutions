/*
 * Напишите программу, реализующую структуру данных, позволяющую добавлять и удалять элементы, а также находить 𝑘-й максимум.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

struct decartes {
    int x, y, size;
    decartes *left, *right;

    decartes(int x) : x(x), y(rand()), left(nullptr), right(nullptr), size(1) {}
};

int size(decartes *tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->size;
    }
}

decartes *propagate(decartes *tree) {
    if (tree == nullptr) {
        return tree;
    }
    tree->size = size(tree->left) + size(tree->right) + 1;
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
        A->right = merge(propagate(A->right), propagate(B));
        return propagate(A);
    } else {
        B->left = merge(propagate(A), propagate(B->left));
        return propagate(B);
    }
}

pair<decartes *, decartes *> split(decartes *tree, int xSplit) {
    if (tree == nullptr) {
        return {tree, tree};
    }
    if (xSplit <= tree->x) {
        auto splitTree = split(tree->left, xSplit);
        tree->left = splitTree.second;
        return {propagate(splitTree.first), propagate(tree)};
    } else {
        auto splitTree = split(tree->right, xSplit);
        tree->right = splitTree.first;
        return {propagate(tree), propagate(splitTree.second)};
    }
}

void insert(decartes *&tree, int x) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(merge(splitTree1.first, new decartes(x)), splitTree2.second);
}

void erase(decartes *&tree, int x) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(splitTree1.first, splitTree2.second);
}

decartes *find(decartes *tree, int k) {
    if (tree == nullptr) {
        return nullptr;
    }
    if (size(tree->right) == k - 1) {
        return tree;
    } else if (size(tree->right) > k - 1) {
        return find(tree->right, k);
    } else {
        return find(tree->left, k - size(tree->right) - 1);
    }
}

signed main() {
    meow
    decartes *first = nullptr;
    int n, k;
    string command;
    cin >> n;
    repeat(i, n) {
        cin >> command >> k;
        if (command == "+1" || command == "1") {
            insert(first, k);
        } else if (command == "0") {
            cout << find(first, k)->x << "\n";
        } else if (command == "-1") {
            erase(first, k);
        }
    }
}