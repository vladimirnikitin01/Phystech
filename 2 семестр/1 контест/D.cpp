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
	void  dfs_for_chain(int s, vector<int>& p, vector<int>& colors, vector<int>& contact, int& count, int &status) {
		if (colors[s] != 0) {
			return;
		}
		colors[s] = 1;
		count += 1;
		for (auto u : adj[s]) {
			if (count > 1 && status==0) {
				if (p[s] == u) {}
				else if (colors[u] == 0) {
					p[u] = s;
					if (contact[u] == 1) {
						count = u;
						status = 1;
						return;
					}
					dfs_for_chain(u, p, colors, contact, count,status);
				}
				else if (colors[u] == 1) {
					return;
				}
			}
			else if (count == 1 && status == 0) {
				if (p[s] == u) {}
				else if (colors[u] == 0 && contact[u] == 0) {
					p[u] = s;
					dfs_for_chain(u, p, colors, contact, count,status);
				}
				else if (colors[u] == 1) {
					return;
				}
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
			if (contact[i] == 0) {
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
				if (k + k1 == Segments[j].points.size()) {
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
			int status_second = 0;//встречалось ли оно перед first или нет
			int number_second = 0;
			for (int i = 0; i < face[Segments[k].The_number_of_face].size(); ++i) {
				if (face[Segments[k].The_number_of_face][i] == Second) {
					status_second = 1;
					number_second = i;
				}
				if (face[Segments[k].The_number_of_face][i] == First) {
					vector<int> a;
					vector<int> b;
					if (status_second == 1) {
						for (int j = number_second; j <= i; ++j) {
							a.push_back(face[Segments[k].The_number_of_face][j]);
						}
						for (int j = i; j <= number_second; j = (j + 1) % face[Segments[k].The_number_of_face].size()) {
							b.push_back(face[Segments[k].The_number_of_face][j]);
						}

					}
					else {
						for (int j = i;; ++j) {
							a.push_back(face[Segments[k].The_number_of_face][j]);
							if (face[Segments[k].The_number_of_face][j] == Second) {
								break;
							}
						}
						for (int j = i;; j = (j + 1) % face[Segments[k].The_number_of_face].size()) {
							if (face[Segments[k].The_number_of_face][j] == Second) {
								status_second = 1;
							}
							if (status_second == 1) {
								b.push_back(face[Segments[k].The_number_of_face][j]);
							}
							if (status_second == 1 && face[Segments[k].The_number_of_face][j] == First) {
								break;
							}
						}
					}
					face[Segments[k].The_number_of_face] = a;
					face.push_back(b);
					break;
				}
			}
		}
		else {
			//добавляем цепь и ищем ее
			vector<int> chain = value.chain(cycle, contact, ribs, Segments[k]);
			vector<int> a;
			vector<int> b;
			int First = chain[0];
			int F = 0;
			int E = 0;
			int End = chain[chain.size() - 1];
			int edge = Segments[k].The_number_of_face;
			for (int i = 0; i < face[edge].size(); ++i) {
				if (face[edge][i] == First) {
					F = i;
				}
				if (face[edge][i] == End) {
					E = i;
				}
			}
			if (F > E) {
				vector<int> reser(face[edge].size());
				for (int i = 0; i < face[edge].size(); ++i) {
					reser[i] = face[edge][face[edge].size() - 1 - i];
				}
				face[edge] = reser;
			}
			for (int i = F; i < E; ++i) {
				a.push_back(face[edge][i]);
			}
			for (int i = chain.size() - 1; i > 0; --i) {
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
	if (cycle.size() == 0) {
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
void planarTEST(Graph& g) {
	gamma_algorithm(g);
	if (g.planary == 2) {
		cout << "NO";
		return;
	}
	cout << "YES";
}
void planar(Graph& g) {
	vector<Graph> AllGraph;
	g.making_the_graph_ready_for_gamma(AllGraph);
	for (int i = 0; i < AllGraph.size(); ++i) {
		gamma_algorithm(AllGraph[i]);
		if (AllGraph[i].planary == 2) {
			cout << "NO";
			return;
		}
		cout << "YES";
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
	planarTEST(g);
}