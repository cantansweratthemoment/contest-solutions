/**
 * На аллее перед зданием Министерства Обороны в ряд высажены n дубов. В связи с грядущим приездом главнокомандующего, было принято решение срубить несколько деревьев для придания аллее более милитаристического вида.
 * Внутренние распорядки министерства позволяют срубать дуб только в двух случаях:
 * если и ближайший дуб слева, и ближайший дуб справа строго ниже, чем данный дуб;
 * если и ближайший дуб слева, и ближайший дуб справа строго выше, чем данный дуб.
 * В частности, согласно этому правилу, нельзя срубить крайний левый и крайний правый дубы.
 * Министр хочет выработать такой план вырубки, чтобы в итоге осталось несколько дубов, высоты которых образуют неубывающую последовательность, то есть чтобы каждый дуб был не ниже, чем все дубы, стоящие слева от него. При этом, как человек любящий флору, министр хочет, чтобы было срублено минимальное возможное количество деревьев.
 * Помогите сотрудникам министерства составить оптимальный план вырубки аллеи или выяснить, что срубить дубы соответствующим образом невозможно.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

const int minimum = INT_MAX - 1000;

bool canCut(int iHeight, int jHeight, int kHeight) {
    return (iHeight < kHeight && jHeight < kHeight) || (iHeight > kHeight && jHeight > kHeight);
}

void cut(int i, int j, vector<int> &trees, vector<vector<bool>> &can) {
    for (int k = i + 1; k < j; k++) {
        if (can[i][k] && can[k][j] && canCut(trees[i], trees[j], trees[k])) {
            cut(i, k, trees, can);
            cut(k, j, trees, can);
            cout << k + 1 << "\n";
            break;
        }
    }
}

signed main() {
    meow
    int n;
    cin >> n;
    vector<int> trees;
    int q;
    repeat(i, n) {
        cin >> q;
        trees.push_back(q);
    }
    vector<vector<bool>> can(n, vector<bool>(n));
    for (int l = 1; l <= n; l++) {
        for (int i = 0; i + l <= n; i++) {
            int j = i + l - 1;
            if (l == 1 || l == 2) {
                can[i][j] = true;
                continue;
            }
            for (int k = i + 1; k < j; k++) {
                if (can[i][k] && can[k][j] && canCut(trees[i], trees[j], trees[k])) {
                    can[i][j] = true;
                    break;
                }
            }
        }
    }
    vector<int> f(n, minimum);
    vector<int> p(n, -1);
    f[0] = 0;
    for (int j = 1; j < n; j++) {
        for (int i = j - 1; i >= 0; i--) {
            if (trees[j] >= trees[i] && can[i][j]) {
                if (f[j] > f[i] + j - i - 1) {
                    f[j] = f[i] + j - i - 1;
                    p[j] = i;
                }
            }
        }
    }
    if (f[n - 1] == minimum) {
        cout << -1;
    } else {
        cout << f[n - 1] << "\n";
        int k = n - 1;
        while (p[k] != -1) {
            cut(p[k], k, trees, can);
            k = p[k];
        }
    }
}