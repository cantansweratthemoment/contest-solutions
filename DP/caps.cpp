/**
 * У программиста Петрова есть хобби — собирать крышки от пивных бутылок. Ничего странного, он знает еще с сотню программистов, которые очень уважают пиво. Да, они тоже собирают крышки. Не все из них, конечно, но некоторые. Если честно, то часть своих крышек он просто купил, уже без бутылок. Да, это не совсем спортивно, зато коллекция теперь более солидная. Одна вот беда — не хватает ему для полноты коллекции еще нескольких редких крышек. Он даже нашел в Интернете программистов, которые согласны продать их ему. Некоторые даже продают крышки сразу наборами, с большой скидкой. Почему продают, да еще со скидкой? А вы попробуйте объяснить жене, какая польза от пивных крышек. Она же не программист. Осталось выбрать оптимальные предложения. Если объяснить жене зачем надо хранить крышки еще возможно, то почему на них надо тратить деньги — точно не поймет. Поэтому надо купить как можно дешевле. Петров выписал на бумажку все варианты и задумался. Купить сразу все не получится, никаких денег не хватит. Тогда надо купить самые необходимые, но подешевле. Да уж, без программы тут не обойдешься...
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

struct set {
    int price;
    int caps;

    set(int price, int caps) : price(price), caps(caps) {};
};

signed main() {
    meow
    int N, M;
    cin >> N;
    vector<set *> sets;
    int price;
    repeat(i, N) {
        cin >> price;
        sets.push_back(new set(price, 1 << i));
    }
    cin >> M;
    int q;
    repeat(i, M) {
        cin >> price >> q;
        int w = 0;
        int e;
        repeat(ii, q) {
            cin >> e;
            w |= 1 << (e - 1);
        }
        sets.push_back(new set(price, w));
    }
    cin >> q;
    int cap;
    int important = 0;
    repeat(i, q) {
        cin >> cap;
        important |= 1 << (cap - 1);
    }
    vector<int> f(1 << N, INT_MAX);
    f[0] = 0;
    for (set *w: sets) {
        f[w->caps] = w->price;
    }
    repeat(mask, 1 << N) {
        for (set *w: sets) {
            int newMask = mask | w->caps;
            f[newMask] = min(f[newMask], f[mask] + w->price);
        }
    }
    int answer = f[important];
    for (int mask = important; mask < 1 << N; mask++) {
        if (((mask | important) == mask) && f[mask] < answer) {
            answer = f[mask];
        }
    }
    cout << answer;
}