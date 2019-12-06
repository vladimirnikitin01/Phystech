/*Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. 
Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. 
Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, 
удаления строки из множества и проверки принадлежности данной строки множеству.Для разрешения коллизий используйте двойное хеширование.*/
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;
class hashtable {
public:
	hashtable(size_t init_size = 8) {
		body.resize(init_size);
	}
	~hashtable() {};
	bool insert(string const& key) {
		if (inserted * 4 >= 3 * body.size()) {
			int size;
			for (int i = 0; i <15; ++i) {
				if (PrimeNumber[i] == body.size()) {
					size = PrimeNumber[i + 1];
					break;
				}
				if (body.size() == 8) {
					size = 17;
				}
			}
			vector<item> body2(body.size());
			for (int j = 0; j < body.size(); ++j) {
				body2[j] = body[j];
			}
			body.erase(body.begin(), body.end());
			body.resize(size);
			for (int j = 0; j < body2.size(); ++j) {
				if (body2[j].tag == item::BUSY) {
					inserted--;
					insert(body2[j].key);
				}
			}
		}
		int h2;
		if (body.size() == 8) {
			h2 = 1;
		}
		else {
			h2 = hash2(key);
		}
		int i = 0;
		for (auto h = hash(key); i < 2 * body.size(); h = (h + h2) % body.size()) {
			++i;
			if (body[h].tag == item::EMPTY || body[h].tag==item::DELETED) {
				body[h] = { key,item::BUSY };
				inserted++;
				return true;
			}
			assert(body[h].tag == item::BUSY);
			if (body[h].key == key)
				return false;
		}
		return true;
	}
	bool erase(string const& key) {
		int h2;
		if (body.size() == 8) {
			h2 = 1;
		}
		else {
			h2 = hash2(key);
		}
		int i = 0;
		for (auto h = hash(key); i < 2 * body.size(); h = (h + h2) % body.size()) {
			++i;
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) continue;
			assert (body[h].tag == item::BUSY);
			if (body[h].key == key) {
				body[h].tag = item::DELETED;
				inserted--;
				return true;
			}
		}
		assert(false);
		return false;
	}
	bool find(string const& key) {
		int h2;
		if (body.size() == 8) {
			h2 = 1;
		}
		else {
			h2=hash2(key);
		}
		int i = 0;
		for (auto h = hash(key); i<2*body.size(); h = (h + h2) % body.size()) {
			++i;
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) continue;
			assert(body[h].tag == item::BUSY);
			if (body[h].key == key) return true;
		}
		return false;
	}
	void TableOfPrimeNumber(vector<int>& PrimeNumber) {
		for (int i = 0; i < 350000; ++i) {
			int k = 0;
			for (int j = 2; 2 * j <= i; ++j) {
				if (i % j == 0) {
					k = 1;
					break;
				}
			}
			if (k == 0) {
				PrimeNumber.push_back(i);
			}
		}
	}
private:
	struct item {
		item(string const& key="", int tag = item::EMPTY) : key(key), tag(tag) {};
		string key;
		enum {
			EMPTY,
			BUSY,
			DELETED
		};
		int tag;
	};
	vector<item> body;
	vector<int> PrimeNumber = { 17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853, 87719, 175447, 350899 };
	size_t inserted = 0;
	size_t hash(string const& key) {
		int a = 31;
		size_t h = 0;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h+key[i]) * a); 
			h = h % (body.size());
		}
		return (h);
	}
	size_t hash2(string const& key) {
		int a = 31;
		size_t h = 0;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h + key[i]) * a);
			h = (h % (body.size()-1))+1;
		}
		return (h);
	}
};
int main() {
	hashtable ht(8);
	string s1;
	while (getline(cin,s1)) {
		string s="";
		for (int j = 2; j < s1.size(); ++j) {
			s += s1[j];
		}
		if (s1[0] == '+') {
			bool ok=ht.find(s);
			if (ok != false) {
				cout << "FAIL" << endl;
			}
			else {
				ht.insert(s);
				cout << "OK"<<endl;
			}
		}
		else if (s1[0] == '-') {
			bool ok = ht.find(s);
			if (ok == false) {
				cout << "FAIL" << endl;
			}
			else {
				ht.erase(s);
				cout << "OK" << endl;
			}
		}
		else {
			bool ok = ht.find(s);
			if (ok == false) {
				cout << "FAIL" << endl;
			}
			else {
				cout << "OK" << endl;
			}
		}
	}
}