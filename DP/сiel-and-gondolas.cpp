 /**
  * Лиса Ciel зашла в парк аттракционов. И вот, она в очереди на колесо обозрения. В очереди стоит n людей (хотя нет, скорее лис): мы будем считать, что первая лиса стоит в начале очереди, а n-ая лиса стоит в хвосте очереди.
  * Всего имеется k гондол, мы распределяем лис по гондолам следующим образом:
  * Когда подплывает первая гондола, q1 лис переходят из начала очереди в подплывшую гондолу.
  * Затем, когда подплывает вторая гондола, q2 лис из начала оставшейся очереди переходит в эту гондолу.
  * ...
  * Оставшиеся qk лис идут с последнюю (k-ую) гондолу.
  * Обратите внимание, что числа q1, q2, ..., qk должны быть положительные. Из условия следует, что  и qi > 0.
  * Вы знаете как лисам не хочется задерживаться в гондолах с незнакомцами. Итак, Ваша задача — найти оптимальный способ размещения (то есть определить оптимальную последовательность q), чтобы угодить всем. Для каждой пары лис i и j задано значение uij, обозначающее степень незнакомости. Можете считать, что uij = uji для всех i, j (1 ≤ i, j ≤ n) и что uii = 0 для всех i (1 ≤ i ≤ n). Тогда значение незнакомости в гондоле определяется как сумма значений незнакомости между всеми парами лис, которые находятся в этой гондоле. Общее значение незнакомости определяется как сумма значений незнакомости по всем гондолам.
  * Помогите лисе Ciel найти минимальное возможное значение общей незнакомости при некотором оптимальном распределении лис по гондолам.
  */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

const int N = 4001;

vector<vector<int>> cost(N, vector<int>(N, 0));
vector<vector<int>> f(N, vector<int>(N));
int n, d;

int recalculateCost(int i, int j) {
    return cost[j][j] - cost[j][i - 1] - cost[i - 1][j] + cost[i - 1][i - 1];
}

int calculate(int i, int j, int left, int right) {
    f[i][j] = INT_MAX;
    int result = left;
    for (int k = left; k <= right; k++) {
        int q = f[i - 1][k] + recalculateCost(k + 1, j);
        if (q < f[i][j]) {
            f[i][j] = q;
            result = k;
        }
    }
    return result;
}

void findOpt(int i, int left, int right, int oLeft, int oRight) {
    if (left > right) {
        return;
    }
    if (left == right) {
        calculate(i, left, oLeft, oRight);
        return;
    }
    oRight = min(oRight, right - 1);
    if (oLeft == oRight) {
        for (int k = left; k <= right; k++) {
            calculate(i, k, oLeft, oRight);
        }
        return;
    }
    int middle = (left + right) / 2;
    int opt = calculate(i, middle, oLeft, oRight);
    findOpt(i, left, middle - 1, oLeft, opt);
    findOpt(i, middle + 1, right, opt, oRight);
}

int main() {
    meow
    cin >> n >> d;
    int q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> q;
            cost[i][j] = q;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] += cost[i - 1][j] + cost[i][j - 1] - cost[i - 1][j - 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        f[1][i] = recalculateCost(1, i);
    }
    for (int i = 2; i <= d; i++) {
        findOpt(i, 2, n, i - 1, n);
    }
    cout << f[d][n] / 2 << endl;
    return 0;
}
