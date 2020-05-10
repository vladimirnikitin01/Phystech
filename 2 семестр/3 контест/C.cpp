/*Вам дан неориентированный граф, состоящий из n вершин. На каждой вершине записано число; число, записанное на вершине i, равно ai. Изначально в графе нет ни одного ребра.
Вы можете добавлять ребра в граф за определенную стоимость. За добавление ребра между вершинами x и y надо заплатить ax + ay монет. Также существует m специальных предложений,
каждое из которых характеризуется тремя числами x, y и w, и означает, что можно добавить ребро между вершинами x и y за w монет. Эти специальные предложения не обязательно использовать:
если существует такая пара вершин x и y, такая, что для нее существует специальное предложение, можно все равно добавить ребро между ними за ax + ay монет.
Сколько монет минимально вам потребуется, чтобы сделать граф связным? Граф является связным, если от каждой вершины можно добраться до любой другой вершины, используя только ребра этого графа.
Формат ввода
В первой строке заданы два целых числа n и m (1 ≤ n ≤ 2 ⋅ 105, 0 ≤ m ≤ 2 ⋅ 105) — количество вершин в графе и специальных предложений, соответственно.
Во второй строке заданы n целых чисел  (1 ≤ ai ≤ 1012) — числа, записанные на вершинах.
Затем следуют m строк, в каждой из которых заданы три целых числа x, y и w (1 ≤ x, y ≤ n, 1 ≤ w ≤ 1012, x ≠ y), обозначающие спецпредложение: можно добавить ребро между вершинами x и y за w монет.*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define size_t long long


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
    size_t end;
    size_t start;
    size_t length;

    rib() {
        end = 0;
        start = 0;
        length = -1;
    }

    rib(size_t a, size_t b, size_t c) {
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
    vector<size_t> all_a;
public:
    size_t min = 10000000000000;
    size_t index_a_min = 0;
    
    Graph(size_t n) {
        vertex_count = n;
        all_a.resize(n);
        all_a[0] = 0;
    };

    void add(size_t start, size_t end, size_t len) {
        adj.emplace_back(start, end, len);
    }

    void add(size_t a_vertex, size_t i) {
        all_a[i + 1] = (a_vertex);
        if (a_vertex < min) {
            min = a_vertex;
            index_a_min = i + 1;
        }
    }

    size_t algorithm() {
        /*сейчас будет ключевая мысль того, как мы должны обработать обработать обычные ребра, а не специальные, их мы уже добавили в граф
            предположение: что каждую вершину надо соединить с вершиной с самым маленьким а. У нас должно быть ребро у любой вершины, ведь граф будет связным. Если соединим все вершины с самой маденькой, то это
            связное дерево, очевидно. Почему сумма длин будет наименьшей, так как каждая вершина соединина с какой-нибудь другой, то их сумма будет (ai+ amin). И эту сумму нельзя улучшить. */

        
        for (size_t i = 1; i < vertex_count; ++i) {
            if (i != index_a_min) {
                add(i, index_a_min, all_a[i] + min);
            }
        }


        size_t result = Kruskal();
        return (result);
    }

    size_t Kruskal() {
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    size_t n, m;
    cin >> n >> m;
    Graph g(n + 1);
    for (size_t i = 0; i < n; ++i) {
        size_t ai;
        cin >> ai;
        g.add(ai, i);
    }
    for (size_t i = 0; i < m; ++i) {
        size_t x, y, w;
        cin >> x >> y >> w;
        g.add(x, y, w);
    }
    cout << g.algorithm();
};