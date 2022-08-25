/**
 * За билетами на премьеру нового мюзикла выстроилась очередь из N человек, каждый из которых хочет купить 1 билет. На всю очередь работала только одна касса, поэтому продажа билетов шла очень медленно, приводя «постояльцев» очереди в отчаяние. Самые сообразительные быстро заметили, что, как правило, несколько билетов в одни руки кассир продаёт быстрее, чем когда эти же билеты продаются по одному. Поэтому они предложили нескольким подряд стоящим людям отдавать деньги первому из них, чтобы он купил билеты на всех.
 * Однако для борьбы со спекулянтами кассир продавала не более 3-х билетов в одни руки, поэтому договориться таким образом между собой могли лишь 2 или 3 подряд стоящих человека.
 * Известно, что на продажу i-му человеку из очереди одного билета кассир тратит Ai секунд, на продажу двух билетов — Bi секунд, трех билетов — Ci секунд. Напишите программу, которая подсчитает минимальное время, за которое могли быть обслужены все покупатели.
 * Обратите внимание, что билеты на группу объединившихся людей всегда покупает первый из них. Также никто в целях ускорения не покупает лишних билетов (то есть билетов, которые никому не нужны).
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

signed main() {
    meow
    vector<int> A;
    vector<int> B;
    vector<int> C;
    vector<int> f;
    int N;
    cin >> N;
    int a, b, c;
    repeat(i, N) {
        cin >> a >> b >> c;
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
    }
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    reverse(C.begin(), C.end());
    f.resize(N);
    f[0] = min(min(A[0], B[0]), C[0]);
    f[1] = min(min(f[0] + A[1], B[1]), C[1]);
    f[2] = min(min(f[1] + A[2], B[2] + f[0]), C[2]);
    for (int i = 3; i < N; i++) {
        f[i] = min(min(f[i - 3] + C[i], f[i - 2] + B[i]), f[i - 1] + A[i]);
    }
    cout << f[N - 1];
}