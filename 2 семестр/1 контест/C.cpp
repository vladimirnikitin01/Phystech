/*Фрэнку опять прилетел новый заказ. Однако в этот раз город играет по очень странным правилам: 
все дороги в городе односторонние и связывают только офисы нанимателей перевозчика. Множество офисов, между любыми двумя из которых существует путь,
образуют квартал, если нельзя добавить никакие другие, чтобы условие выполнялось. Фрэнку интересно,
каково минимальное количество односторонних дорог нужно ещё построить, чтобы весь город стал квраталом. 
Первая строка содержит пару целых чисел n и m (1 ≤ n ≤ 105, 0 ≤ m ≤ 105) — количество вершин и рёбер заданного ориентированного графа.
Следующие m строк содержат описания рёбер, по одному в строке. Каждая из строк содержит по два целых числа a и b (1 ≤ a, b ≤ n) — начало и конец ребра.*/
#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
class Graph {
private:
	vector<vector<int>> adj;
	vector<vector<int>> adj2;
public:
	Graph(int n)
	{
		adj.resize(n);
		adj2.resize(n);
	}
	struct AllVariables {
		vector<int> colors;
		vector <int> q;
		vector <int> q2;
		vector<int> strongly_connected;
		vector<int> sinks;
		vector<int> sources;
		int NumberOfStrong;
	};
	void add(int from, int to) {
		adj[from].push_back(to);
		adj2[to].push_back(from);
	}
	int algoritm() {
		AllVariables AllVariables;
		AllVariables.colors.resize(adj.size());
		AllVariables.strongly_connected.resize(adj.size());
		vector<int> colors(adj.size());
		TheFirst(AllVariables); // делаем первый обход dfs
		Smena(AllVariables);//делаем второй обход и отмечаем каким компонентам сильной связности принадлежат наши вершины
		int result = SearchSinksAndSources(AllVariables);
		return(result);
	}
	int SearchSinksAndSources(AllVariables& AllVariables) {
		AllVariables.sinks.resize(AllVariables.NumberOfStrong);
		AllVariables.sources.resize(AllVariables.NumberOfStrong);
		for (int i = 1; i < adj.size(); ++i) {
			for (auto u : adj[i]) {
				if (AllVariables.strongly_connected[u] != AllVariables.strongly_connected[i]) {
					AllVariables.sources[AllVariables.strongly_connected[i]] += 1;
					AllVariables.sinks[AllVariables.strongly_connected[u]] += 1;
				}
			}
		}
		int AllSources = 0, AllSinks = 0;
		for (int i = 0; i < AllVariables.NumberOfStrong; ++i) {
			if (AllVariables.sources[i] == 0) {
				AllSources += 1;
			}
			if (AllVariables.sinks[i] == 0) {
				AllSinks += 1;
			}
		}
		if (AllVariables.NumberOfStrong == 1) {
			return(0);
		}
		return(max(AllSinks, AllSources));
	}
	void Smena(AllVariables& AllVariables) {
		for (int i = 1; i < AllVariables.colors.size(); ++i) {
			AllVariables.colors[i] = 0;
		}
		AllVariables.q2 = AllVariables.q;
		int NumberOfStrong = 0;
		while (AllVariables.q2.size() > 0) {
			AllVariables.q.clear();
			dfs(AllVariables.q2.back(), AllVariables,adj2);
			AllVariables.q2.pop_back();
			for (int j = 0; j < AllVariables.q.size(); ++j) {
				AllVariables.strongly_connected[AllVariables.q[j]] = NumberOfStrong;
				if (j + 1 == AllVariables.q.size()) {
					NumberOfStrong += 1;
				}
			}
		}
		AllVariables.NumberOfStrong = NumberOfStrong;
	}
	void TheFirst(AllVariables& AllVariables) {
		for (int i = 1; i < adj.size(); ++i) {
			dfs(i, AllVariables, adj);
		}
	}
	void dfs(int s, AllVariables& AllVariables, vector<vector<int>> &adj) {
		if (AllVariables.colors[s] != 0) {
			return;
		}
		AllVariables.colors[s] = 1;
		for (auto u : adj[s]) {
			if (AllVariables.colors[u] == 0) {
				dfs(u, AllVariables, adj);
			}
		}
		AllVariables.colors[s] = 2;
		AllVariables.q.push_back(s);
	}
};
int main()
{
	int n, m;
	cin >> n >> m;
	Graph g(n + 1);
	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;
		g.add(from, to);
	}
	int result = g.algoritm();
	cout << result;
}