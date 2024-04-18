#include <initializer_list>

struct node {
	int data;
	node* left;
	node* right;
	node(int val, node* left, node* right);
};
class my_set {
	node* _root;

	void _clear(node* root);
	node* _copy(node* root);
	bool _equal(const node* first, const node* second) const;
	bool _erase(node*& node_, const int key);
public:
	my_set();
	my_set(const int val);
	my_set(const my_set& other);
	my_set(std::initializer_list<int> values);

	void swap(my_set& other) noexcept;
	my_set& operator=(my_set other);

	int get_root_value() const;
	bool equal(const my_set& second) const;
	bool operator==(const my_set& second);
	bool operator!=(const my_set& second);
	bool contains(const int key) const;
	bool insert(const int key);
	bool erase(const int key);
	
	~my_set();
};