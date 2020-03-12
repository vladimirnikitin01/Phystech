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
	int start = -1;
	int end;
	int status;
};
struct segment {
	int prioritet = 0;
	set<int> points;
	int type;//тип сегмента 0 или 1
	vector<vector<int>> adj4;
	int The_number_of_face;
};
class Graph {
private:
	vector<vector<int>> adj;
public:
	int planary = 0;// 0 я еще не знаю, 1 планарен, 2 не планарен
	Graph(int n)
	{
		adj.resize(n);
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
	void add2(vector<vector<int>>& adj3) {
		adj = adj3;
	}
	void DFS_for_bridge(int s, vector<int>& parent, vector<int>& colors, vector<int>& low, vector<int>& d, int& time, vector<vector<int>>& bridge) {
		if (colors[s] != 0) {
			return;
		}
		colors[s] = 1;
		time += 1;
		d[s] = time;
		low[s] = time;
		for (auto u : adj[s]) {
			if (u != parent[s]) {
				if (colors[u] != 0) {
					low[s] = std::min(low[s], d[u]);
				}
				else {
					parent[u] = s;
					DFS_for_bridge(u, parent, colors, low, d, time, bridge);
					low[s] = std::min(low[s], low[u]);
					if (low[u] > d[s]) {
						vector<int> now(2);
						now[0] = u;
						now[1] = s;
						bridge.push_back(now);
					}
				}
			}
			colors[u] = 2;
		}
	};
	void dfs_for_connectivity(int s, vector<int>& p, set<int>& ListForOutput, vector<int>& colors, vector<set<int>>& adj3, vector<int>& contact) {
		if (colors[s] != 0 || contact[s] == 1) {
			return;
		}
		colors[s] = 1;
		for (auto u : adj3[s]) {
			if (p[s] == u) {
			}
			else if (colors[u] == 0) {
				p[u] = s;
				ListForOutput.insert(s);
				ListForOutput.insert(u);
				dfs_for_connectivity(u, p, ListForOutput, colors, adj3, contact);
			}
			else if (colors[u] == 1) {
				return;
			}
		}
		if (adj3[s].size() == 0) {
			ListForOutput.insert(s);
		}
	}
	void dfs(int s, vector<int>& p, vector<int>& ListForOutput, vector<int>& colors, bool& Status_Cycle) {
		if (colors[s] != 0 || Status_Cycle == true) {
			return;
		}
		colors[s] = 1;
		for (auto u : adj[s]) {
			if (p[s] == u) {}
			else if (colors[u] == 0) {
				p[u] = s;
				dfs(u, p, ListForOutput, colors, Status_Cycle);
			}
			else if (colors[u] == 1 && Status_Cycle == false) {
				Status_Cycle = true;
				ListForOutput[0] = u;
				ListForOutput[1] = s;
				return;
			}
		}
		colors[s] = 2;
	}
	void  dfs_for_chain(int s, vector<int>& p, vector<int>& colors, vector<int>& contact, int& count, int& status) {
		if (colors[s] != 0) {
			return;
		}
		colors[s] = 1;
		count += 1;
		for (auto u : adj[s]) {
			if (count > 1 && status == 0) {
				if (p[s] == u) {}
				else if (colors[u] == 0) {
					p[u] = s;
					if (contact[u] == 1) {
						count = u;
						status = 1;
						return;
					}
					dfs_for_chain(u, p, colors, contact, count, status);
				}
				else if (colors[u] == 1) {
					return;
				}
			}
			else if (count == 1 && status == 0) {
				if (p[s] == u) {}
				else if (colors[u] == 0 && contact[u] == 0) {
					p[u] = s;
					dfs_for_chain(u, p, colors, contact, count, status);
				}
				else if (colors[u] == 1) {
					return;
				}
			}
		}
		colors[s] = 2;
	}
	void remove_the_bridges() {
		vector<int> parent;
		parent.assign(adj.size(), -1);
		vector<int> colors(adj.size());
		vector<vector<int>> bridge;
		vector<int> low(adj.size());
		vector<int> d(adj.size());
		int time = 0;
		for (int i = 0; i < adj.size(); ++i) {
			DFS_for_bridge(i, parent, colors, low, d, time, bridge);
		}
		for (int i = 0; i < bridge.size(); ++i) {
			int First = bridge[i][0];
			int Second = bridge[i][1];
			for (int l = 0; l < adj[First].size(); ++l) {
				if (adj[First][l] == Second) {
					adj[First].erase(adj[First].begin() + l);

				}
			}
			for (int l = 0; l < adj[Second].size(); ++l) {
				if (adj[Second][l] == First) {
					adj[Second].erase(adj[Second].begin() + l);

				}
			}
		}
	}
	void checking_for_connectivity(int s, vector<int>& p, set<int>& ListForOutput, vector<int>& colors) {
		if (colors[s] != 0) {
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
				checking_for_connectivity(u, p, ListForOutput, colors);
			}
			else if (colors[u] == 1) {
				return;
			}
		}
		if (adj[s].size() == 0) {
			ListForOutput.insert(s);
		}
	}
	void making_the_graph_ready_for_gamma(vector<Graph>& AllGraph) {
		vector<int> p;
		p.assign(adj.size(), -1);
		vector<int> colors(adj.size());
		for (int i = 0; i < adj.size(); ++i) {
			set<int> ListForOutput;
			checking_for_connectivity(i, p, ListForOutput, colors);
			if (ListForOutput.size() > 0) {
				vector < vector<int>> adj3(adj.size());
				for (auto u : ListForOutput) {
					for (int i = 0; i < adj[u].size(); ++i) {
						if (ListForOutput.count(adj[u][i]) > 0) {
							adj3[u].push_back(adj[u][i]);
						}
					}
				}
				Graph a(adj.size());
				a.add2(adj3);
				AllGraph.push_back(a);
			}
		}
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
			a[0] = -1;
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
		vector<ribs> rib;
		for (int i = 0; i < adj.size(); ++i) {
			for (int j = 0; j < adj[i].size(); ++j) {
				if (i < adj[i][j]) {
					ribs that;
					that.start = i;
					that.end = adj[i][j];
					that.status = 0;
					//отмечаем 1 тех, которые есть в цикле
					for (int l = 0; l < cycle.size() - 1; ++l) {
						if (cycle[l] < cycle[l + 1] && cycle[l] == i && cycle[l + 1] == adj[i][j]) {
							that.status = 1;
						}
						if (cycle[l] > cycle[l + 1] && cycle[l + 1] == i && cycle[l] == adj[i][j]) {
							that.status = 1;
						}
					}
					if (cycle[cycle.size() - 1] < cycle[0] && cycle[cycle.size() - 1] == i && cycle[0] == adj[i][j]) {
						that.status = 1;
					}
					if (cycle[cycle.size() - 1] > cycle[0] && cycle[0] == i && cycle[cycle.size() - 1] == adj[i][j]) {
						that.status = 1;
					}
					rib.push_back(that);
				}
			}
		}

		return(rib);
	}
	vector<segment> search_segments(vector<int>& cycle, vector<int>& contact, vector<ribs>& ribs) {
		set<int> withOutG;
		for (int i = 0; i < contact.size(); ++i) {
			if (contact[i] == 0 && adj[i].size() > 0) {
				withOutG.insert(i);
			}
		}
		vector<set<int>> adj3(adj.size());
		for (int i = 0; i < adj.size(); ++i) {
			if (withOutG.count(i) > 0) {
				for (int j = 0; j < adj[i].size(); ++j) {
					if (withOutG.count(adj[i][j]) > 0) {
						adj3[i].insert(adj[i][j]);
						adj3[adj[i][j]].insert(i);
					}
				}
			}
		}
		vector<segment> Segments;
		if (withOutG.size() > 0) {
			vector<int>colors(adj.size());
			vector<int> p(adj.size());
			set<int> ListForOutput;
			set<int> DopPoint;// ребра которые надо добавить
			for (int i = 0; i < adj3.size(); ++i) {
				dfs_for_connectivity(i, p, ListForOutput, colors, adj3, contact);
				if (ListForOutput.size() > 0) {
					for (auto u : ListForOutput) {
						for (int j = 0; j < adj[u].size(); ++j) {
							if (contact[adj[u][j]] == 1) {
								DopPoint.insert(adj[u][j]);
							}
						}
					}
					for (auto u : DopPoint) {
						ListForOutput.insert(u);
					}
					segment a;
					a.type = 1;
					a.points = ListForOutput;
					Segments.push_back(a);
					ListForOutput.clear();
					DopPoint.clear();
				}
			}

		}
		for (int i = 0; i < ribs.size(); ++i) {
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
	vector<int> chain(vector<int>& cycle, vector<int>& contact, vector<ribs>& ribs, segment& That) {
		vector<int> colors(adj.size());
		vector<int> p;
		p.assign(adj.size(), -1);
		int count = 0;
		int end;
		int status = 0;
		for (int i = 0; i < adj.size(); ++i) {
			if (contact[i] == 1 && That.points.count(i) > 0) {
				dfs_for_chain(i, p, colors, contact, count, status);
				end = count;
				break;
			}
		}
		vector<int> chain;
		for (int i = end; p[i] != -1; i = p[i]) {
			chain.push_back(i);
			end = i;
		}
		chain.push_back(p[end]);
		for (int i = 0; i < chain.size(); ++i) {
			contact[chain[i]] = 1;
		}
		return(chain);
	}
};
void include(vector<vector<int>>& face, vector<int>& chain, int The_number_of_face) {
	vector<int> a;
	vector<int> b;
	int First = chain[0];
	int F = 0;
	int E = 0;
	int End = chain[chain.size() - 1];
	int edge = The_number_of_face;
	for (int i = 0; i < face[edge].size(); ++i) {
		if (face[edge][i] == First) {
			F = i;
		}
		if (face[edge][i] == End) {
			E = i;
		}
	}
	if (F > E) {
		vector<int> reser(chain.size());
		for (int i = 0; i < chain.size(); ++i) {
			reser[i] = chain[chain.size() - 1 - i];
		}
		chain = reser;
		int a = F;
		F = E;
		E = a;
	}
	for (int i = F; i <= E; ++i) {
		a.push_back(face[edge][i]);
	}
	for (int i = chain.size() - 2; i > 0; --i) {
		a.push_back(chain[i]);
	}
	for (int i = E; i != F; i = (i + 1) % (face[edge].size())) {
		b.push_back(face[edge][i]);
	}
	for (int i = 0; i < chain.size() - 1; ++i) {
		b.push_back(chain[i]);
	}
	face[edge] = a;
	face.push_back(b);
}
void checking_segments(vector<vector<int>>& face, Graph& value, vector<int>& contact, vector<int>& cycle) {
	vector<ribs> ribs = value.rib(contact, cycle);//после этой строки поставить цикл
	while (true) {
		vector<segment> Segments = value.search_segments(cycle, contact, ribs);
		if (Segments.size() == 0) {
			value.planary = 1;
			return;
		}
		for (int i = 0; i < face.size(); ++i) {
			set<int> point;
			for (int j = 0; j < face[i].size(); ++j) {
				point.insert(face[i][j]);
			}
			for (int j = 0; j < Segments.size(); ++j) {
				int k = 0;
				int k1 = 0;//считаем количество внутренних вершин
				for (auto u : Segments[j].points) {
					if (point.count(u) > 0) {
						k += 1;
					}
					if (contact[u] == 0) {
						k1 += 1;
					}
				}
				if (k == Segments[j].points.size() - k1) {
					Segments[j].prioritet += 1;
					Segments[j].The_number_of_face = i;
				}
			}
		}
		int min = face.size() + 1;
		int k = -1;
		for (int i = 0; i < Segments.size(); ++i) {
			if (Segments[i].prioritet < min) {
				min = Segments[i].prioritet;
				k = i;
			}
		}
		if (min == 0) {
			value.planary = 2;
			return;
		}
		else if (Segments[k].type == 0) {
			vector<int> points;
			for (auto u : Segments[k].points) {
				points.push_back(u);
			}
			int First = points[0];
			int Second = points[1];
			// добавляем этот отрезок сюда;
			for (int i = 0; i < ribs.size(); ++i) {
				if (ribs[i].start == std::min(First, Second) && ribs[i].end == std::max(First, Second)) {
					ribs[i].status = 1;
					break;
				}
			}
			include(face, points, Segments[k].The_number_of_face);
		}
		else {
			//добавляем цепь и ищем ее
			vector<int> chain = value.chain(cycle, contact, ribs, Segments[k]);
			include(face, chain, Segments[k].The_number_of_face);
			for (int i = 0; i < chain.size() - 1; ++i) {
				int start = chain[i];
				int end = chain[i + 1];
				for (int j = 0; j < ribs.size(); ++j) {
					if (ribs[j].start == std::min(start, end) && ribs[j].end == std::max(start, end)) {
						ribs[j].status = 1;
						break;
					}
				}
			}
		}
	}
}
void gamma_algorithm(Graph& value) {
	vector<int> cycle = value.cycle_search();
	if (cycle[0] == -1) {
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
		checking_segments(face, value, contact, cycle);
	}
}
void planar(Graph& g) {
	vector<Graph> AllGraph;
	g.remove_the_bridges();
	g.making_the_graph_ready_for_gamma(AllGraph);
	for (int i = 0; i < AllGraph.size(); ++i) {
		gamma_algorithm(AllGraph[i]);
		if (AllGraph[i].planary == 2) {
			cout << "NO";
			return;
		}
	}
	cout << "YES";
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
	planar(g);
}