/**
 * Для того чтобы написать строку, Atilla должен сначала выучить все буквы, которые содержатся в строке.
 * Он хочет написать сообщение 𝑠. Он просит вас узнать минимальный размер алфавита, который ему предстоит выучить, чтобы он смог написать эту всю эту строку.
 * Алфавит размером 𝑥 (1≤𝑥≤26) содержит только первые 𝑥 латинских букв.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

int alphabet(int n) {
    char q;
    int max = 0;
    repeat(i, n) {
        cin >> q;
        if (q - 'a' > max) {
            max = q - 'a';
        }
    }
    return ++max;
}

signed main() {
    meow
    int t, n;
    cin >> t;
    repeat(i, t) {
        cin >> n;
        cout << alphabet(n) << "\n";
    }
}