/*Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.
Для решения задачи используйте структуру данных Sparse Table. Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных .
Формат ввода
В первой строке заданы 2 числа: размер последовательности N и количество диапазонов M.
Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел - границ диапазонов.
Гарантируется, что каждый диапазон содержит как минимум 2 элемента.
Формат вывода
Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.*/

#include <iostream>
#include <vector>
#include<algorithm>
#include <cmath>
#define ll long long
using namespace std;

class SearchSecondStatistic {
public:
    vector<ll> AllAlgorithm(vector<std::pair<ll, ll>>& all_pairs, vector<ll>& a) {
        vector<vector<ll>> SparseTable(a.size());
        ll j = floor(log(a.size()) / log(2))+1;
        for (ll i = 0; i < a.size(); ++i) {
            SparseTable[i].assign(j, 0);
        }
        //подготовка структуры, а именно подсчет log всех длин
        vector<ll> lengths(a.size() + 1);
        for (ll i = 1; i < lengths.size(); ++i) {
            lengths[i] = floor(log(i) / log(2));
        }
        //заполним таблицу
        for (ll i = 0; i < a.size(); ++i) {
            SparseTable[i][0] = i;
        }
        for (ll j = 1; std::pow(2, j) <= a.size(); ++j) {
            for (ll i = 0; i < a.size(); ++i) {
                if (i + pow(2, j) <= a.size()) {//тут мб ошибка
                    if (a[SparseTable[i][j - 1]] > a[SparseTable[i + pow(2, j - 1)][j - 1]]) {
                        SparseTable[i][j] = SparseTable[i + pow(2, j - 1)][j - 1];
                    }
                    else {
                        SparseTable[i][j] = SparseTable[i][j - 1];
                    }
                }
            }
        }
        vector<ll> result(all_pairs.size());
        for (ll i = 0; i < all_pairs.size(); ++i) {
            ll middle=TheSecondStatistics(all_pairs[i].first, all_pairs[i].second, lengths, SparseTable, a);
            ll left = -1;
            ll right = -1;
            if (middle - 1 >= all_pairs[i].first) {
                left = TheSecondStatistics(all_pairs[i].first, middle - 1, lengths, SparseTable, a);
            }
            if (middle + 1 <= all_pairs[i].second) {
                right = TheSecondStatistics(middle + 1, all_pairs[i].second, lengths, SparseTable, a);
            }
            if (left != -1 && right != -1) {
                result[i] = std::min(a[left], a[right]);
            }
            else if (left == -1) {
                result[i] = (a[right]);
            }
            else {
                result[i] = (a[left]);
            }
        }
        return(result);
    }
    ll TheSecondStatistics(ll start, ll end, vector<ll>& lengths, vector<vector<ll>>& SparseTable, vector<ll>& a) {
        ll j = lengths[end - start + 1];
        ll result = 0;
        if (a[SparseTable[start][j]] > a[SparseTable[end - pow(2, j)+1][j]]) {
            result = SparseTable[end - pow(2, j) + 1][j];
        }
        else {
            result = SparseTable[start][j];
        }
        return(result);
    }
};

int main()
{
    ll n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) {
        ll now;
        cin >> now;
        a[i] = now;
    }
    vector<std::pair<ll, ll>> all_pairs(m);
    for (ll i = 0; i < m; ++i) {
        ll start, end;
        cin >> start >> end;
        all_pairs[i] = { start-1, end-1 };
    }
    SearchSecondStatistic work;
    auto result=work.AllAlgorithm(all_pairs, a);
    for (ll i = 0; i < m; ++i) {
        cout << result[i] << std::endl;
    }

}
