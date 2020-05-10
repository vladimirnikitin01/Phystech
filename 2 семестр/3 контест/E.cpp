/*Шрек и Осёл уже были на пути домой. Им оставалось только преодолеть лес, который отделял их от болота. Но они поссорились, поэтому не хотят идти вместе.
Лес представляет собой опушки, пронумерованы числами от 1 до n и соединенные m дорожками (может быть несколько дорожек соединяющих две опушки, могут быть дорожки,
соединяющие опушку с собой же). Из-за ссоры, если по дорожке прошел один из друзей, то второй по той же дорожке уже идти не может. Сейчас друзья находятся на опушке с номером s,
а болото Шрека — на опушке с номером t. Помогите Шреку и Ослу добраться до болота.*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;
struct rib {
    long long vertex;
    long long capacity = 1;
    long long flow = 0;
    bool irreversible = true;
};
class Graph {
private:
    vector<vector<rib>> adj;
public:
    Graph(size_t n)
    {
        adj.resize(n);
    }
    void add(ll start, ll end) {
        ll index = Index2(start, end);
        if (index == -1) {
            rib RIB;
            RIB.vertex = end;
            RIB.capacity = 1;
            RIB.flow = 0;
            RIB.irreversible = true;
            adj[start].push_back(RIB);
            RIB.capacity = 0;
            RIB.vertex = start;
            RIB.irreversible = false;
            adj[end].push_back(RIB);
        }
        else {
            adj[start][index].capacity += 1;
        }
    }
    ll Index(ll start, ll end) {
        for (size_t i = 0; i < adj[end].size(); ++i) {
            if (adj[end][i].vertex == start) {
                return(i);
            }
        }
        return -1;
    }

    ll Index2(ll start, ll end) {
        for (size_t i = 0; i < adj[start].size(); ++i) {
            if (adj[start][i].vertex == end) {
                return(i);
            }
        }
        return -1;
    }
    std::pair<string, vector<vector<ll>>> algorithm(ll s, ll t) {
        std::pair<string, vector<vector<ll>>> answer;
        vector<bool> used;
        used.assign(adj.size(), false);
        ll result = dfs(s, t, 100000, used);
        if (result < 1) {
            answer.first = "NO";
            return(answer);
        }
        if (result == 1) {
            used.assign(adj.size(), false);
            ll new_result = dfs(s, t, 100000, used);
            if (new_result < 1) {
                answer.first = "NO";
                return(answer);
            }
        }
        bool status = true;
        answer.first = "YES";
        vector<ll> pair_first;
        pair_first.push_back(s);
        used.assign(adj.size(), false);
        usual_dfs(s, t, pair_first, used, status);

        status = true;
        vector<ll> pair_second;
        pair_second.push_back(s);
        used.assign(adj.size(), false);
        usual_dfs(s, t, pair_second, used, status);


        vector<vector<ll>> vector_answer(2);
        vector_answer[0] = pair_first;
        vector_answer[1] = pair_second;
        answer.second = vector_answer;
        return(answer);
    }
    ll dfs(ll start, ll end, ll c, vector<bool>& used) {
        if (end == start) {
            return c;
        }
        used[start] = true;
        for (size_t i = 0; i < adj[start].size(); ++i) {
            if ((adj[start][i].flow < adj[start][i].capacity) && (used[adj[start][i].vertex] == false)) {
                ll result = dfs(adj[start][i].vertex, end, std::min(c, adj[start][i].capacity - adj[start][i].flow), used);
                if (result > 0) {
                    adj[start][i].flow += result;
                    ll index = Index(start, adj[start][i].vertex);
                    adj[adj[start][i].vertex][index].flow -= result;
                    return result;
                }
            }
        }
        return 0;
    }
    void usual_dfs(ll start, ll end, vector<ll>& vertexes, vector<bool>& used, bool& status) {
        used[start] = true;
        for (size_t i = 0; i < adj[start].size(); ++i) {
            if (status == false) {
                break;
            }
            if (adj[start][i].irreversible == true && adj[start][i].flow > 0 && used[adj[start][i].vertex] == false) {
                vertexes.push_back(adj[start][i].vertex);
                adj[start][i].flow -= 1;
                if (adj[start][i].vertex != end) {
                    usual_dfs(adj[start][i].vertex, end, vertexes, used, status);
                }
                else {
                    status = false;
                }
            }
        }
    }
};
int main()
{
    ll n, m, s, t;
    cin >> n >> m >> s >> t;
    Graph g(n);
    for (size_t i = 0; i < m; ++i) {
        ll start, end;
        cin >> start >> end;
        g.add(start - 1, end - 1);
    }
    std::pair<string, vector<vector<ll>>> result = g.algorithm(s - 1, t - 1);
    if (result.first == "NO") {
        cout << "NO";
    }
    else {
        cout << "YES" << std::endl;
        for (auto u : result.second[0]) {
            cout << u + 1 << ' ';
        }
        cout << std::endl;
        for (auto u : result.second[1]) {
            cout << u + 1 << ' ';
        }
    }
}