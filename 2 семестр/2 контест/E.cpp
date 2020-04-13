/*Рик решил на день почувствовать себя бизнесменом!
В городе есть несколько обменников валюты. В рамках данной задачи считаем, что каждый обменник специализируется только на двух валютах и может производить операции только с ними.
Возможно, существуют обменники, специализирующиеся на одинаковых парах валют. В каждом обменнике — свой обменный курс: курс обмена A на B — это количество единиц валюты B, выдаваемое за 1 единицу валюты A.
Также в каждом обменнике есть комиссия — сумма, которую вы должны заплатить, чтобы производить операцию. Комиссия взимается в той валюте, которую меняет клиент.
Например, если вы хотите поменять 100 долларов США на русские рубли в обменнике, где курс обмена равен 29.75, а комиссия равна 0.39, вы получите (100 - 0.39) ⋅ 29.75 = 2963.3975 рублей (эх, были времена).
Вы точно знаете, что в городе используется всего N валют. Пронумеруем их числами 1, 2, …, N. Тогда каждый обменник представляют 6 чисел: целые A и B — номера обмениваемых валют,
а также вещественные RAB, CAB, RBA и CBA — обменные курсы и комиссии при переводе из A в B и из B в A соответственно.
Рик обладает некоторой суммой в валюте S. Он задаётся вопросом, можно ли, после нескольких операций обмена увеличить свой капитал.
Конечно, он хочет, чтобы в конце его деньги вновь были в валюте S. Помогите ему ответить на его вопрос. Рик должен всегда должен иметь неотрицательную сумму денег.
Формат ввода
Первая строка содержит четыре числа: N — количество валют, M — количество обменников, S — валюта, которой располагает Рик, и V — количество единиц этой валюты.
Следующие M строк содержат по 6 чисел, которые задают описание соответствующих обменников в описанном выше формате. Числа разделяются одним или несколькими пробелами.
Выполняются ограничения , V — вещественное число, .
В каждом обменнике курсы обмена и комиссии — вещественные числа, задаваемые с точностью не выше двух знаков после запятой в десятичном представлении, причём .
Назовём последовательность операций обмена простой, если каждый обменник используется в ней не более одного раза. Вы можете считать,
что отношение итоговой суммы Рика к исходной не будет превосходить 104 при любой простой последовательности операций.*/
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
struct rib {
	size_t vertex;
	double exchange_rate;
	double commission;
};
class Graph {
private:
	vector<vector<rib>> adj;
public:
	Graph(size_t n)
	{
		adj.resize(n);
	}
	void add(size_t A, size_t B, double RAB, double CAB) {
		rib RIB;
		RIB.vertex = B;
		RIB.exchange_rate = RAB;
		RIB.commission = CAB;
		adj[A].push_back(RIB);
	}
	bool algorithm(size_t s, double v) {
		vector<double> result;
		result.assign(adj.size(), -100000000);
		result[s] = v;
		bool answer= Ford_Bellman(result, s);
		return(answer);
	}
	bool Ford_Bellman(vector<double>& result, size_t s) {
		for (size_t i = 0; i < adj.size()-1; ++i) {
			for (size_t j = 1; j < adj.size(); ++j) {
				for (size_t l = 0; l < adj[j].size(); ++l) {
					double new_money = (result[j] - adj[j][l].commission) * adj[j][l].exchange_rate;
					if (result[adj[j][l].vertex] < new_money && new_money >= 0) {
						result[adj[j][l].vertex] = new_money;
					}
				}
			}
		}
		vector<double> result1 = result;
		for (size_t j = 1; j < adj.size(); ++j) {
			for (size_t l = 0; l < adj[j].size(); ++l) {
				double new_money = (result[j] - adj[j][l].commission) * adj[j][l].exchange_rate;
				if (result[adj[j][l].vertex] < new_money && result[j] - adj[j][l].commission >= 0) {
					result[adj[j][l].vertex] = new_money;
				}
			}
		}
		bool status_of_change = false;
		for (size_t i = 1; i < result.size(); ++i) {
			if (result1[i] < result[i]) {
				status_of_change = true;
				break;
			}
		}
		return(status_of_change);
	}
};
int main()
{
	size_t n, m, s;
	double v;
	cin >> n >> m >> s >> v;
	Graph g(n + 1);
	for (size_t i = 0; i < m; ++i) {
		size_t A, B;
		double RAB, CAB, RBA, CBA;
		cin >> A >> B >> RAB >> CAB >> RBA >> CBA;
		g.add(A, B, RAB, CAB);
		g.add(B, A, RBA, CBA);
	}
	bool answer = g.algorithm(s,v);
	if (answer) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}
}