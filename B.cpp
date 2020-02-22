/*Джон Макклейн сообщает по рации новую информацию о террористах в отдел с n полицейскими. Он звонит нескольким сотрудникам и просит распространить информацию по отделу,
зная, что у каждого полицейского есть связь с определёнными коллегами. Джон Макклейн хочет, чтобы операция прошла успешно. Но если полицейский позвонит коллеге,
от которого(возможно, не напрямую) сам получил информацию, террористы смогут отследить этот звонок и помешать операции. Если же двое сотрудников оповестят одного,
ничего плохого не произойдёт. Помогите Джону Макклейну. Выведите NO, если кто-то из полицейских ошибётся, делая звонок. Если всё пройдёт хорошо, выведите YES и порядок,
в котором полицейские получат информацию, считая, что полицейские оповещают коллег по возрастанию их номеров, а в начале Джон даёт информацию тем, кому не может позвонить никто из коллег.
Формат ввода
Первая строка содержит пару целых чисел n и m (1 ≤ n, m ≤ 105) — количество вершин и рёбер заданного ориентированного графа.
Следующие m строк содержат описания рёбер, по одному в строке. Каждая из строк содержит по два целых числа a и b (0 ≤ a, b < n) — начало и конец ребра.*/
#include <vector>
#include <iostream>
#include <set>
using namespace std;
class Graph {
private:
	vector<set<int>> adj;
	vector <int> ListForOutput;
	bool Status_Cycle = true;
public:
	Graph(int n)
	{
		adj.resize(n);
	}
	void add(int from, int to) {
		adj[from].insert(to);
	}
	void algoritm() {
		vector<int> colors(adj.size());
		for (int i = 0; i < adj.size(); ++i) {
			if (Status_Cycle == false) {
				return;
			}
			else {
				dfs(i,colors);
			}
		}
	}
	void dfs(int s, vector<int> &colors) {
		if (colors[s] != 0) {
			return;
		}
		colors[s] = 1;
		for (auto u : adj[s]) {
			if (colors[u] == 0) {
				dfs(u,colors);
			}
			else if (colors[u] == 1) {
				Status_Cycle = false;
			}

		}
		colors[s] = 2;
		ListForOutput.push_back(s);
	}
	void output() {
		if (Status_Cycle == true) {
			cout << "YES" << endl;
			while (ListForOutput.size() > 0) {
				cout << ListForOutput.back() << ' ';
				ListForOutput.pop_back();
			}
		}
		else {
			cout << "NO";
		}
	}
};
int main()
{
	int n, m;
	cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; ++i) {
		int from, to;
		cin >> from >> to;
		g.add(from, to);
	}
	g.algoritm();
	g.output();
}

