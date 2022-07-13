/*
 * Перед возвращением в штаб-квартиру корпорации Аазу и Скиву пришлось заполнить на местной таможне декларацию о доходах за время визита. Получилась довольно внушительная последовательность чисел. Обработка этой последовательности заняла весьма долгое время.
 * — Своппер кривой, — со знанием дела сказал таможенник.
 * — А что такое своппер? — спросил любопытный Скив.
 * Ааз объяснил, что своппер — это структура данных, которая умеет делать следующее.
 * Взять отрезок чётной длины от 𝑥 до 𝑦 и поменять местами число 𝑥 с 𝑥+1, 𝑥+2 с 𝑥+3, и т.д.
 * Посчитать сумму чисел на произвольном отрезке от 𝑎 до 𝑏.
 * Учитывая, что обсчёт может затянуться надолго, корпорация «МИФ» попросила Вас решить проблему со своппером и промоделировать ЭТО эффективно.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

struct decartes {
    int x, y, size, sum;
    decartes *left, *right;

    decartes(int x) : x(x), y(rand()), left(nullptr), right(nullptr), size(1), sum(x) {}
};

int size(decartes *tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->size;
    }
}

int sum(decartes *tree) {
    if (tree == nullptr) {
        return 0;
    } else {
        return tree->sum;
    }
}

decartes *update(decartes *tree) {
    if (tree == nullptr) {
        return tree;
    }
    tree->size = size(tree->left) + size(tree->right) + 1;
    tree->sum = sum(tree->left) + sum(tree->right) + tree->x;
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

void insert(decartes *&tree, int x) {
    tree = merge(tree, new decartes(x));
}

int getSum(int left, int right, decartes *&tree) {
    auto split1 = split(tree, left);
    auto split2 = split(split1.second, right - left + 1);
    int result = sum(split2.first);
    auto mergeTree = merge(split2.first, split2.second);
    merge(split1.first, mergeTree);
    return result;
}

void swap(int left, int right, decartes *&first, decartes *&second) {
    auto split1 = split(first, left / 2);
    auto split2 = split(split1.second, (right + 1) / 2 - left / 2);
    auto split3 = split(second, (left + 1) / 2);
    auto split4 = split(split3.second, right / 2 + 1 - (left + 1) / 2);
    first = merge(merge(split1.first, split4.first), split2.second);
    second = merge(merge(split3.first, split2.first), split4.second);
}

signed main() {
    meow
    int N, M;
    cin >> N >> M;
    int ii = 1;
    int command, a, b, sumResult;
    int q;
    while (!(N == 0 && M == 0)) {
        decartes *first = nullptr;
        decartes *second = nullptr;
        cout << "Swapper " << ii << ":\n";
        repeat(i, N) {
            cin >> q;
            if (i % 2 == 1) {
                insert(first, q);
            } else {
                insert(second, q);
            }
        }
        repeat(i, M) {
            cin >> command >> a >> b;
            a--;
            b--;
            if (command == 1) {
                swap(a, b, first, second);
            } else {
                sumResult = getSum(a / 2, (b + 1) / 2 - 1, first) + getSum((a + 1) / 2, b / 2, second);
                cout << sumResult << "\n";
            }
        }
        cin >> N >> M;
        cout << "\n";
        ii++;
    }
}