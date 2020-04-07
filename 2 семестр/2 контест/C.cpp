/*Сейчас Рику надо попасть из вселенной с номером S во вселенную с номером F. Он знает все существующие телепорты, и казалось бы нет никакой проблемы.
Но, далеко не секрет, что за свою долгую жизнь Рик поссорился много с кем. Из своего личного опыта он знает, что при телепортациях есть вероятность, что его заставят ответить за свои слова.
Если Рик знает вероятности быть прижатым к стенке на всех существующих телепортациях, помогите ему посчитать минимальную вероятность, что он всё-таки столкнется с неприятностями.
Формат ввода
В первой строке даны количество вселенных N (2 ≤ N ≤ 100), количество существующих телепортаций M (1 ≤ M ≤ N ⋅ (N - 1) / 2), стартовая вселенная S (1 ≤ S ≤ N) и конечная вселенная F (1 ≤ F ≤ N).
Далее в M строках дается описание телепортаций в формате Si, Fi, Pi, где Si и Fi — номера вселенных, которые связывает i-я телепортация (телепорты двунаправленные, 1 ≤ Si, Fi ≤ N),
Pi — вероятность быть избитым на i-й телепортации в процентах (0 ≤ Pi ≤ 100).*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
struct rib {
	size_t vertex;
	size_t length;
};
class Graph {
private:
	vector<vector<rib>> adj;
public:
	Graph(size_t n)
	{
		adj.resize(n);
	}
	void add(size_t start, size_t end, size_t len) {
		rib RIB;
		RIB.vertex = end;
		RIB.length = len;
		adj[start].push_back(RIB);
		RIB.vertex = start;
		adj[end].push_back(RIB);
	}
	double algorithm(size_t s, size_t f) {
		vector<double> result;
		result.assign(adj.size(), 100);
		result[s] = 0;
		Ford_Bellman(result, s);
		return(result[f]);
	}
	void Ford_Bellman(vector<double>& result, size_t s) {
		for (size_t i = 0; i < adj.size(); ++i) {
			for (size_t j = 1; j < adj.size(); ++j) {
				for (size_t l = 0; l < adj[j].size(); ++l) {
					if (result[adj[j][l].vertex] > result[j] + adj[j][l].length / 100.0 - result[j] * (adj[j][l].length / 100.0)) {
						result[adj[j][l].vertex] = result[j] + adj[j][l].length / 100.0 - result[j] * (adj[j][l].length / 100.0);
					}
				}
			}

		}
	}
};
int main()
{
	size_t n, m, s, f;
	cin >> n >> m >> s >> f;
	Graph g(n + 1);
	for (size_t i = 0; i < m; ++i) {
		size_t start, end, len;
		cin >> start >> end >> len;
		g.add(start, end, len);
	}
	double result = floor(g.algorithm(s, f) * 1000000.0 + 0.5) / 1000000.0;
	cout << result;
}