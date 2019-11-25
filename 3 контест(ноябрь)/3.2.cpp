/*
Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики.
Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”.
Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).
*/
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include <set>
#include <iostream>
using namespace std;

struct AVLNode {
	AVLNode* left, * right;
	int key;
	int children;
	int height;
	int childrenOfLeft, childrenOfRight;
	~AVLNode() {
		if (left != nullptr) {
			delete left;
		}
		if (right != nullptr) {
			delete right;
		}
	}
	AVLNode(int const& _key) : key(_key) {
		left = right = nullptr;
		height = 1;
		children = 0;
		childrenOfLeft = 0, childrenOfRight = 0;
	}
	void print(int level = 0) const {
		if (this == nullptr) return;
		right->print(level + 1);
		for (int i = 0; i < level; i++) cout << "  ";
		cout << key << ' ' << children << endl;
		left->print(level + 1);
	}
	int getBalanceFactor() const {
		int r = right == nullptr ? 0 : right->height;
		int l = left == nullptr ? 0 : left->height;
		return r - l;
	}
	void fix() {
		int r = right == nullptr ? 0 : right->height;
		int l = left == nullptr ? 0 : left->height;
		height = (r > l ? r : l) + 1;
	}
	void fixCh() {
		int childrenR = right == nullptr ? 0 : right->children;
		int childrenL = left == nullptr ? 0 : left->children;
		if (left != nullptr) {
			childrenOfLeft = 1 + childrenL;
		}
		else {
			childrenOfLeft = 0;
		}
		if (right != nullptr) {
			childrenOfRight = 1 + childrenR;
		}
		else {
			childrenOfRight = 0;
		}
		children = childrenOfRight + childrenOfLeft;
	}
	AVLNode* rotateRight() {
		auto result = left;
		left = result->right;
		result->right = this;
		fix();

		if ((result->left) != nullptr) {
			result->left->fixCh();
		}
		if ((result->right) != nullptr) {
			result->right->fixCh();
		}
		result->fixCh();
		return result;
	}
	AVLNode* rotateLeft() {
		auto result = right;
		right = result->left;
		result->left = this;
		fix();

		result->fix();
		if ((result->left) != nullptr) {
			result->left->fixCh();
		}
		if ((result->right) != nullptr) {
			result->right->fixCh();
		}
		result->fixCh();
		return result;
	}
	void searchK(int k) {
		if (left == nullptr && right == nullptr) {
			cout << key << endl;
		}
		else if (this->childrenOfLeft >= k && (left != nullptr)) {
			left->searchK(k);
		}
		else if (k == this->childrenOfLeft + 1) {
			cout << key << endl;
		}
		else {
			right->searchK(k - 1 - childrenOfLeft);
		}

	}
	AVLNode* balance() {
		fix();
		switch (getBalanceFactor()) {
		case -2:
			if (left->getBalanceFactor() > 0) {
				left = left->rotateLeft();
			}
			return rotateRight();
		case 2:
			if (right->getBalanceFactor() < 0) {
				right = right->rotateRight();
			}
			return rotateLeft();
		default:
			fixCh();
			return this;
		}
	}

	AVLNode* insert(int const& _key) {
		if (_key < key)
			left = left == nullptr ? new AVLNode(_key) : left->insert(_key);
		else
			right = right == nullptr ? new AVLNode(_key) : right->insert(_key);
		return balance();
	}
	AVLNode* findMinimum() {
		return left != nullptr ? left->findMinimum() : this;
	}

	AVLNode* removeMinimum() {
		if (left == nullptr) return right;
		left = left->removeMinimum();
		return balance();
	}

	static AVLNode* remove(AVLNode* p, int const& _key) {
		if (p == nullptr) return nullptr;
		if (_key < p->key) {
			p->left = remove(p->left, _key);
			return p->balance();
		}
		else if (_key > p->key) {
			p->right = remove(p->right, _key);
			return p->balance();
		}
		else {
			AVLNode* l = p->left;
			AVLNode* r = p->right;
			p->right = nullptr;
			p->left = nullptr;
			delete p;
			if (r == nullptr) return l;
			AVLNode* min = r->findMinimum();
			min->right = r->removeMinimum();
			min->left = l;
			return min->balance();
		}
	}
};

struct AVLTree {
	AVLNode* root;
	AVLTree() {
		root = nullptr;
	}
	~AVLTree() {
		delete root;
	}
	void print() const {
		if (root != nullptr) root->print(0);
		cout << endl;
	}

	bool insert(int const& _key) {
		if (root == nullptr) root = new AVLNode(_key);
		else root = root->insert(_key);
		return true;
	}

	bool remove(int const& _key) {
		root = AVLNode::remove(root, _key);
		return true;
	}
	bool searchK(int const& k) {
		root->searchK(k);
		return true;
	}
};

int main() {
	AVLTree t;
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int b, k;
		cin >> b >> k;
		if (b > 0) {
			t.insert(b);
			t.searchK(k + 1);
		}
		else {
			t.remove(-b);
			t.searchK(k + 1);
		}
	}

}