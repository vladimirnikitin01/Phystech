/*Рик и Морти снова бороздят просторы вселенных, но решили ограничиться только теми, номера которых меньше M.
Они могут телепортироваться из вселенной с номером z
во вселенную (z+1) mod M за a бутылок лимонада или во вселенную (z2+1) mod M за b бутылок лимонада.
Рик и Морти хотят добраться из вселенной с номером x во вселенную с номером y.
Сколько бутылок лимонада отдаст Рик за такое путешествие, если он хочет потратить их как можно меньше?
Формат ввода
В строке подряд даны количество бутылок a за первый тип телепортации,
количество бутылок b за второй тип телепортации, количество вселенных M,
 номер стартовой вселенной x, номер конечной вселенной y (0 ≤ a, b ≤ 100, 1 ≤ M ≤ 106, 0 ≤ x, y < M).*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
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
	void add(size_t from, size_t a, size_t b, size_t m) {
		rib First;
		First.vertex = (from + 1) % m;
		First.length = a;
		rib Second;
		Second.vertex = (from * from + 1) % m;
		Second.length = b;
		adj[from].push_back(First);
		adj[from].push_back(Second);
	}
	size_t alglgorithm(size_t a, size_t b, size_t m, size_t x, size_t y) {
		size_t min_rib = std::min(a, b);
		vector<size_t> result = BFS(x, min_rib);
		return(result[y]);
	}
	vector<size_t> BFS(size_t s, size_t min_rib) {
		deque<size_t> q;
		q.push_front(s);
		vector <size_t> distance(adj.size(), -1);
		distance[s] = 0;
		while (q.size() > 0) {
			size_t value = q.front();
			q.pop_front();
			for (auto u : adj[value]) {
				// мы будем добавлять в начало более маленькие, чтобы инверсия сохранялась(после того, как до конца обработаем q.front)
				if (distance[u.vertex]==-1) {
					distance[u.vertex] = u.length+distance[value];
					if (u.length == min_rib) {
						q.push_front(u.vertex);
					}
					else {
						q.push_back(u.vertex);
					}
				}
				else if (distance[value] + u.length < distance[u.vertex]) {
					distance[u.vertex] = distance[value] + u.length;
					if (u.length == min_rib) {
						q.push_front(u.vertex);
					}
					else {
						q.push_back(u.vertex);
					}
				}
			}
		}
		return(distance);
	}
};
int main()
{
	size_t a, b, m, x, y;
	cin >> a >> b >> m >> x >> y;
	Graph g(m);
	for (size_t i = 0; i < m; ++i) {
		g.add(i, a, b, m);
	}
	size_t result = g.alglgorithm(a, b, m, x, y);
	cout << result;
}