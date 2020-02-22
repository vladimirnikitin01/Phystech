/*Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N. Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве. Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
Равные ключи добавляйте в правое поддерево. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.
Разница может быть отрицательна.
*/
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
template<typename T, class C>
class decartach {
private:
	struct node {
		T value;
		T prior;
		node* NewElement = nullptr;
		node* left = nullptr;
		node* right = nullptr;
		node* current;
		explicit node(T const& value, T& prior) :value(value), prior(prior) {}
		void print(int level, std::vector <int>& width, int& MaxWidth) {
			if (width.size() < level + 1) {
				width.push_back(0);
			}
			if (this == nullptr) return;
			right->print(level + 1, width, MaxWidth);
			width[level] += 1;
			if (width[level] > MaxWidth) {
				MaxWidth = width[level];
			}
			left->print(level + 1, width, MaxWidth);
		}
		~node() {
			if (this != nullptr) {
				delete this->NewElement;
			}
		}
	};
	node* root = nullptr;
	C comp;
public:
	decartach(C comp) : comp(comp) {}
	~decartach() {
		std::queue <node* > del;
		del.push(root);
		while (del.size() != 0) {
			auto current = del.front();
			del.pop();
			if (current->left != nullptr) {
				del.push(current->left);
			}
			if (current->right != nullptr) {
				del.push(current->right);
			}
			delete current;
		}
	}
	bool empty() const {
		return root == nullptr;
	}
	int print1() {
		std::vector<int> width(1);
		int MaxWidth = 0;
		root->print(0, width, MaxWidth);
		return MaxWidth;
	}
	struct UnderTree {
		node* T1;
		node* T2;
	};
	UnderTree split(node*& current, T key) {
		UnderTree ut;
		if (current == nullptr) {
			ut.T1 = nullptr;
			ut.T2 = nullptr;
			return(ut);
		}
		else if (key >= current->value) {
			ut = split(current->right, key);
			current->right = ut.T1;
			ut.T1 = current;
			return(ut);
		}
		else {
			ut = split(current->left, key);
			current->left = ut.T2;
			ut.T2 = current;
			return(ut);
		}
	}
	bool insert(node*& current, node* NewElement) {
		if (root == nullptr) {
			root = NewElement;
			return true;
		}
		else if (current == nullptr) {
			current = NewElement;
			return true;
		}
		if (NewElement->prior <= current->prior) {
			if (NewElement->value >= current->value) {
				insert(current->right, NewElement);
			}
			else {
				insert(current->left, NewElement);
			}
			return true;
		}
		else {
			auto current1 = current;
			UnderTree ut = split(current, NewElement->value);
			current = NewElement;
			current->left = ut.T1;
			current->right = ut.T2;
			return true;
		}
	}
	bool insert1(T const& value, T& prior) {
		node* NewElement = new node(value, prior);
		insert(root, NewElement);
		return true;
	}
};


template<typename T, class C>
class BST {
public:
	BST(C comp) : comp(comp) {}
	~BST() {
		std::queue <node* > del;
		del.push(root);
		while (del.size() != 0) {
			auto current = del.front();
			del.pop();
			if (current->left != nullptr) {
				del.push(current->left);
			}
			if (current->right != nullptr) {
				del.push(current->right);
			}
			delete current;
		}
	}
	bool empty() const {
		return root == nullptr;
	}
	int print1() {
		std::vector<int> width(1);
		int MaxWidth = 0;
		root->print(width, MaxWidth);
		return MaxWidth;
	}
	bool insert(T const& value) {
		if (empty()) {
			root = new node(value, 0);
			return true;
		}
		auto current = root;
		auto parent = root;
		bool isleft = true;
		while (current != nullptr) {
			parent = current;
			int height = parent->height;
			if (comp(value, current->value)) {
				current = current->left;
				isleft = true;
			}
			else if (comp(current->value, value)) {
				current = current->right;
				isleft = false;
			}
			else {
				return false;
			}
		}
		if (isleft) {
			parent->left = new node(value, parent->height + 1);
		}
		else {
			parent->right = new node(value, parent->height + 1);
		}
		return true;
	}
private:
	struct node {
		T value;
		int height = 0;
		node* left = nullptr;
		node* right = nullptr;
		explicit node(T const& value, int height) :value(value), height(height) {}
		~node() {
		}
		void print(std::vector <int>& width, int& MaxWidth) {
			std::queue <node* > q;
			q.push(this);
			while (q.size() != 0) {
				auto current = q.front();
				if (width.size() < (current->height) + 1) {
					width.push_back(0);
				}
				width[current->height] += 1;
				if (width[current->height] > MaxWidth) {
					MaxWidth = width[current->height];
				}
				q.pop();
				if (current->left != nullptr) {
					q.push(current->left);
				}
				if (current->right != nullptr) {
					q.push(current->right);
				}
			}
		}
	} *root = nullptr;
	C comp;
};
class int_comparer {
public:
	bool operator()(int x, int y) {
		return x < y;
	}
};
int main() {
	int_comparer icomp;
	int_comparer compForBST;
	decartach<int, int_comparer> tree(icomp);
	BST<int, int_comparer> tree2(compForBST);
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int b, y;
		std::cin >> b >> y;
		tree.insert1(b, y);
		tree2.insert(b);
	}
	std::cout << (tree.print1() - tree2.print1());
}
