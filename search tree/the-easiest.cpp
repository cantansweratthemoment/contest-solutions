/*
 * Имеется 𝑁 наборов чисел, которые изначально известны.
 * Поступают 𝑄 запросов вида 𝑥 𝑦 𝑘, для выполнения запроса нужно взять все числа из набора под номером 𝑥, которые не меньше числа k, и переместить их в набор номер 𝑦.
 * После выполнения всех запросов необходимо вывести конечные состояния наборов.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

struct decartes {
    int x, y;
    decartes *left, *right;

    decartes(int x) : x(x), y(rand()), left(nullptr), right(nullptr) {}
};

vector<decartes *> trees;

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
    if (xSplit < tree->x) {
        auto splitTree = split(tree->left, xSplit);
        tree->left = splitTree.second;
        return {splitTree.first, tree};
    } else {
        auto splitTree = split(tree->right, xSplit);
        tree->right = splitTree.first;
        return {tree, splitTree.second};
    }
}

void insert(decartes *&tree, int x) {
    auto splitTree1 = split(tree, x);
    auto splitTree2 = split(splitTree1.second, x + 1);
    tree = merge(merge(splitTree1.first, new decartes(x)), splitTree2.second);
}

decartes *findMin(decartes *tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    if (tree->left == nullptr) {
        return tree;
    } else {
        return findMin(tree->left);
    }
}

void printTree(decartes *tree) {
    if (tree == nullptr) {
        return;
    }
    printTree(tree->left);
    cout << tree->x << " ";
    printTree(tree->right);
}

void sizeTree(decartes *tree, int &size) {
    if (tree == nullptr) {
        return;
    }
    sizeTree(tree->left, size);
    size++;
    sizeTree(tree->right, size);
}

signed main() {
    meow
    int N, Q;
    cin >> N >> Q;
    int k;
    repeat(i, N) {
        cin >> k;
        decartes *first = nullptr;
        int q;
        repeat(ii, k) {
            cin >> q;
            insert(first, q);
        }
        trees.push_back(first);
    }
    int x, y;
    repeat(i, Q) {
        cin >> x >> y >> k;
        x--;
        y--;
        decartes *mergeTree = nullptr;
        auto splitXTree = split(trees[x], k - 1);
        decartes *xTree = splitXTree.second;
        trees[x] = splitXTree.first;
        decartes *yTree = trees[y];
        while (true) {
            auto xMinNode = findMin(xTree);
            auto yMinNode = findMin(yTree);
            if (xMinNode == nullptr && yMinNode == nullptr) {
                break;
            }
            if (xMinNode == nullptr) {
                mergeTree = merge(mergeTree, yTree);
                break;
            }
            if (yMinNode == nullptr) {
                mergeTree = merge(mergeTree, xTree);
                break;
            }
            int xMin = xMinNode->x;
            int yMin = yMinNode->x;
            if (xMin < yMin) {
                auto splitTree = split(xTree, yMin);
                mergeTree = merge(mergeTree, splitTree.first);
                xTree = splitTree.second;
            } else {
                auto splitTree = split(yTree, xMin);
                mergeTree = merge(mergeTree, splitTree.first);
                yTree = splitTree.second;
            }
        }
        trees[y] = mergeTree;
    }
    repeat(i, trees.size()) {
        int size = 0;
        sizeTree(trees[i], size);
        cout << size << " ";
        printTree(trees[i]);
        cout << "\n";
    }
}