/**
 * Вам дан массив 𝑎[0…𝑛−1] из 𝑛 целых чисел. Этот массив называется «долиной», если существует ровно один подмассив 𝑎[𝑙…𝑟] такой, что:
 * 0≤𝑙≤𝑟≤𝑛−1
 * 𝑎𝑙=𝑎𝑙+1=𝑎𝑙+2=⋯=𝑎𝑟
 * или 𝑎𝑙−1>𝑎𝑙, 𝑟=𝑛−1 мне лень писать условие дальше
 */

#include <iostream>
#include <vector>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

bool checkArray(const vector<int> &a) {
    int n = a.size();
    int l = 0;
    int r = 0;
    bool flag = false;
    int count = 0;
    while (r < n) {
        if (a[l] != a[r]) {
            if (l == r) {
                r++;
            }
            l = r;
            flag = false;
            continue;
        }
        if (l != 0 && a[l - 1] <= a[l]) {
            l++;
            if (l > r) {
                r = l;
            }
            flag = false;
            continue;
        }
        if (r != (n - 1) && a[r] >= a[r + 1]) {
            r++;
            flag = false;
            continue;
        }
        if (!flag) {
            flag = true;
            count++;
            r++;
            l = r;
        }
    }
    return count == 1;
}

signed main() {
    meow
    int t, n, ai;
    cin >> t;
    repeat(i, t) {
        cin >> n;
        vector<int> a;
        repeat(ii, n) {
            cin >> ai;
            a.push_back(ai);
        }
        if (checkArray(a)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}