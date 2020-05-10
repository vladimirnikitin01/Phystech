/*Шрек и Фиона пригласили всех своих друзей на свою свадьбу. На церемонии они хотят рассадить их всех на две непустые части так, чтобы количество знакомств между двумя частями было минимальным.
Всего приглашенных на свадьбу n, а каждое знакомство обоюдно.
Вам дан граф, в котором ребро означает знакомство между людьми. Помогите Шреку и Фионе поделить гостей на две непустые части.
Формат ввода
В первой строке входного файла записано целое число n () — число гостей. Каждая из следующих n строк содержит по n символов.
i-й символ j-й из этих строк равен «1», если между вершинами i и j есть ребро, и «0» в противном случае. Заданная таким образом матрица смежности является антирефлексивной (на главной диагонали стоят нули)
и симметричной (относительно главной диагонали).
Формат вывода
Выведите в выходной файл две строки. На первой выведите номера вершин, попавших в левую часть, через пробел, а на второй — номера вершин, попавших в правую часть, также через пробел.
Номера вершин можно выводить в любом порядке.*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;
enum Condition {
    independent = 0,
    inside,
    boss
};

void OUTPUT(std::pair<set<int>, set<int>>& result) {
    for (auto u : result.first) {
        cout << u + 1 << ' ';
    }
    cout << std::endl;
    for (auto u : result.second) {
        cout << u + 1 << ' ';
    }
}

struct rib {
    size_t vertex;
    int length;

    rib() {
        vertex = 0;
        length = -1;
    }

    rib(size_t a, int b) {
        vertex = a;
        length = b;
    }
};

class Graph {
private:
    vector<vector<int>> adj;
public:
    Graph(size_t n) {
        adj.resize(n);
        for (size_t i = 0; i < n; ++i) {
            adj[i].resize(n);
        }
    }

    void add(string& s, size_t i) {
        for (size_t j = 0; j < adj.size(); ++j) {
            adj[i][j] = s[j] - '0';
        }
    }

    std::pair<set<int>, set<int>> algorithm() {
        set<int> answer;
        vector<set<int>> vertex(adj.size());//храним какие вершины внутри i
        for (size_t i = 0; i < adj.size(); ++i) {
            vertex[i].insert(i);
        }
        int Min = 100000000;
        vector<Condition> condition(adj.size());//чтобы отследить состояния
        for (size_t l = 0; l < adj.size() - 1; ++l) {
            vector<int> points_to_merger;//порядок добавления, чтобы потом взять 2 последние
            vector<bool> in_a;
            in_a.assign(adj.size(), false);
            in_a[0] = true;
            set<int> a;
            a.insert(0);
            for (size_t i = 0; i < adj.size() - l - 1; ++i) {
                int Max = 0;
                int index_max = 0;
                for (size_t j = 1; j < adj.size(); ++j) {//a=0
                    if (!in_a[j] && (condition[j] == 0 || condition[j] == 2)) {
                        int result = 0;

                        for (auto u : a) {
                            result += adj[j][u];
                        }
                        if (result > Max) {
                            Max = result;
                            index_max = j;
                        }

                    }
                }
                points_to_merger.push_back(index_max);
                a.insert(index_max);
                in_a[index_max] = true;
            }
            int past = points_to_merger[points_to_merger.size() - 1];
            int result = 0;
            for (size_t i = 0; i < adj.size(); ++i) {
                if (in_a[i] == true && past != i) {
                    result += adj[past][i];
                }
            }
            if (result < Min) {
                Min = result;
                answer = vertex[past];
            }
            //процесс слияния двух точек в одну
            if (points_to_merger.size() > 1) {
                int past2 = points_to_merger[points_to_merger.size() - 2];
                for (size_t i = 0; i < adj.size(); ++i) {
                    if (condition[i] != inside) {
                        adj[i][past] += adj[past2][i];
                        adj[past][i] = adj[i][past];
                    }
                }
                condition[past2] = inside;
                condition[past] = boss;
                vertex[past].merge(vertex[past2]);
            }
        }
        set<int> all;
        for (size_t i = 0; i < adj.size(); ++i) {
            all.insert(i);
        }
        for (auto u : answer) {
            all.erase(u);
        }
        return { all, answer };
    }

};

int main() {
    size_t n;
    cin >> n;
    Graph g(n);
    for (size_t i = 0; i < n; ++i) {
        string s;
        cin >> s;
        g.add(s, i);
    }
    std::pair<set<int>, set<int>> result = g.algorithm();
    OUTPUT(result);
}