/**
 * Вам дан бинарный массив† длины 𝑛. Вам можете выполнить над ним следующую операцию не более одного раза. Операция заключается в следующем — вы можете выбрать любой элемент и инвертировать его: превратить 0 в 1 или наоборот.
 * Какое максимальное количество инверсий ‡ может иметь массив после выполнения не более одной операции?
 */

#include <iostream>
#include <vector>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

int countInversions(const vector<int> &a) {
    int counter = 0;
    int oneCounter = 0;
    repeat(i, a.size()) {
        if (a[i] == 1) {
            oneCounter++;
        } else {
            counter += oneCounter;
        }
    }
    return counter;
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
        int counter1, counter2, counter3;
        counter1 = countInversions(a);
        int index = 0;
        bool flag = false;
        repeat(ii, n) {
            if (a[ii] == 1) {
                index = ii;
                flag = true;
            }
        }
        if (flag) {
            a[index] = 0;
            counter2 = countInversions(a);
            a[index] = 1;
        } else {
            counter2 = INT_MIN;
        }
        repeat(ii, n) {
            if (a[ii] == 0) {
                a[ii] = 1;
                break;
            }
        }
        counter3 = countInversions(a);
        cout << max(max(counter1, counter2), counter3) << "\n";
    }
}