/*Требуется найти в связном графе остовное дерево минимального веса.
Воспользуйтесь алгоритмом Прима.
Формат ввода
Первая строка входного файла содержит два натуральных числа n и m — количество вершин и ребер графа соответственно.
 Следующие m строк содержат описание ребер по одному на строке. Ребро номер i описывается тремя натуральными числами bi,
 ei и wi — номера концов ребра и его вес соответственно (1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100 000). n ≤ 5 000, m ≤ 100 000.
Граф является связным.*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <set>

using namespace std;

class DSU {
private:
    vector<size_t> parents;
public:
    DSU(size_t count) {
        parents.resize(count);
        for (size_t i = 0; i < count; ++i) {
            parents[i] = i;
        }
    }
    //в нашем случае не надо создавать множества из элементов, так как мы сразу будем для всех собирать
    size_t FIND(size_t a) {
        if (a == parents[a]) {
            return(a);
        }
        else {
            return(parents[a] = FIND(parents[a]));
        }
    }
    void UNION(size_t a, size_t b) {
        a = FIND(a);
        b = FIND(b);
        if (a != b)
            if (rand() & 1)
                swap(a, b);
        parents[a] = b;
    }
};

struct rib {
    int end;
    int start;
    int length;

    rib() {
        end = 0;
        start = 0;
        length = -1;
    }

    rib(int a, int b, int c) {
        end = b;
        length = c;
        start = a;
    }
};

bool cmp(const rib& a, const rib& b) {
    return a.length < b.length;
}

class Graph {
private:
    vector<rib> adj;
    size_t vertex_count;
public:
    Graph(size_t n) {
        vertex_count = n;
    };

    void add(size_t start, size_t end, size_t len) {
        adj.push_back(rib(start, end, len));
    }

    size_t algorithm() {
        size_t result = 0;
        DSU now_dsu(vertex_count);
        sort(adj.begin(), adj.end(), cmp);
        for (auto RIB : adj) {
            if (now_dsu.FIND(RIB.start) != now_dsu.FIND(RIB.end)) {
                result += RIB.length;
                now_dsu.UNION(RIB.start, RIB.end);
            }
        }
        return (result);
    }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    Graph g(n + 1);
    for (size_t i = 0; i < m; ++i) {
        size_t b, e, w;
        cin >> b >> e >> w;
        g.add(b, e, w);
    }
    size_t result = g.algorithm();
    cout << result;
}