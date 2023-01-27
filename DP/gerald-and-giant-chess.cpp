/**
 * На Геральдионе очень распространены гигантские шахматы. Не будем углубляться в правила этой игры, скажем лишь, что игра происходит на поле размера h × w, и оно тоже раскрашено в два цвета, но не как в шахматах. Почти все клетки поля белые и только некоторые — чёрные. В данный момент Геральд заканчивает партию в гигантские шахматы против своего друга Полларда. Геральд почти выиграл, и для победы ему осталось только провести свою пешку из верхнего левого угла доски, где она сейчас стоит, в нижний правый. Геральд настолько уверен в победе, что ему стало интересно, сколькими способами он может выиграть?
 * Пешка, которая осталась у Геральда, может ходить двумя способами: на одну клетку вниз или на одну клетку вправо. Кроме того, она не может ходить на чёрные клетки, иначе Геральд всё-таки проиграет. Никаких других пешек или фигур на поле не осталось, так что, согласно правилам гигантских шахмат, Геральд ходит своей пешкой, пока игра не закончится, а Поллард просто наблюдает за этим процессом.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

const int FACTORIAL_N = 2 * 100000 + 1;
const int MOD = 1000000007;

vector<int> factorial(FACTORIAL_N);

int powerFast(int num, int deg) {
    int result = 1;
    while (deg) {
        if (deg % 2 == 0) {
            deg /= 2;
            num *= num;
            num %= MOD;
        } else {
            deg--;
            result *= num;
            result %= MOD;
        }
    }
    return result;
}

int smallFerma(int q) {
    return powerFast(q, MOD - 2);
}

struct cell {
    int x;
    int y;
};

int functionn(int x1, int x2, int y1, int y2) {
    int height = x2 - x1 + 1;
    int width = y2 - y1 + 1;
    return (factorial[height + width - 2] *
            smallFerma((factorial[width - 1] * factorial[height + width - 2 - width + 1]) % MOD)) % MOD;
}

signed main() {
    meow
    factorial[1] = 1;
    factorial[0] = 1;
    for (int i = 2; i < FACTORIAL_N; i++) {
        factorial[i] = (factorial[i - 1] * i) % MOD;
    }
    int h, w, n;
    cin >> h >> w >> n;
    vector<cell> blackCells(n + 1);
    int r, c;
    repeat(i, n) {
        cin >> r >> c;
        blackCells[i].x = c;
        blackCells[i].y = r;
    }
    blackCells[n].x = w;
    blackCells[n].y = h;
    sort(blackCells.begin(), blackCells.end(), [](cell q, cell w) {
        if (q.y == w.y) {
            return q.x < w.x;
        }
        return q.y < w.y;
    });
    n++;
    vector<int> f(n);
    repeat(i, n) {
        f[i] = functionn(1, blackCells[i].x, 1, blackCells[i].y) % MOD;
        repeat(j, i) {
            if (blackCells[j].x > blackCells[i].x) {
                continue;
            }
            f[i] -= f[j] * functionn(blackCells[j].x, blackCells[i].x, blackCells[j].y, blackCells[i].y);
            f[i] %= MOD;
        }
    }
    cout << (f[n - 1] % MOD + MOD) % MOD;
}