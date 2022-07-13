/*
 * Реализуйте сбалансированное двоичное дерево поиска.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
//#define int long long

struct decartes {
    int x, y, value;
    decartes *left, *right;

    decartes(int x, int value) : x(x), y(rand()), value(value), left(nullptr), right(nullptr) {}
};

decartes *merge(decartes *A, decartes *B) {
    if (A == nullptr) {
        return B;
    }
    if (B == nullptr) {
        return A;
    }
    if (A->y > B->y) {
        A->right = merge(A->right, B);
        return A;
    } else {
        B->left = merge(A, B->left);
        return B;
    }
}

pair<decartes *, decartes *> split(decartes *tree, int xSplit) {
    if (tree == nullptr) {
        return {tree, tree};
    }
    if (xSplit <= tree->x) {
        auto splitTree = split(tree->left, xSplit);
        tree->left = splitTree.second;
        return {splitTree.first, tree};
    } else {
        auto splitTree = split(tree->right, xSplit);
        tree->right = splitTree.first;
        return {tree, splitTree.second};
    }
}

void insert(decartes *&tree, int x, int value) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(merge(splitTree1.first, new decartes(x, value)), splitTree2.second);
}

void erase(decartes *&tree, int x) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(splitTree1.first, splitTree2.second);
}

decartes *find(decartes *tree, int x) {
    if (tree == nullptr) {
        return nullptr;
    }
    if (x == tree->x) {
        return tree;
    } else if (x < tree->x) {
        return find(tree->left, x);
    } else {
        return find(tree->right, x);
    }
}

int next(decartes *tree, int x, int min) {
    if (tree == nullptr) {
        return min;
    } else if (tree->x > x) {
        if (tree->x < min) {
            min = tree->x;
        }
        return next(tree->left, x, min);
    } else {
        return next(tree->right, x, min);
    }
}

int prev(decartes *tree, int x, int max) {
    if (tree == nullptr) {
        return max;
    } else if (tree->x >= x) {
        return prev(tree->left, x, max);
    } else {
        if (tree->x > max) {
            max = tree->x;
        }
        return prev(tree->right, x, max);
    }
}

signed main() {
    meow
    string command;
    int x;
    auto first = new decartes(1000000001, 1000000001);
    while (cin >> command) {
        cin >> x;
        if (command == "insert") {
            if (find(first, x) == nullptr) {
                insert(first, x, x);
            }
        } else if (command == "delete") {
            if (find(first, x) != nullptr) {
                erase(first, x);
            }
        } else if (command == "exists") {
            if (find(first, x) == nullptr) {
                cout << "false" << endl;
            } else {
                cout << "true" << endl;
            }
        } else if (command == "next") {
            int result = next(first, x, INT_MAX);
            if (result == INT_MAX || result == 1000000001) {
                cout << "none" << endl;
            } else {
                cout << result << endl;
            }
        } else {
            int result = prev(first, x, INT_MIN);
            if (result == INT_MIN) {
                cout << "none" << endl;
            } else {
                cout << result << endl;
            }
        }
    }
    return 0;
}