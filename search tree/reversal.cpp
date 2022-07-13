/*
 * Дан массив. Надо научиться обрабатывать два типа запросов.
 * 1 L R - перевернуть отрезок [𝐿, 𝑅]
 * 2 L R - найти минимум на отрезке [𝐿, 𝑅]
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

struct decartes {
    int x, y, size, min;
    bool reversed;
    decartes *left, *right;

    decartes(int x, int min) : x(x), y(rand()), left(nullptr), right(nullptr), size(1), min(min), reversed(false) {}
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

decartes *push(decartes *tree) {
    if (tree) {
        if (tree->reversed) {
            swap(tree->left, tree->right);
            if (tree->left) {
                tree->left->reversed = !tree->left->reversed;
            }
            if (tree->right) {
                tree->right->reversed = !tree->right->reversed;
            }
        }
        tree->reversed = false;
    }
    return tree;
}

decartes *merge(decartes *A, decartes *B) {
    if (A == nullptr) {
        return B;
    }
    if (B == nullptr) {
        return A;
    }
    A = push(A);
    B = push(B);
    if (A->y > B->y) {
        A->right = merge(update(A->right), update(B));
        return push(update(A));
    } else {
        B->left = merge(update(A), update(B->left));
        return push(update(B));
    }
}

pair<decartes *, decartes *> split(decartes *tree, int k) {
    tree = push(tree);
    if (tree == nullptr) {
        return {tree, tree};
    }
    if (k <= size(tree->left)) {
        auto splitTree = split(tree->left, k);
        tree->left = update(splitTree.second);
        return {push(update(splitTree.first)), push(update(tree))};
    } else {
        auto splitTree = split(tree->right, k - size(tree->left) - 1);
        tree->right = update(splitTree.first);
        return {push(update(tree)), push(update(splitTree.second))};
    }
}

void insert(decartes *&tree, int i, int x) {
    auto splitTree1 = split(tree, i);
    tree = merge(merge(splitTree1.first, new decartes(x, x)), splitTree1.second);
}

void reverse(int left, int right, decartes *&tree) {
    auto splitTree1 = split(tree, right);
    auto splitTree2 = split(splitTree1.first, left);
    if (splitTree2.second) {
        splitTree2.second->reversed = !splitTree2.second->reversed;
    }
    tree = merge(splitTree2.first, merge(splitTree2.second, splitTree1.second));
}

int findMin(decartes *&tree, int left, int right) {
    auto splitTree1 = split(tree, left - 1);
    auto splitTree2 = split(splitTree1.second, right - left + 1);
    int answer = minValue(splitTree2.first);
    tree = merge(splitTree1.first, merge(splitTree2.first, splitTree2.second));
    return answer;
}

signed main() {
    meow
    decartes *first = nullptr;
    int n, m;
    cin >> n >> m;
    int a;
    repeat(i, n) {
        cin >> a;
        insert(first, i + 1, a);
    }
    int command, L, R;
    repeat(i, m) {
        cin >> command >> L >> R;
        if (command == 1) {
            reverse(--L, R, first);
        } else {
            cout << findMin(first, L, R) << "\n";
        }
    }
}