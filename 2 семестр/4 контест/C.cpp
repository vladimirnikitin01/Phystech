/*У художника-авангардиста есть полоска разноцветного холста. За один раз он перекрашивает некоторый отрезок полоски в некоторый цвет.
После каждого перекрашивания специально обученный фотограф делает снимок части получившегося творения для музея современного искусства
. Для правильного экспонирования требуется знать яркость самого темного цвета на выбранном фотографом отрезке. Напишите программу для определения яркости самого темного цвета на отрезке.
Требуемая скорость определения яркости — O(log N).
Цвет задается тремя числами R, G и B (0 ≤ R, G, B ≤ 255), его яркость = R + G + B.
Цвет (R1, G1, B1) темнее цвета (R2, G2, B2), если R1 + G1 + B1 < R2 + G2 + B2.
Формат ввода
Первая строка содержит число N –– длина отрезка (координаты [0...N-1]).
Затем следует N строк по 3 числа –– цвета отрезка.
Следующая строка содержит число K –– количество перекрашиваний и фотографирований.
Затем задано K строк, описывающих перекрашивание и фотографирование.
В каждой такой строке 7 натуральных чисел: C, D, R, G, B, E, F, где [C, D] –– координаты перекрашиваемого отрезка, (R, G, B) –– цвет покраски, [E, F] –– фотографируемый отрезок.
Формат вывода
Требуется вывести K целых чисел. Каждое число –– яркость самого темного цвета на отрезке [E, F] после соответствующего окрашивания.*/
#include <iostream>
#include <vector>
#include<algorithm>
#include <cmath>
#define ll long long
using namespace std;
struct InTree {//будем ее использовать, чтобы хранить всю инфу отрезка
	ll Min = 800; 
	ll current = 0;
	ll add = -1;
};
class SegmentTree {
private:
	vector<InTree> tree;
	vector<ll> base;
	vector<ll> result;
public:
	SegmentTree(ll n, vector<ll> a) {
		tree.resize(4 * n);
		base = a;
	}
	void Build(ll index, ll left, ll right, vector < ll>& a) {
		if (left != right) {
			ll middle = (left + right) / 2;
			Build(2 * index, left, middle, a);
			Build(2 * index + 1, middle + 1, right, a);
			tree[index].Min = std::min(tree[2 * index].Min, tree[2 * index + 1].Min);
		}
		else {
			tree[index].Min = a[left];
		}
	}

	void Push(ll index, ll left, ll right) {
		if (left == right)
			return;
		if (tree[index].add != -1) {
			tree[index * 2].add = tree[index].add;
			tree[index * 2 + 1].add = tree[index].add;
			tree[index*2].Min = tree[index].add;
			tree[index*2+1].Min = tree[index].add;
			tree[index].add = -1;
		}
	}

	void ChangeColor(ll index, ll tree_left, ll tree_right, ll left_range, ll right_range, ll number) {
		Push(index, tree_left, tree_right);
		if (left_range > right_range)
			return;
		if (tree_left == left_range && tree_right == right_range) {
			tree[index].add = number;
			tree[index].Min = number;
			return;
		}
		ll middle = (tree_left + tree_right) / 2;
		if (left_range <= middle) {
			ChangeColor(2 * index, tree_left, middle, left_range, std::min(right_range, middle), number);
		}
		if (right_range > middle) {
			ChangeColor(2 * index + 1, middle + 1, tree_right, std::max(middle + 1, left_range), right_range, number);
		}
		tree[index].Min = std::min(tree[index * 2].Min, tree[index * 2 + 1].Min);
	}

	ll GetMin(ll index, ll tree_left, ll tree_right, ll left_range, ll right_range) {
		Push(index, tree_left, tree_right);
		if (left_range > right_range)
			return 800;
		if (tree_left == left_range && tree_right == right_range) {
			return tree[index].Min;
		}
		ll middle = (tree_left + tree_right) / 2;
		ll l = 800;
		ll r = 800;
		if (left_range <= middle) {
			l = GetMin(2 * index, tree_left, middle, left_range, std::min(right_range, middle));
		}
		if (right_range > middle) {
			r = GetMin(2 * index + 1, middle + 1, tree_right, std::max(middle + 1, left_range), right_range);
		}
		return(std::min(l, r));
	}

	void Algo(ll c,ll d,ll brightness,ll e, ll f) {
		ChangeColor(1,0,base.size()-1, c, d, brightness);
		ll res = GetMin(1, 0, base.size() - 1, e, f);
		result.emplace_back(res);
	}
	vector<ll> GetResult() {
		return result;
	}
};

int main()
{
	ll n,r,g,b;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; ++i) {
		cin >> r >> g >> b;
		a[i] = r + g + b;
	}
	SegmentTree tree(n, a);
	tree.Build(1, 0, n - 1, a);
	ll k;
	cin >> k;
	for (ll i = 0; i < k; ++i) {
		ll c, d, r, g, b, e, f;
		cin >> c >> d >> r>>g >> b >> e >> f;
		tree.Algo(c, d, r + g + b, e, f);
	}
	auto result = tree.GetResult();
	for (auto u : result) {
		cout << u << ' ';
	}
};
