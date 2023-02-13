#ifndef RBTNODE_HPP
# define RBTNODE_HPP

namespace ft
{
	enum Color {
		BLACK = 0,
		RED = 1
	};

	template <typename T>
	struct rbtNode
	{
		T		value;
		rbtNode	*parent;
		rbtNode	*left;
		rbtNode	*right;
		bool	color;

		rbtNode(T val = T(), bool col = BLACK)
			: value(val), parent(NULL), left(NULL), right(NULL), color(col) {}
		rbtNode(const rbtNode& other) { *this = other; }
		~rbtNode() {}

		rbtNode& operator=(const rbtNode& other) {
			value = other.value;
			parent = other.parent;
			left = other.left;
			right = other.right;
			color = other.color;

			return *this;
		}

		static rbtNode *minimum(rbtNode *n) {
			if (!n)
				return NULL;
			while (n->left)
				n = n->left;
			return n;
		}
		static rbtNode *maximum(rbtNode *n) {
			if (!n)
				return NULL;
			while (n->right)
				n = n->right;
			return n;
		}

		rbtNode *next() {
			rbtNode *tmp = this;
			if (tmp->right)
				return minimum(tmp->right);

			rbtNode *possible_last = tmp->right;
			rbtNode *tmp_parent = tmp->parent;
			while (tmp_parent && tmp == tmp_parent->right) {
				tmp = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return tmp_parent ? tmp_parent : possible_last;
		}
		rbtNode *prev() {
			rbtNode *tmp = this;
			if (tmp->left)
				return maximum(tmp->left);

			rbtNode *tmp_parent = tmp->parent;
			while (tmp_parent && tmp == tmp_parent->left) {
				tmp = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return tmp_parent;
		}
	};
}

#endif