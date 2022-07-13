/*
 * Реализуйте структуру данных, которая поддерживает множество 𝑆 целых чисел, с котором разрешается производить следующие операции:
 * 𝑎𝑑𝑑(𝑖) — добавить в множество 𝑆 число 𝑖 (если он там уже есть, то множество не меняется);
 * 𝑠𝑢𝑚(𝑙,𝑟) — вывести сумму всех элементов 𝑥 из 𝑆, которые удовлетворяют неравенству 𝑙≤𝑥≤𝑟.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

struct decartes {
    int x, y, value, sum;
    decartes *left, *right;

    decartes(int x, int value) : x(x), y(rand()), value(value), left(nullptr), right(nullptr), sum(value) {}
};

int sum(decartes *tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->sum;
    }
}

decartes *propagate(decartes *tree) {
    if (tree == nullptr) {
        return tree;
    }
    tree->sum = sum(tree->left) + sum(tree->right) + tree->value;
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

void insert(decartes *&tree, int x, int value) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(merge(splitTree1.first, new decartes(x, value)), splitTree2.second);
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

signed main() {
    meow
    auto first = new decartes(0, 0);
    int n, i, l, r;
    int y = 0;
    string command;
    cin >> n;
    bool flag = false;
    repeat(j, n) {
        cin >> command;
        if (command == "+") {
            cin >> i;
            if (flag) {
                i = (i + y) % 1000000000;
            }
            if (find(first, i) == nullptr) {
                insert(first, i, i);
            }
            flag = false;
        } else {
            flag = true;
            cin >> l >> r;
            auto split1 = split(first, l);
            auto split2 = split(split1.second, r + 1);
            y = sum(split2.first);
            auto mergeTree = merge(split2.first, split2.second);
            merge(split1.first, mergeTree);
            cout << y << endl;
        }
    }
}