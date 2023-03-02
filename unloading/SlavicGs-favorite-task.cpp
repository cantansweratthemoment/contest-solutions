/**
 * Вам задано взвешенное дерево с 𝑛 вершинами. Деревом называется неориентированный связный граф без циклов. Дерево является взвешенным, если каждому его ребру сопоставлено число — его вес. Дерево неориентировано, не содержит корня.
 * Так как деревья слишком скучны, вы решили повеселить себя игрой на дереве.
 * За один ход вы можете переместиться из вершины в любого его соседа (такую вершину, в которую есть ребро из текущей).
 * Вы начинаете игру, имея значение переменной 𝑥 равное 0. Когда вы перемещаетесь по ребру 𝑖, то 𝑥 изменяет своё значение на 𝑥 𝖷𝖮𝖱 𝑤𝑖 (где — 𝑤𝑖 вес 𝑖-го ребра).
 * Ваша задача пройти от вершины 𝑎 до вершины 𝑏, но вы имеете право входить в вершину 𝑏 только если 𝑥 после этого станет равно 0. Другими словами, вы можете пройти по ребру 𝑖, которое ведёт в 𝑏 тогда и только тогда, когда 𝑥 𝖷𝖮𝖱 𝑤𝑖=0.
 * Как только вы попадаете 𝑏, то игра заканчивается вашей победой.
 * Есть дополнительное правило — не более одного раза за игру вы можете воспользоваться телепортом. Он перемещает вас мгновенно в любую вершину (отличную от 𝑏
 * Вы можете использовать телепорт из любой вершины (даже из 𝑎).
 * Выведите «YES», если вы можете попасть в 𝑏 из 𝑎. Выведите «NO» в противном случае.
 */

#include <bits/stdc++.h>

using namespace std;

#define meow ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define repeat(i, n) for(int (i)=0; (i)<(n); (i)++)
#define int long long

struct entry {
    int v;
    int weight;

    entry(int v, int weight) {
        this->v = v;
        this->weight = weight;
    }
};

void DFSFromA(vector<vector<entry>> &graph, int i, vector<bool> &checked, int b, int x, set<int> &xors) {
    checked[i] = true;
    if (i == b) {
        return;
    }
    xors.insert(x);
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j].v]) {
            DFSFromA(graph, graph[i][j].v, checked, b, x ^ graph[i][j].weight, xors);
        }
    }
}

void DFSFromB(vector<vector<entry>> &graph, int i, vector<bool> &checked, int b, int x, set<int> &xors, bool &flag) {
    checked[i] = true;
    if (xors.find(x) != xors.end() && i != b) {
        flag = true;
        return;
    }
    repeat(j, graph[i].size()) {
        if (!checked[graph[i][j].v]) {
            DFSFromB(graph, graph[i][j].v, checked, b, x ^ graph[i][j].weight, xors, flag);
        }
    }
}

signed main() {
    meow
    int t, n, a, b, u, v, w;
    cin >> t;
    repeat(i, t) {
        cin >> n >> a >> b;
        vector<vector<entry>> graph(n);
        a--;
        b--;
        repeat(ii, n - 1) {
            cin >> u >> v >> w;
            u--;
            v--;
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        set<int> xors;
        vector<bool> checkedA(n, false);
        DFSFromA(graph, a, checkedA, b, 0, xors);
        vector<bool> checkedB(n, false);
        bool flag = false;
        DFSFromB(graph, b, checkedB, b, 0, xors, flag);
        if (flag) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}
