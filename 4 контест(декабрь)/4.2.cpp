/*  Сумма длин до остальных.
Для каждой вершины определите сумму расстояний до всех остальных вершин. Время работы должно быть O(n).*/
#include <vector>
#include <iostream>
using namespace std;
struct PairOfChildAndHisParent {
	vector <vector<int>> children;
	vector <int> parent;
	PairOfChildAndHisParent(vector <vector<int>> children, vector <int> parent) : children(children), parent(parent) {}
};
int dfs(int start, vector <vector<int>>& children, vector<int>& parent, vector<int>& relatives) {
	int distance = 0;
	for (int i = 0; i < children[start].size(); ++i) {
		int j = children[start][i];
		int distanceOfChild = dfs(j, children, parent, relatives);
		relatives[start] += relatives[j] + 1;
		distance = distance + distanceOfChild + relatives[j] + 1;
	}
	return(distance);
}
vector<int> result(vector <vector<int>>& children, vector<int>& parent) {
	vector <int> relatives(parent.size());//  название для всех нижестоячих родственников
	vector<int> distance(parent.size());
	int distanceFor0 = dfs(0, children, parent, relatives);
	vector<int> res(parent.size());
	res[0] = distanceFor0;
	for (int i = 1; i < res.size(); ++i) {
		res[i] = res[parent[i]] - relatives[i] - 1 + (parent.size() - relatives[i] - 1);
	}
	return (res);
}
PairOfChildAndHisParent input(int n) {
	vector <int> parent(n + 1);
	vector <vector<int>> children(n + 1);
	for (int i = 0; i < n; ++i) {
		int parentOfThisChild, child;
		cin >> parentOfThisChild >> child;
		if (child < parentOfThisChild) {
			swap(child, parentOfThisChild);
		}
		parent[child] = parentOfThisChild;
		children[parentOfThisChild].push_back(child);
	}
	return(PairOfChildAndHisParent(children, parent));
}
void output(vector<int>& res) {
	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << endl;
	}
}
int main() {
	int  n;
	cin >> n;
	PairOfChildAndHisParent pair = input(n - 1);
	vector<int> res = result(pair.children, pair.parent);
	output(res);
}