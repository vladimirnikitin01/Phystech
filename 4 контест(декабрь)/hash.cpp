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
		if (inserted * 4 >= 3*body.size()) {
			
		}
		for (auto h = hash(key); ; h = (h + 1) % body.size()) {
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
		for (auto h = hash(key); ; h = (h + 1) % body.size()) {
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) continue;
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
		for (auto h = hash(key); ; h = (h + 1) % body.size()) {
			if (body[h].tag == item::EMPTY) return false;
			if (body[h].tag == item::DELETED) continue;
			assert(body[h].tag == item::BUSY);
			if (body[h].key == key) return true;
		}
		assert(false);
		return false;
	}
private:
	struct item {
		item(string const& key, int tag = item::EMPTY) : key(key), tag(tag) {};
		string key;
		enum {
			EMPTY,
			BUSY,
			DELETED
		};
		int tag;
	};
	vector<item> body;
	size_t inserted = 0;
	//CRCCoder<unsigned>crc;//типо хэш функция
	size_t hash(string const& key) {
		//return crc.calc(key.c_str()) % body.size();
	}

};
void TableOfPrimeNumber(vector<int> &PrimeNumber) {
	for (int i = 0; i < 350000; ++i) {
		int k = 0;
		for (int j = 2; 2*j <= i; ++j) {
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
int main() {
	//hashtable ht(8);
	vector<int> PrimeNumber;
	TableOfPrimeNumber(PrimeNumber);
	/*
	ht.insert('abra');
	ht.insert('shvabra');
	bool ok = ht.find('abra');
	assert(ok);*/
	for (int i = 0; i < PrimeNumber.size(); ++i) {
		cout << PrimeNumber[i] << ' ';
	}
}