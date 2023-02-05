#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iterator> // for std::bidirectional_iterator_tag
# include <cstddef>

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
			while (tmp_parent && tmp == parent.right) {
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
			while (tmp_parent && tmp == parent.left) {
				tmp = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			return tmp_parent;
		}
	};

	template <typename T>
	class mapIterator
	{
		// MEMBER TYPES
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef struct node<T>					node_type;
		typedef node_type*						node_pointer;

		// DATA MEMBERS
	private:
		node_pointer _ptr;

		// MEMBER FUNCTIONS
	public:
		mapIterator() {}
		mapIterator(pointer ptr) { this->_ptr = ptr; }
		mapIterator(const mapIterator& other) { this->_ptr = other._ptr; }
		~mapIterator() {}

		mapIterator& operator=(const mapIterator& other)
		{
			this->_ptr = other._ptr;
			return *this;
		}

 		// const conversion
 		operator mapIterator<const T>() const { return mapIterator<const T>(_ptr); }

		reference operator*() const { return _ptr->value; }
		pointer operator->() const { return &(_ptr->value); }

		mapIterator& operator++() {_ptr = _ptr->next(); return *this; }
		mapIterator operator++(int) {
			mapIterator tmp(*this);
			_ptr = _ptr->next();
			return tmp;
		}

		mapIterator& operator--() {_ptr = _ptr->prev(); return *this; }
		mapIterator operator--(int) {
			mapIterator tmp(*this);
			_ptr = _ptr->prev();
			return tmp;
		}

		// NON-MEMBER FUNCTIONS
		friend bool operator==(const mapIterator& l, const mapIterator& r) {
			return &(*l) == &(*r);
		}
		friend bool operator!=(const mapIterator& l, const mapIterator& r) {
			return &(*l) != &(*r);
		}
	};
}

#endif