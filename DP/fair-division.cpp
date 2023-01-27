/**
 * — Я хотел честно, — сказал Балаганов, собирая деньги с кровати, — по справедливости.
 * В коробке от сигарет «Кавказ», отнятой у Корейко, было всего 1≤𝑁≤15 купюр, каждая номиналом 1≤𝑎𝑖≤103. Разделить надо было на 1≤𝐾≤100 частей, причём известно, что общая сумма делится на 𝐾.
 * Метод деления «по справедливости» следующий: если разделить поровну не получается, то делить следует так, чтобы среднеквадратичное отклонение было минимальным.
 * Среднеквадратичное отклонение для данного способа дележа определяется следующим образом. Пусть 𝑖-й человек получил сумму денег, равную 𝑆𝑖. Обозначим за 𝑀 среднее арифметическое сумм денег, полученных каждым: 𝑀=(∑𝐾𝑖=1𝑆𝑖)/𝐾. Тогда среднеквадратичное отклонение можно вычислить так: 𝜎=(∑𝐾𝑖=1(𝑆𝑖−𝑀)2)/𝐾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾√
 * — И как? — поинтересовался Остап.
 * — Сложно... — вздохнул Шура.
 * Попробуйте и вы разделить деньги «по справедливости».
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

signed main() {
    meow
    int N, K;
    cin >> N >> K;
    vector<int> bills;
    int a;
    double M = 0;
    repeat(i, N) {
        cin >> a;
        M += a;
        bills.push_back(a);
    }
    M /= K;
    vector<double> fMask(1 << N);
    for (int mask = 0; mask < 1 << N; mask++) {
        int sum = 0;
        repeat(i, N) {
            if (mask & (1 << i)) {
                sum += bills[i];
            }
        }
        fMask[mask] = (sum - M) * (sum - M);
    }
    vector<vector<double>> f(K + 1, vector<double>(1 << N, INT_MAX));
    vector<vector<int>> p(K + 1, vector<int>(1 << N, 0));
    repeat(i, 1 << N) {
        f[1][i] = fMask[i];
        p[1][i] = i;
    }
    for (int k = 2; k < K + 1; k++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            for (int maskSmall = mask; maskSmall != 0; maskSmall = (maskSmall - 1) & mask) {
                int maskSmall2 = mask ^ maskSmall;
                if (f[k - 1][maskSmall] + fMask[maskSmall2] < f[k][mask]) {
                    f[k][mask] = f[k - 1][maskSmall] + fMask[maskSmall2];
                    p[k][mask] = maskSmall2;
                }
            }
        }
    }
    vector<int> who(N, 0);
    int BIGMASK = (1 << N) - 1;
    for (int k = K; k > 0; k--) {
        int MASKSMALL = p[k][BIGMASK];
        for (int i = 0; i < N; i++) {
            if (MASKSMALL & (1 << i)) {
                who[i] = k;
            }
        }
        BIGMASK ^= MASKSMALL;
    }
    cout << fixed << setprecision(8) << sqrt(((f[K][(1 << N) - 1]) / K)) << "\n";
    repeat(i, N) {
        cout << who[i] << " ";
    }
}