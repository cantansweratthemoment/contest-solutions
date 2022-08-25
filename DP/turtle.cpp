/**
 * В левом верхнем углу прямоугольной таблицы размером 𝑛×𝑚 находится черепашка. Она хочет попасть в правый нижний угол к своей любимой семье. У неё есть своя особенность: черепашка умеет ходить лишь вправо, либо вниз.
 * За нахождение в клетке, находящейся на пересечении 𝑖-й строки и 𝑗-го столбца, на черепашку накладывается штраф в размере 𝑎𝑖𝑗 рублей. Естественно, черепашка хочет дойти до семьи с минимальным суммарным штрафом. Помогите ей сделать это.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

vector<vector<int>> penalty;
vector<vector<int>> f;

signed main() {
    meow
    int N, M;
    cin >> N >> M;
    penalty.resize(N);
    int q;
    repeat(i, N) {
        repeat(j, M) {
            cin >> q;
            penalty[i].push_back(q);
        }
    }
    f.resize(N);
    repeat(i, N) {
        f[i].resize(M);
    }
    f[0][0] = penalty[0][0];
    for (int i = 1; i < M; i++) {
        f[0][i] = f[0][i - 1] + penalty[0][i];
    }

    for (int i = 1; i < N; i++) {
        f[i][0] = f[i - 1][0] + penalty[i][0];
    }
    if (N != 1 && M != 1) {
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < M; j++) {
                f[i][j] = min(f[i - 1][j], f[i][j - 1]) + penalty[i][j];
            }
        }
    }
    cout << f[N - 1][M - 1];
}