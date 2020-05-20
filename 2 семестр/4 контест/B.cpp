/*ООО "Новые Железные Дороги" поручило вам разработать систему бронирования билетов на новый маршрут поезда дальнего следования. Маршрут проходит через N станций, занумерованных от 0 до N-1.
Вместимость поезда ограничена.
В систему бронирования последовательно приходят запросы от пассажиров с указанием номера начальной и конечной станции, а также количество билетов, которые пассажир хочет приобрести.
Требуемая скорость обработки каждого запроса - .
Формат ввода
Первая строка содержит число N –– количество станций (1 ≤ N ≤ 50 000).
Вторая строка содержит начальное количество проданных билетов.
В примере продано по одному билету на перегонах 0->1 и 4->5.
В третьей строке указана вместимость поезда. В четвёртой — количество запросов на бронирование.
Далее идут непосредственно запросы в виде: номер начальной станции, номер конечной станции, количество запрашиваемых билетов.
Формат вывода
Необходимо вывести номера запросов, которые не удалось выполнить из-за отсутствия свободных мест.*/
#include <iostream>
#include <vector>
#include<algorithm>
#include <cmath>
#define ll long long
using namespace std;
struct InTree {//будем ее использовать, чтобы хранить всю инфу отрезка
	ll Max = 0;
	ll current = 0;
	ll add = 0;
};
class SegmentTree {
private:
	vector<InTree> tree;
	vector<ll> base;
	ll count;//вместимость
	vector<ll> result;
public:
	SegmentTree(ll n, vector<ll> a, ll Max_) {
		tree.resize(4 * n);
		base = a;
		count = Max_;
	}
	void Build(ll index, ll left, ll right, vector < ll>& a) {
		if (left != right) {
			ll middle = (left + right) / 2;
			Build(2 * index, left, middle, a);
			Build(2 * index + 1, middle + 1, right, a);
			tree[index].Max = std::max(tree[2 * index].Max, tree[2 * index + 1].Max);
		}
		else {
			tree[index].Max = a[left];
		}
	}

	void add(ll index, ll tree_left, ll tree_right, ll left_range, ll right_range, ll number) {
		if (left_range > right_range)
			return;
		if (tree_left == left_range && tree_right == right_range) {
			tree[index].current +=number;
			return;
		}
		ll middle = (tree_left + tree_right) / 2;
		if (left_range <= middle) {
			add(2 * index, tree_left, middle, left_range, std::min(right_range, middle), number);
		}
		if (right_range > middle) {
			add(2 * index + 1, middle + 1, tree_right, std::max(middle + 1, left_range),right_range, number);
		}
		tree[index].Max = std::max(tree[index * 2].Max+ tree[index * 2].current, tree[index * 2+1].Max + tree[index * 2+1].current);
	}
	ll GetMax(ll index, ll tree_left, ll tree_right, ll left_range, ll right_range) {
		if (left_range > right_range)
			return 0;
		if (tree_left == left_range && tree_right == right_range) {
			return tree[index].Max+tree[index].current;
		}
		ll middle = (tree_left + tree_right) / 2;
		ll l = 0;
		ll r = 0;
		if (left_range <= middle) {
			l=GetMax(2 * index, tree_left, middle, left_range, std::min(right_range, middle));
		}
		if (right_range > middle) {
			r=GetMax(2 * index + 1, middle + 1, tree_right, std::max(middle + 1, left_range), right_range);
		}
		return(std::max(l, r)+tree[index].current);
	}
	void Algo(ll start, ll end, ll people, ll i) {
		ll now_max = GetMax(1, 0, base.size()-1, start, end-1);
		if (now_max + people > count) {
			result.push_back(i);
		}
		else {
			add(1,0, base.size()-1, start, end - 1, people);
		}
	}
	vector<ll> GetResult() {
		return result;
	}
};

int main()
{
	ll n, Max, count;
	cin >> n;
	vector<ll> a(n-1);
	for (ll i = 0; i < n - 1; ++i) {
		ll now;
		cin >> now;
		a[i] = now;
	}
	cin >> Max >> count;
	SegmentTree Tree(n, a, Max);
	Tree.Build(1, 0, n - 2, a);
	for (ll i = 0; i < count; ++i) {
		ll start, end, people;
		cin >> start >> end >> people;
		Tree.Algo(start, end, people, i);
	}
	auto result = Tree.GetResult();
	if (!result.empty()) {
		for (auto u : result) {
			cout << u << ' ';
		}
	}
};
