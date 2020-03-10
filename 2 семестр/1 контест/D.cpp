/*Беатрикс Киддо в молодости была наемницей и любила составлять графы связей между её целями. Она цепляла на стену иголки и связывала их нитками. 
Но так как она наполовину японка, ей особенно нравилось, когда цели можно было расположить так, чтобы нитки не пересекались. 
Вам известна схема, которую хочет начертить Беатрикс. Выясните, может ли в этот раз схема ей понравиться?*/
#include <vector>
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
struct ribs {
	int start=-1;
	int end;
	int status;
};
struct segment {
	int prioritet;
	set<int> points;
	int type;//тип сегмента 0 или 1
	vector<vector<int>> adj4;
};
class Graph {
private:
	vector<vector<int>> adj;
	vector<vector<int>> adj2;
public:
	int planary = 0;// 0 я еще не знаю, 1 планарен, 2 не планарен
	Graph(int n)
	{
		adj.resize(n);
		adj2.resize(n);
	}
	int size() {
		return(adj.size());
	}
	/*struct AllVariables {
		int parent;
		vector <int> colors;
		vector <int> d;
		int children;
		int time; 
		set <int>point;
		vector <int> low;
	};*/
	void add(int from, int to) {
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	void dfs_for_connectivity(int s, vector<int>& p, set<int>& ListForOutput, vector<int>& colors, vector<vector<int>>& adj3) {
		if (colors[s] != 0 && adj3[s].size()==0) {
			return;
		}
		colors[s] = 1;
		for (auto u : adj[s]) {
			if (p[s] == u) {
			}
			else if (colors[u] == 0) {
				p[u] = s;
				ListForOutput.insert(s);
				ListForOutput.insert(u);
				dfs_for_connectivity(u, p, ListForOutput, colors, adj3);
			}
			else if (colors[u] == 1) {
				return;
			}
		}
	}
	void dfs(int s, vector<int>& p, vector<int>& ListForOutput, vector<int>& colors, bool& Status_Cycle) {
		if (colors[s] != 0 || Status_Cycle==true) {
			return;
		}
		colors[s] = 1;
		for (auto u : adj[s]) {
			if (p[s] == u) {}
			else if (colors[u] == 0) {
				p[u] = s;
				dfs(u, p, ListForOutput, colors, Status_Cycle);
			}
			else if (colors[u] == 1) {
				Status_Cycle = true;
				ListForOutput[0] = u;
				ListForOutput[1] = s;
				return;
			}
		}
		colors[s] = 2;
	}
	void remove_the_bridges() {

	}
	void remove_the_points_of_articulation() {

	}
	void checking_for_connectivity() {

	}
	void making_the_graph_ready_for_gamma(vector<Graph>& AllGraph) {

	}
	vector<int> cycle_search() {
		vector<int>colors(adj.size());
		vector<int> ListForOutput(2);
		vector<int> p;
		p.assign(adj.size(), -1);
		bool Status_Cycle = false;
		for (int i = 0; i < adj.size(); ++i) {
			if (Status_Cycle == false) {
				dfs(i, p, ListForOutput, colors, Status_Cycle);
			}
		}
		if (Status_Cycle == false) {
			vector<int> a(1);
			a[1] = -1;
			return(a);
		}
		else {
			vector<int> cycle;
			cycle.push_back(ListForOutput[0]);
			for (int i = ListForOutput[1]; i != ListForOutput[0]; i = p[i]) {
				cycle.push_back(i);
			}
			return(cycle);
		}

	}
	vector<ribs> rib(vector<int>& contact, vector<int>& cycle) {
		vector<ribs> rib(adj.size());
		int k = 0;//счетчик ребер
		for (int i = 0; i < adj.size(); ++i) {
			k += adj[i].size();
		}
		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < adj[i].size(); ++j) {
				if (i < adj[i][j]) {
					rib[i].start = i;
					rib[i].end = adj[i][j];
					rib[i].status = 0;
				}
				else {
					rib[i].start = adj[i][j];
					rib[i].end = i;
					rib[i].status = 0;
				}
			}
		}
		return(rib);
	}
	vector<segment> search_segments(vector<int>& cycle, vector<int>& contact, vector<ribs>& ribs) {
		set<int> withOutG;
		for (int i = 0; i < contact.size(); ++i) {
			if (contact[i] == 0) {
				withOutG.insert(contact[i]);
			}
		}
		vector<vector<int>> adj3(adj.size());
		for (int i = 0; i < adj.size(); ++i) {
			if (withOutG.count(i) > 0) {
				for (int j = 0; j < adj[i].size(); ++i) {
					if (withOutG.count(adj[i][j]) > 0) {
						adj3[i].push_back(adj[i][j]);
						adj3[adj[i][j]].push_back(i);
					}
				}
			}
		}

		vector<int>colors(adj.size());
		vector<int> p(adj.size());
		set<int> ListForOutput;
		vector<segment> Segments;
		set<int> DopPoint;// ребра которые надо добавить
		for (int i = 0; i < adj3.size(); ++i) {
			dfs_for_connectivity(i, p, ListForOutput, colors, adj3);
			for (auto u : ListForOutput) {
				for (int j = 0; j < adj[u].size(); ++i) {
					if (contact[adj[u][j]] == 1) {
						DopPoint.insert(j);
					}
				}
			}
			for (auto u: DopPoint) {
				ListForOutput.insert(u);
			}
			segment a;
			a.type = 1;
			a.points = ListForOutput;
			Segments.push_back(a);
			ListForOutput.clear();
			DopPoint.clear();
		}

		for (int i=0;i<ribs.size();++i) {
			if (ribs[i].status == 0 && contact[ribs[i].start] == 1 && contact[ribs[i].end] == 1) {
				segment a;
				a.type = 0;
				set<int> ListForOutput;
				ListForOutput.insert(ribs[i].start);
				ListForOutput.insert(ribs[i].end);
				a.points = ListForOutput;
				Segments.push_back(a);
			}
		}
		return(Segments);
	}
};
void planar(Graph& g) {
	vector<Graph> AllGraph;
	g.making_the_graph_ready_for_gamma(AllGraph);
	for (int i = 0; i < AllGraph.size(); ++i) {
		//gamma_algorithm(AllGraph[i]);
		if (AllGraph[i].planary == 2) {
			cout << "NO";
			return;
		}
		cout << "YES";
	}
}
int checking_segments(vector<vector<int>>& face, Graph& value, vector<int>& contact, vector<int>& cycle){
	vector<ribs> ribs = value.rib;
	vector<segment> Segments = value.search_segments(cycle, contact, ribs);
	for (int i = 0; i < face.size(); ++i) {
		set<int> point;
		for (int j = 0; j < face[i].size(); ++j) {
			point.insert(face[i][j]);
		}
		for (int j = 0; j < Segments.size(); ++j) {
			int k = 0;
			for (auto u : Segments[j].points) {
				if (point.count(u) > 0) {
					k += 1;
				}
			}
			if (k == Segments[j].points.size()) {
				Segments[j].prioritet += 1;
			}
		}
	}
	int min = face.size()+1;
	int k = -1;
	for (int i = 0; i < Segments.size(); ++i) {
		if (Segments[i].prioritet < min) {
			min = Segments[i].prioritet;
			k = i;
		}
	}
	if (min == 0) {
		value.planary = 2;
	}
	else if (Segments[k].type = 1) {
		//добавляем этот отрезок сюда
	}
	else {
		//добавляем цепь
	}
}
void gamma_algorithm(Graph& value) {
	vector<int> cycle = value.cycle_search();
	if (cycle.size() == 1) {
		value.planary = 1;
	}
	else {
		vector<int> contact(value.size());
		vector<vector<int>> face(2);
		for (int i = 0; i < cycle.size(); ++i) {
			contact[cycle[i]] = 1;
		}
		face[1] = cycle;
		face[0] = cycle;
		value.planary = checking_segments(face, value, contact, cycle);
	}
}
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
}