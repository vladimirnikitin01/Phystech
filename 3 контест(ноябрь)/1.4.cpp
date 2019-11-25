/*Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево поиска, заданное наивным порядком вставки. Т.е.,
при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Выведите элементы в порядке level-order (по слоям, “в ширину”).*/
#include <iostream>
#include <queue>
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
	bool insert(T const& value) {
		if (empty()) {
			root = new node(value);
			return true;
		}
		auto current = root;
		auto parent = root;
		bool isleft = true;
		while (current != nullptr) {
			parent = current;
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
		if (isleft) parent->left = new node(value);
		else parent->right = new node(value);
		return true;
	}
	void print2() {
		std::queue <node* > q;
		q.push(root);
		while (q.size() != 0) {
			node* current = q.front();
			std::cout << current->value << ' ';
			q.pop();
			if (current->left != nullptr) {
				q.push(current->left);
			}
			if (current->right != nullptr) {
				q.push(current->right);
			}
		}
	}
private:
	struct node {
		T value;
		node* left = nullptr;
		node* right = nullptr;
		explicit node(T const& value) :value(value) {}
		~node() {
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
	BST<int, int_comparer> tree(icomp);
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int b;
		std::cin >> b;
		tree.insert(b);
	}
	tree.print2();

}
