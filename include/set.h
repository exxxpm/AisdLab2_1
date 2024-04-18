struct node {
	int data;
	node* left;
	node* right;
	node(int val, node* left, node* right);
};
class my_set {
	node* _root;

	void _clear(node* root);
public:
	my_set();
	my_set(const int val);

	int get_root_value() const;

	~my_set();
};