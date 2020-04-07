/*Рик отправляет Морти в путешествие по N вселенным. У него есть список всех существующих однонаправленных телепортов. Чтобы Морти не потерялся, Рику необходимо узнать,
между какими вселенными существуют пути, а между какими нет. Помогите ему в этом!
Формат ввода
На первой строке задано количество вселенных N (1 ≤ N ≤ 1 000). Следующие N строк имеют длину N, состоят из нулей и единиц и задают матрицу смежности вселенных.
Единица в i-й строке j-м столбце обозначает телепорт из i-й вселенной в j-ю.*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <bitset>
using namespace std;
class Graph {
private:
	vector<vector<bitset<32>>> adj;
	size_t columns = 0;
public:
	Graph(size_t n)
	{
		adj.resize(n);
		size_t size = n /32;
		if (n % 32 != 0) {
			size += 1;
		}
		columns = size;
	}
	void add(string s, int number_of_adj) {
		size_t number_of_column = 0;
		bitset<32> now;
		int k=0;
		for (size_t i = 0; i < s.size(); ++i) {
			if (number_of_column == columns - 1 && s.size()%32!=0) {
				int numbers = s.size() % 32;
				now.reset();
				int now_i = i;
				for (k = 0; k < numbers; ++k) {
					now[k] = s[now_i]-'0';
					++now_i;
				}
				adj[number_of_adj].push_back(now);
				break;
			}
			now[k] = s[i]-'0';
			++k;
			if (k == 32) {
				k = 0;
				adj[number_of_adj].push_back(now);
				++number_of_column;
			}
		}
	}
	void out(vector<vector<bitset<32>>>& result) {
		for (size_t i = 0; i < result.size(); ++i) {
			size_t number_of_column = 0;
			for (int y = 0; y < columns; ++y) {
				if (number_of_column == columns - 1 && adj.size()%32!=0) {
					int number = adj.size() % 32;
					bitset<32> now = result[i][number_of_column];
					for (int j =0; j < number; ++j) {
						cout << now[j];
					}
					break;
				}
				bitset<32> now = adj[i][y];
				for (int j = 0; j < 32; ++j) {
					cout << now[j];
				}
				++number_of_column;
			}
			cout << endl;
		}
	}
	void algorithm() {
		vector<vector<bitset<32>>>& result = adj;
		Floyd_Warshell(result);
		out(result);
	}
	void Floyd_Warshell(vector<vector<bitset<32>>>& result) {
		size_t n = adj.size();
		for (size_t k = 0; k < n; ++k) {
			for (size_t i = 0; i < n; ++i) {
				bitset<32> now_one_part_of_adj= adj[i][(k) / 32];
				int now = now_one_part_of_adj[k % 32];
				if (now==1) {
					for (size_t j = 0; j < columns; ++j) {
						adj[i][j] |= adj[k][j];
					}
				}
			}
		}
	}
};
int main()
{
	size_t n;
	cin >> n;
	Graph g(n);
	for (size_t i = 0; i < n; ++i) {
		string s;
		cin >> s;
		g.add(s,i);
	}
	g.algorithm();
}