 /*  Сумма длин до остальных.
Для каждой вершины определите сумму расстояний до всех остальных вершин. Время работы должно быть O(n).*/
#include <vector>
#include <iostream>
using namespace std;
int dfs(int start, vector <vector<int>>& children, vector<int>& parent, vector<int>& rugrats) {
	int distance=0;
	for (int i = 0; i < children[start].size(); ++i) {
		int j = children[start][i];
		int distanceOfChild= dfs(j, children, parent, rugrats);
		rugrats[start] += rugrats[j]+1;
		distance = distance + distanceOfChild + rugrats[j]+1;
	}
	return(distance);
}
vector<int> result(vector <vector<int>>& children, vector<int>& parent) {
	vector <int> rugrats(parent.size());// спиногрызы, так как не могу придумать другое название для всех нижестоячих родственников
	vector<int> distance(parent.size());
	int distanceFor0= dfs(0,children, parent, rugrats);
	vector<int> res(parent.size());
	res[0] = distanceFor0;
	for (int i = 1; i < res.size(); ++i) {
		res[i] = res[parent[i]] - rugrats[i]-1 + (parent.size() - rugrats[i]-1);
	}
	return (res);
}
int main() {
	int  n;
	cin >> n;
	vector <int> parent(n);
	vector <vector<int>> children(n);
	for (int i = 0; i < n-1; ++i) {
		int a, b;
		cin >> a >> b;
		if (b < a) {
			swap(b, a);
		}
		parent[b] = a;
		children[a].push_back(b);
	}
	vector<int> res = result(children, parent);
	for (int i = 0; i < n; ++i) {
		cout << res[i] << endl;
	}
}