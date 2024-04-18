#include <set.h>
#include <iostream>
#include <queue>

node::node(int val, node* left, node* right) : data(val), left(left), right(right) {};

my_set::my_set() : _root(nullptr) {};

my_set::my_set(const int val) : _root(new node(val, nullptr, nullptr)) {};

my_set::my_set(std::initializer_list<int> values) {
	_root = nullptr;
	for (auto val : values) insert(val);
}

node* my_set::_copy(node* root) {
	if (!root) return nullptr;
	node* new_node = new node(root->data, root->left, root->right);
	new_node->left = _copy(root->left);
	new_node->right = _copy(root->right);
	return new_node;
}

my_set& my_set::operator=(my_set other) {
	swap(other);
	return *this;
}

void my_set::swap(my_set& other) noexcept {
	std::swap(_root, other._root);
}

my_set::my_set(const my_set& other) {
	_root = _copy(other._root);
}

void my_set::_clear(node* root) {
	if (!root) return;
	_clear(root->left);
	_clear(root->right);
	delete root;
}

bool my_set::_equal(const node* first, const node* second) const {
	if (!first && !second) return true;
	if (first && second) {
		return first->data == second->data && _equal(first->left, second->left) && _equal(first->right, second->right);
	}
	return false;
}

bool my_set::equal(const my_set& second) const {
	return _equal(_root, second._root);
}

bool my_set::operator==(const my_set& second) {
	return equal(second);
}


bool my_set::operator!=(const my_set& second) {
	return !(*this == second);
}

int my_set::get_root_value() const {
	return _root ? _root->data : throw std::logic_error("root is nullptr");
}

bool my_set::contains(const int key) const {
	node* tmp = _root;
	while (tmp) {
		if (tmp->data == key) return true;
		if (tmp->data > key) {
			tmp = tmp->left;
		}
		else tmp = tmp->right;
	}
	return false;
}

bool my_set::insert(const int key) {
	auto new_node = new node(key, nullptr, nullptr);
	if (!_root) {
		_root = new_node;
		return true;
	}
	node* tmp = _root;
	while (tmp) {
		if (tmp->data == key) return false;
		if (tmp->data > key) {
			if (!tmp->left) {
				tmp->left = new_node;
				return true;
			}
			tmp = tmp->left;
		}
		else {
			if (!tmp->right) {
				tmp->right = new_node;
				return true;
			}
			tmp = tmp->right;
		}
	}
	return false;
}

bool my_set::erase(const int key) {
	return _erase(_root, key);
}

bool my_set::_erase(node*& node_, const int key) {
	if (!node_) {
		return false;
	}
	if (key < node_->data) {
		return _erase(node_->left, key);
	}
	else if (key > node_->data) {
		return _erase(node_->right, key);
	}
	else {
		if (!node_->left) {
			auto tmp = node_->right;
			delete node_;
			node_ = tmp;
			return true;
		}
		else if (!node_->right) {
			auto tmp = node_->left;
			delete node_;
			node_ = tmp;
			return true;
		}
		auto min_right = node_->right;
		while (min_right->left) {
			min_right = min_right->left;
		}
		node_->data = min_right->data;
		return _erase(node_->right, min_right->data);
	}
}

void my_set::_print(const node* root) const {
	if (!root) return;
	std::cout << root->data << " ";
	_print(root->left);
	_print(root->right);
}

void my_set::print() const {
	_print(_root);
}

node* my_set::get_root() const {
	return _root;
}

my_set::~my_set() {
	_clear(_root);
	_root = nullptr;
}

my_set union_of_sets(const my_set& first, const my_set& second) {
	my_set result;
	if (!first.get_root()) {
		result = second;
		return result;
	}
	if (!second.get_root()) {
		result = first;
		return result;
	}
	std::queue<node*> queue1;
	queue1.push(first.get_root());
	queue1.push(second.get_root());
	while (!queue1.empty()) {
		auto current = queue1.front();
		result.insert(current->data);
		if (current->left) queue1.push(current->left);
		if (current->right)queue1.push(current->right);
		queue1.pop();
	}
	return result;
}

my_set symmetrical_difference(const my_set& first, const my_set& second) {
	my_set result;
	if (!first.get_root()) {
		result = second;
		return result;
	}
	if (!second.get_root()) {
		result = first;
		return result;
	}
	std::queue<node*> queue;;
	queue.push(first.get_root());
	queue.push(second.get_root());
	while (!queue.empty()) {
		auto current = queue.front();
		if (second.contains(current->data) && first.contains(current->data)) {
			if (current->left) queue.push(current->left);
			if (current->right)queue.push(current->right);
			queue.pop();
		}
		else result.insert(current->data);
		if (current->left) queue.push(current->left);
		if (current->right)queue.push(current->right);
		queue.pop();
	}
	return result;
}