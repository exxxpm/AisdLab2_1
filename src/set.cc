#include <set.h>
#include <iostream>

node::node(int val, node* left, node* right) : data(val), left(left), right(right) {};

my_set::my_set() : _root(nullptr) {};

my_set::my_set(const int val) : _root(new node(val, nullptr, nullptr)) {};

void my_set::_clear(node* root) {
	if (!root) return;
	_clear(root->left);
	_clear(root->right);
	delete root;
}


int my_set::get_root_value() const {
	return _root ? _root->data : throw std::logic_error("root is nullptr");
}

my_set::~my_set() {
	_clear(_root);
	_root = nullptr;
}