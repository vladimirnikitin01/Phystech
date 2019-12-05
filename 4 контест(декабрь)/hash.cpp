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
		if (body.size() < 10) {
			TableOfPrimeNumber(PrimeNumber);
		}
		if (inserted * 4 >= 3*body.size()) {
			int size = body.size() * 2;
			int j = 0;
			while (true) {
				if (size >= PrimeNumber[j]) {
					size = PrimeNumber[j];
					break;
				}
				++j;
			}
			vector<item> body2(body.size());
			for (int j = 0; j < body.size(); ++j) {
				body2[j] = body[j];
			}
			body.erase(body.begin(), body.end());
			body.resize(size);
			for (int j = 0; j < body2.size(); ++j) {
				if (body2[j].tag == item::BUSY) {
					insert(body2[j].key);
				}
			}
		}
		for (auto h = hash(key); ; h = (h + hash2(key)) % body.size()) {
			if (body[h].tag == item::EMPTY || body[h].tag==item::DELETED) {
				body[h] = { key,item::BUSY };
				return true;
			}
			assert(body[h].tag == item::BUSY);
			if (body[h].key == key)
				return false;
		}
		return true;
	}
	bool erase(string const& key) {
		for (auto h = hash(key); ; h = (h + hash2(key)) % body.size()) {
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) return false;
			assert (body[h].tag == item::BUSY);
			if (body[h].key == key) {
				body[h].tag = item::DELETED;
				return true;
			}
		}
		assert(false);
		return false;
	}
	bool find(string const& key) {
		for (auto h = hash(key); ; h = (h + hash2(key)) % body.size()) {
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) continue;
			assert(body[h].tag == item::BUSY);
			if (body[h].key == key) return true;
		}
		assert(false);
		return false;
	}
	void TableOfPrimeNumber(vector<int>& PrimeNumber) {
		for (int i = 0; i < 350; ++i) {
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
	vector<int> PrimeNumber;
	size_t inserted = 0;
	size_t hash(string const& key) {
		int a = 31;
		size_t h = 0;
		for (int i = 0; i < key.size(); ++i) {
			h = ((h + key[i]) * a) % key.size();
		}
		return h;
	}
	size_t hash2(string const& key) {
		int a = 29;
		size_t h = 0;
		for (int i = 0; i < key.size(); ++i) {
			h = (((h + key[i]) * a) % (key.size()));
		}
		return h;
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