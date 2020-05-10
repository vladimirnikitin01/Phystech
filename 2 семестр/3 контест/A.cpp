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

using namespace std;

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
			adj[i].assign(n, -1);
		}
	}

	void add(size_t start, size_t end, size_t len) {
		if (adj[start][end] == -1 || adj[start][end] > len) {
			adj[start][end] = len;
			adj[end][start] = len;
		}
	}

	size_t algorithm() {
		size_t result = 0;
		size_t the_last_vertex = 1;
		vector<rib> the_smallest_length(adj.size(), rib());
		vector<bool> F_or_G(adj.size(),
			false);//поделим наш граф на 2 подграфа, и будем быстро смотреть в какой из 2 подграфов лежит наша вершина
		F_or_G[1] = true;
		Prim_algorithm(result, the_smallest_length, F_or_G, the_last_vertex);
		return (result);
	}

	vector<int> Search_smallest_length(vector<rib>& the_smallest_length, vector<bool>& F_or_G, size_t& the_last_vertex) {
		//если у i вершины ребро в другое поддерево, то надо каждый раз пересчитывать, и то, только для последней добавленной вершины
		//если же нет, то тогда надо проверить есть ли ребро между i и последней добавленной
		int min = 1000000;
		size_t vertex_from = 0;
		size_t vertex_to = 0;
		for (size_t i = 1; i < F_or_G.size(); ++i) {
			if (the_smallest_length[i].length != -1 && adj[i][the_last_vertex] != -1 && F_or_G[i] == false) {
				if (the_smallest_length[i].length > adj[i][the_last_vertex]) {
					the_smallest_length[i].length = adj[i][the_last_vertex];
					the_smallest_length[i].vertex = the_last_vertex;
				}
			}
			if (the_smallest_length[i].length == -1 && adj[i][the_last_vertex] != -1 && F_or_G[i] == false) {
				the_smallest_length[i].length = adj[i][the_last_vertex];
				the_smallest_length[i].vertex = the_last_vertex;
			}
			if (F_or_G[i] == false && min > the_smallest_length[i].length&& the_smallest_length[i].length != -1) {
				min = the_smallest_length[i].length;
				vertex_from = the_smallest_length[i].vertex;
				vertex_to = i;
			}
		}
		vector<int>  a(3);
		a[0] = min;
		a[1] = vertex_from;
		a[2] = vertex_to;
		return(a);
	}

	void
		Prim_algorithm(size_t& result, vector<rib>& the_smallest_length, vector<bool>& F_or_G, size_t& the_last_vertex) {
		for (size_t i = 1; i < F_or_G.size() - 1; ++i) {
			vector<int> now = Search_smallest_length(the_smallest_length, F_or_G, the_last_vertex);
			the_last_vertex = now[2];
			F_or_G[now[2]] = true;
			result += adj[now[1]][now[2]];
		}
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