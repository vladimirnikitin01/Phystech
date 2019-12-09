/*В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел башню максимальной высоты. Б
ашня — это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, третий стоит на плечах у второго и т.д.
Каждый атлет характеризуется силой si (kg) и массой mi (kg). Сила — это максимальная масса, которую атлет способен держать у себя на плечах. 
К сожалению ни один из атлетов не умеет программировать, так как всю жизнь они занимались физической подготовкой, и у них не было времени на изучение языков программирования. 
Помогите им, напишите программу, которая определит максимальную высоту башни, которую они могут составить.
Известно, что если атлет тяжелее, то он и сильнее: если mi>mj, то si > sj. 
Атлеты равной массы могут иметь различную силу.*/
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int Partition(vector<int>& a, int start, int end) {
	if (end > start) {
		int m = (start + end) / 2;
		swap(a[start], a[m]);
		int i = end;
		for (int j = end; j >= (start + 1); --j) {
			if (a[j] >= a[start]) {
				swap(a[i], a[j]);
				--i;
			}
		}
		swap(a[i], a[start]);
		return(i);
	}
}
void qsort(vector <int>& a, int start, int end) {
	if (start < end) {
		int p = Partition(a, start, end);
		qsort(a, start, p - 1);
		qsort(a, p + 1, end);
	}
}
int result(vector <int> &mi, vector<int> &si) {
	qsort(mi, 0, mi.size() - 1);
	qsort(si, 0, si.size() - 1);
	int h = 1;
	int massa = mi[0];
	for (int i = 1; i < mi.size(); ++i) {
		if (massa <= si[i]) {
			massa += mi[i];
			++h;
		}
	}
	return (h);
}
int main() {
	string s;
	vector<int> mi;
	vector<int> si;// масса и сила, так обозначаются в условии
	while (getline(cin, s)) {
		string s1,s2;
		int probel = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == ' ') {
				probel = 1;
			}
			if (probel == 0) {
				s1 += s[i];
			}
			else if (s[i] != ' ' && probel == 1) {
				s2 += s[i];
			}
		}
		int m = stoi(s1);
		int s = stoi(s2);
		mi.push_back(m);
		si.push_back(s);
	}
	int res = result(mi, si);
	cout << res;
}