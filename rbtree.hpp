#ifndef RBTREE_HPP
# define RBTREE_HPP

namespace ft
{
	template <typename T>
	struct node
	{
		T		value;
		node	*parent;
		node	*left;
		node	*right;

		node(T val = T()) : value(val), parent(NULL), left(NULL), right(NULL) {}
		node(const node& other) { *this = other; }
		~node() {}

		node& operator=(const node& other) {
			value = other.value;
			parent = other.parent;
			left = other.left;
			right = other.right;
		}

		node *minimum(node *n) {
			if (!n)
				return NULL;
			while (n->left)
				n = n->left;
			return n;
		}
		node *maximum(node *n) {
			if (!n)
				return NULL;
			while (n->right)
				n = n->right;
			return n;
		}

		node *next() {
			node *tmp = this;
			if (tmp->right)
				return minimun(tmp->right);

			node *tmp_parent = tmp->parent;
			while (tmp_parent && tmp == tmp_parent->right) {
				tmp = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return tmp_parent;
		}
		node *prev() {
			node *tmp = this;
			if (tmp->left)
				return maximum(tmp->left);

			node *tmp_parent = tmp->parent;
			while (tmp_parent && tmp == tmp_parent->left) {
				tmp = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return tmp_parent;
		}
	};

	template <typename T, typename Compare>
	class rbtree
	{
	public:
		typedef T				value_type;
		typedef struct node<T>	node_type;
		typedef node_type*		node_pointer;
	};
}

#endif