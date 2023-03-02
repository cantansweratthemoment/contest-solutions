/**
 * В соревновании участвуют 𝑛 участников, причем участник 𝑖 имеет силу 𝑠𝑖.
 * Каждый участник хочет узнать, какое преимущество он имеет перед лучшим участником соревнования помимо него самого. Другими словами, каждый участник 𝑖 хочет знать разность между 𝑠𝑖 и 𝑠𝑗, где 𝑗 — сильнейший участник соревнования, не считая 𝑖
 * . Обратите внимание, что разность может быть отрицательной.
 * Поэтому они просят вас о помощи! Для каждого 𝑖 (1≤𝑖≤𝑛) выведите разность между 𝑠𝑖 и максимальной силой участника, отличного от 𝑖.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)

struct participant {
    int i;
    int s;
    int answer;
};

bool comparatorS(participant a, participant b) {
    return a.s > b.s;
}

bool comparatorI(participant a, participant b) {
    return a.i < b.i;
}

signed main() {
    meow
    int t, n, s;
    cin >> t;
    repeat(i, t) {
        cin >> n;
        vector<participant> participants;
        repeat(ii, n) {
            participant q{};
            q.i = ii;
            cin >> s;
            q.s = s;
            participants.push_back(q);
        }
        sort(participants.begin(), participants.end(), comparatorS);
        participants[0].answer = participants[0].s - participants[1].s;
        for (int ii = 1; ii < participants.size(); ii++) {
            participants[ii].answer = participants[ii].s - participants[0].s;
        }
        sort(participants.begin(), participants.end(), comparatorI);
        repeat(ii, participants.size()) {
            cout << participants[ii].answer << " ";
        }
        cout << "\n";
    }
}