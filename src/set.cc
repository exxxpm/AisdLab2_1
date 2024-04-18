#include <set.h>
#include <iostream>

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

my_set::~my_set() {
	_clear(_root);
	_root = nullptr;
}