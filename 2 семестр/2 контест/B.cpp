/*Рику необходимо попасть на межвселенную конференцию. За каждую телепортацию он платит бутылками лимонада,
поэтому хочет потратить их на дорогу как можно меньше (он же всё-таки на конференцию едет!). Однако после K перелетов подряд Рика начинает сильно тошнить,
и он ложится спать на день. Ему известны все существующие телепортации. Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада), учитывая,
что телепортация не занимает времени, а до конференции осталось 10 минут (то есть он может совершить не более K перелетов)!
Формат ввода
В первой строке находятся количество вселенных N, количество существующих телепортаций M, количество перелетов подряд K, номер вселенной Рика S,
номер вселенной конференции F (2 ≤ N ≤ 300, 1 ≤ M ≤ 105, 1 ≤ K ≤ 300, 1 ≤ S ≤ N, 1 ≤ F ≤ N).
Далее идет M строк, задающих телепортации. i-я строка содержит три натуральных числа: Si, Fi и Pi, где Si - номер вселенной, из которой ведет i-я телепортация,
Fi - номер вселенной, в которую ведет i-я телепортация, Pi - стоимость i-й телепортации. 1 ≤ Si ≤ N, 1 ≤ Fi ≤ N, 1 ≤ Pi ≤ 106.*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
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
	}
	long long alglgorithm(size_t s, size_t f, size_t k) {
		size_t min_len_rib = BFS(s, f);//расстояние в ребрах до конференции
		if (min_len_rib > k) {
			return(-1);
		}
		vector<long long> result;
		result.assign(adj.size(), -1);
		result[s] = 0;
		Ford_Bellman(result, s, k);
		return(result[f]);
	}
	void Ford_Bellman(vector<long long>& result, size_t s, size_t k) {
		vector<bool> status;
		vector<size_t> which_status_swapped;
		status.assign(adj.size(), false);
		status[s] = true;
		for (size_t i = 0; i < k; ++i) {
			for (size_t j = 1; j < adj.size(); ++j) {
				for (size_t l = 0; l < adj[j].size(); ++l) {
					if (status[j] == false) {}
					else if (result[adj[j][l].vertex] == -1) {
						result[adj[j][l].vertex] = result[j] + adj[j][l].length;
						which_status_swapped.push_back(adj[j][l].vertex);
					}
					else if (result[adj[j][l].vertex] > result[j] + adj[j][l].length) {
						result[adj[j][l].vertex] = result[j] + adj[j][l].length;
					}
				}
			}
			for (int j = 0; j < which_status_swapped.size(); ++j) {
				status[which_status_swapped[j]] = true;
			}
			which_status_swapped.clear();
		}
	}
	size_t BFS(size_t s, size_t end) {
		queue<size_t> q;
		vector<size_t> colors(adj.size());
		q.push(s);
		colors[s] = 1;
		vector <size_t> distation(adj.size());
		while (q.size() > 0) {
			size_t value = q.front();
			q.pop();
			for (auto u : adj[value]) {
				if (colors[u.vertex] == 0) {
					q.push(u.vertex);
					colors[u.vertex] = 1;
					distation[u.vertex] = distation[value] + 1;
				}
			}
		}
		return(distation[end]);
	}
};
int main()
{
	size_t n, m, k, s, f;
	cin >> n >> m >> k >> s >> f;
	Graph g(n + 1);
	for (size_t i = 0; i < m; ++i) {
		size_t start, end, len;
		cin >> start >> end >> len;
		g.add(start, end, len);
	}
	long long result = g.alglgorithm(s, f, k);
	cout << result;
}