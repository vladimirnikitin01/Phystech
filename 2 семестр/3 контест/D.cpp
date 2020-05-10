﻿/*Шреку необходимо пробраться в башню, чтобы спасти прекрасную принцессу Фиону. И сейчас его путь лежит через старый полуразвалившийся мост.
Осёл очень боится упасть с этого моста в лавовую реку под ним и отказывается идти дальше, пока мост не будет полностью починен. Шрек не может идти без друга и решил отремонтировать его.
Мост представляет собой поле из n × m клеток, причем некоторые клетки ещё остались целыми. У Шрека есть только дощечки размера 1 × 2, установка которых занимает у него a секунд, и 1 × 1, установка которых занимает b секунд. Ему необходимо закрыть все пустые клетки,
причем только их, не накладывая дощечки друг на друга.
Определите, через какое минимальное количество секунд Шрек и Осёл смогут продолжить свой путь дальше.
Формат ввода
Первая строка входного файла содержит 4 целых числа n, m, a, b (1 ≤ n, m ≤ 100, |a| ≤ 1 000, |b| ≤ 1 000). Каждая из последующих n строк содержит по m символов: символ  «.» (точка) обозначает целую клетку моста,
а символ «*» (звёздочка) — пустую.
Формат вывода
В выходной файл выведите одно число — минимальное количество секунд, через которое наши герои смогут продолжить свой путь, закрыв пустые клетки моста (их и только их).*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Shares {
	vector<vector<int>> adj_white;//нечетные
	long long count_white = 0;
	vector<vector<int>> adj_black;//четные
	long long count_black = 0;

	explicit Shares(size_t size) {
		adj_white.resize(size);
		adj_black.resize(size);
	}
};

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
	size_t n;
	size_t m;
public:
	Graph(int n_, int m_) {
		adj.resize(n_);
		for (size_t i = 0; i < n_; ++i) {
			adj[i].resize(m_);
		}
		n = n_;
		m = m_;
	}

	void do_list_of_adjacencies(int i, int j, vector<vector<int>>& v) {
		if (i - 1 >= 0 && adj[i - 1][j] == 1) {
			v[i * m + j].push_back((i - 1) * m + j);
		}
		if (i + 1 < n && adj[i + 1][j] == 1) {
			v[i * m + j].push_back((i + 1) * m + j);
		}
		if (j - 1 >= 0 && adj[i][j - 1] == 1) {
			v[i * m + j].push_back(i * m + j - 1);
		}
		if (j + 1 < m && adj[i][j + 1] == 1) {
			v[i * m + j].push_back(i * m + j + 1);
		}
	}

	void adprocessingd(Shares& shares) {
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				if (adj[i][j] == 1) {
					if ((j + i) % 2 == 0) {
						++shares.count_black;
						do_list_of_adjacencies(i, j, shares.adj_black);
					}
					else {
						++shares.count_white;
						do_list_of_adjacencies(i, j, shares.adj_white);
					}
				}
			}
		}
	}

	void add(string& s, size_t i) {
		for (size_t j = 0; j < s.size(); ++j) {
			adj[i][j] = ((s[j] == 42) ? 1 : 0);
		}
	}

	bool kuhn(size_t a, vector<vector<int>>& v, vector<bool>& used, vector<int>& result) {
		if (used[a]) {
			return false;
		}
		used[a] = true;
		for (auto u : v[a]) {
			if (result[u] == -1 || kuhn(result[u], v, used, result)) {
				result[u] = a;
				return true;
			}
		}
		return false;
	}

	long long algorithm(int a, int b) {
		Shares shares(n * m);
		adprocessingd(shares);//сделали ввод в нужном формате и весь подсчет
		if (2 * b <= a) {
			return (b * (shares.count_black + shares.count_white));
		}
		vector<bool> used;
		used.assign(n * m, false);
		vector<int> result;
		result.assign(n * m, -1);
		int ost = 0;
		if (shares.count_white < shares.count_black) {
			ost = 1;
			shares.adj_black = shares.adj_white;
		}
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < m; ++j) {
				if ((i + j) % 2 == ost) {
					if (kuhn(i * m + j, shares.adj_black, used, result)) {
						used.assign(n * m, false);
					}
				}
			}
		}
		long long count = 0;
		for (int i : result) {
			if (i != -1) {
				++count;
			}
		}

		return (count * a + (shares.count_black + shares.count_white - 2 * count) * b);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	Graph g(n, m);
	for (size_t i = 0; i < n; ++i) {
		string s;
		cin >> s;
		g.add(s, i);
	}
	cout << g.algorithm(a, b);
};