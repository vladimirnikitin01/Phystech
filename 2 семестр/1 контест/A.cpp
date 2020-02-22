/*Леон и Матильда собрались пойти в магазин за молоком. Их хочет поймать Стэнсфилд, поэтому нашим товарищам нужно сделать это как можно быстрее.
Каково минимальное количество улиц, по которым пройдёт хотя бы один из ребят (либо Матильда, либо Леон, либо оба вместе)?
Формат ввода
Первая строка содержит количество вершин n (1 ≤ n ≤ 105), количество ребер m (0 ≤ m ≤ 105) и номера вершин графа leon, matilda, milk,
в которых находятся соответственно Леон, Матильда и магазин с молоком.
Следующие m строк содержат ребра графа. В каждой строке два числа, разделенные пробелом, если между i и j существует ребро. Гарантируется, что в графе нет петель и мультиребер.*/
#include <iostream>
#include <set>
#include<queue>
#include <vector>
#include <algorithm>
using namespace std;
class Graph {
private:
	vector<set<int>> adj;
public:
	Graph(int n)
	{
		adj.resize(n);
	}
	void add(int from, int to) {
		adj[from].insert(to);
	}
	int alglgorithm(int& Leon, int& Matilda, int& Milk) {
		vector <int> FromLeon, FromMatilda, FromMilk, SumOfTheDistances(adj.size());
		FromLeon = BFS(Leon);
		FromMatilda = BFS(Matilda);
		FromMilk = BFS(Milk);
		for (int i = 1; i < adj.size(); ++i) {
			SumOfTheDistances[i] = FromLeon[i] + FromMatilda[i] + FromMilk[i];
		}
		int dist = *min_element(SumOfTheDistances.begin() + 1, SumOfTheDistances.end());
		return (dist);
	}
	vector<int> BFS(int s) {
		queue<int> q;
		vector<int> colors(adj.size());
		q.push(s);
		colors[s] = 1;
		vector <int> distation(adj.size());
		while (q.size() > 0) {
			int value = q.front();
			q.pop();
			for (auto u : adj[value]) {
				if (colors[u] == 0) {
					q.push(u);
					colors[u] = 1;
					distation[u] = distation[value] + 1;
				}
			}
		}
		return(distation);
	}
};
int main()
{
	int n, m, Leon, Matilda, Milk;
	cin >> n >> m >> Leon >> Matilda>> Milk;
	Graph g(n + 1);
	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;
		g.add(from, to);
		g.add(to, from);
	}
	int result = g.alglgorithm(Leon, Matilda, Milk);
	cout << result;
}