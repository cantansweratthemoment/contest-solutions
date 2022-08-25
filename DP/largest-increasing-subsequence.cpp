/**
 * Дана последовательность, требуется найти её наибольшую возрастающую подпоследовательность.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

signed main() {
    meow
    int n;
    cin >> n;
    vector<int> arr;
    int q;
    repeat(i, n) {
        cin >> q;
        arr.push_back(q);
    }
    vector<int> p(n, INT_MIN);
    vector<int> f(n, 1);
    repeat(i, n) {
        repeat(j, i) {
            if (f[j] + 1 > f[i] && arr[i] > arr[j]) {
                p[i] = j;
                f[i] = f[j] + 1;
            }
        }
    }
    int size = f[0];
    int answerI = 0;
    repeat(i, n) {
        if (f[i] > size) {
            answerI = i;
            size = f[i];
        }
    }
    int j = answerI;
    vector<int> result;
    while (j != INT_MIN) {
        result.push_back(arr[j]);
        j = p[j];
    }
    reverse(result.begin(), result.end());
    cout << size << "\n";
    repeat(i, result.size()) {
        cout << result[i] << " ";
    }
}