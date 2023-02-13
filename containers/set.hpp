#ifndef SET_HPP
# define SET_HPP

// For print the red black tree
# if DEBUG
#  include <iostream>
#  include <deque>
# endif

# include <memory>
# include <functional>
# include <stdexcept>
# include "../iterators/map_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"
# include "../utils/algorithm.hpp"
# include "../utils/rbtNode.hpp"
# include "../utils/utility.hpp"

namespace ft
{
	template <class Key, class Compare = std::less<Key>,
		class Allocator = std::allocator<Key> >
	class set
	{
	public:
		// MEMBER TYPES
		typedef Key                                     key_type;
		typedef Key                                     value_type;
		typedef std::size_t                             size_type;
		typedef std::ptrdiff_t                          difference_type;
		typedef Compare                                 key_compare;
		typedef Compare                                 value_compare;
		typedef Allocator                               allocator_type;
		typedef value_type&                             reference;
		typedef const value_type&                       const_reference;
		typedef typename Allocator::pointer             pointer;
		typedef typename Allocator::const_pointer       const_pointer;
		typedef ft::mapIterator<const value_type>       iterator;
		typedef ft::mapIterator<const value_type>       const_iterator;
		typedef ft::reverse_iterator<iterator>          reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

	private:
		typedef rbtNode<const value_type>						                tree_node;
		typedef rbtNode<const value_type>						        const_tree_node;
		typedef typename Allocator::template rebind<tree_node>::other   node_alloc;

		tree_node		*_root;
		key_compare		_comp;
		node_alloc      _alloc;
		size_type       _size;
		tree_node       *_end;
		// TODO: add _begin to return it in constant time

	public:
		// MEMBER FUNCTIONS
		//set() {}
		explicit set(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			_end->parent = _root;
		}

		template <class InputIt>
		set(InputIt first, InputIt last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type())
			: _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			_end->parent = _root;
			insert(first, last);
		}

		set(const set& other) : _root(NULL), _comp(other._comp), _alloc(other._alloc), _size(0) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, value_type());
			_end->parent = _root;
			insert(other.begin(), other.end());
		}

		~set() {
			if (_size)
				clear();
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		}

		set& operator=(const set& other) {
			_root = NULL;
			_comp = other._comp;
			_alloc = other._alloc;
			_size = 0;
			insert(other.begin(), other.end());
			return *this;
		}

		allocator_type get_allocator() const { return _alloc; }

		// Iterators
		iterator begin() { return iterator(tree_node::minimum(_root)); }
		const_iterator begin() const {
			return const_iterator((const_tree_node*)tree_node::minimum(_root));
		}
		iterator end() {
			tree_node *last = _root->maximum(_root);
			if (last && last != _end) {
				_end->parent = last;
				last->right = _end;
			}
			return iterator(_end);
		}
		const_iterator end() const {
			tree_node *last = _root->maximum(_root);
			if (last && last != _end) {
				_end->parent = last;
				last->right = _end;
			}
			return const_iterator((const_tree_node*)_end);
		}
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// Capacity
		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }

		// Modifiers
		void clear() { erase(begin(), end()); }

		ft::pair<iterator, bool> insert(const value_type& value) {
			tree_node *parent = NULL;
			tree_node *tmp = _root;
			while (tmp && tmp != _end) {
				if (!_comp(value, tmp->value) && !_comp(tmp->value, value))
					return ft::make_pair(iterator(tmp), false);

				parent = tmp;
				if (_comp(value, tmp->value))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}

			tree_node *new_node = _alloc.allocate(1);
			_alloc.construct(new_node, value);
			new_node->color = RED;
			new_node->parent = parent;
			if (!parent)
				_root = new_node;
			else {
				if (_comp(new_node->value, parent->value))
					parent->left = new_node;
				else
					parent->right = new_node;
			}
			insert_fixup(new_node);
			_size++;
			return ft::make_pair(iterator(new_node), true);
		}

		iterator insert(iterator pos, const value_type& value) {
			(void) pos;
			return insert(value).first;
		}

		template <class InputIt>
		void insert(InputIt first, InputIt last) {
			while (first != last) {
				insert(*first);
				first++;
			}
		}

		iterator erase(iterator pos) {
			iterator last = pos;
			last++;
			erase(*pos);
			return last;
		}

		iterator erase(iterator first, iterator last) {
			while (first != last) {
				key_type key = *first;
				first++;
				erase(key);
			}
			return last;
		}

		size_type erase(const key_type& key) {
			tree_node *tmp;
			tree_node *pos = search(key);
			if (pos == _end) { return 0; }
			int original_color = pos->color;

			if (!pos->left) {
				tmp = pos->right;
				transplant(pos, pos->right);
			} else if (!pos->right && pos->right != _end) {
				tmp = pos->left;
				transplant(pos, pos->left);
			} else {
				tree_node *next_node = pos->next();
				original_color = next_node->color;
				tmp = next_node->right;
				if (next_node->parent == pos) {
					if (tmp) { tmp->parent = next_node; }
				} else {
					transplant(next_node, next_node->right);
					next_node->right = pos->right;
					next_node->right->parent = next_node;
				}
				transplant(pos, next_node);
				next_node->left = pos->left;
				next_node->left->parent = next_node;
				next_node->color = pos->color;
			}
			_alloc.destroy(pos);
			_alloc.deallocate(pos, 1);
			if (original_color == BLACK && tmp && tmp != _end)
				delete_fixup(tmp);
			_size--;
			return 1;
		}

		void swap(set& other) {
			swapAny(_root, other._root);
			swapAny(_comp, other._comp);
			swapAny(_alloc, other._alloc);
			swapAny(_size, other._size);
			swapAny(_end, other._end);
		}

		// Lookup
		size_type count(const key_type& key) const {
			tree_node *node = _root;
			while (node && key != node->value) {
				if (_comp(key, node->value))
					node = node->left;
				else
					node = node->right;
			}
			if (node)
				return 1;
			return 0;
		}
		iterator find(const key_type& key) {
			return iterator(search(key));
		}
		const_iterator find(const key_type& key) const {
			return const_iterator((const_tree_node*)search(key));
		}

		ft::pair<iterator, iterator> equal_range(const key_type& key) {
			return make_pair(lower_bound(key), upper_bound(key));
		}
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
			return make_pair(lower_bound(key), upper_bound(key));
		}
		iterator lower_bound(const key_type& key) {
			iterator it = begin();
			for (; it != end(); it++) {
				if (!_comp(*it, key))
					break;
			}
			return it;
		}
		const_iterator lower_bound(const key_type& key) const {
			const_iterator it = begin();
			for (; it != end(); it++) {
				if (!_comp(*it, key))
					break;
			}
			return it;
		}
		iterator upper_bound(const key_type& key) {
			iterator it = lower_bound(key);
			if (it != _end && !_comp(*it, key) && !_comp(key, *it))
				++it;
			return it;
		}
		const_iterator upper_bound(const key_type& key) const {
			const_iterator it = lower_bound(key);
			const_tree_node *the_end = (const_tree_node*)_end;
			if (it != the_end && !_comp(*it, key) && !_comp(key, *it))
				++it;
			return it;
		}

		// Observers
		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return value_compare(_comp); }

# if DEBUG
// For print the red black tree
		void print() const {
			std::deque<tree_node*> queue;
			queue.push_back(_root);

			while (!queue.empty()) {
				tree_node *node = queue.front();
				std::cout << node->value << " | " << node->value
					<< " c: " << node->color << std::endl;
				if (node->left) queue.push_back(node->left);
				if (node->right) queue.push_back(node->right);
				queue.pop_front();
			}
			std::cout << std::endl;
		}
# endif

	private:
		template <class Type>
		void swapAny(Type& a, Type& b) {
			Type tmp(a);
			a = b;
			b = tmp;
		}

		tree_node *search(const key_type& key) const {
			tree_node *node = _root;
			while (node && key != node->value) {
				if (_comp(key, node->value))
					node = node->left;
				else
					node = node->right;
			}
			return node ? node : _end;
		}

		// INSERT HELPERS
		void left_rotate(tree_node *node) {
			tree_node *tmp = node->right;
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				_root = tmp;
			else {
				if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
			}
			tmp->left = node;
			node->parent = tmp;
		}

		void right_rotate(tree_node *node) {
			tree_node *tmp = node->left;
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (!node->parent)
				_root = tmp;
			else {
				if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
			}
			tmp->right = node;
			node->parent = tmp;
		}

		void insert_fixup(tree_node *node) {
			while (node->parent && node->parent->parent && node->parent->color == RED) {
				if (node->parent == node->parent->parent->left) {
					tree_node *uncle = node->parent->parent->right;
					if (uncle && uncle->color == RED) {
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->right) {
							node = node->parent;
							left_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						right_rotate(node->parent->parent);
					}
				} else {
					tree_node *uncle = node->parent->parent->left;
					if (uncle && uncle->color == RED) {
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					} else {
						if (node == node->parent->left) {
							node = node->parent;
							right_rotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						left_rotate(node->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}

		// DELETE HELPERS
		void transplant(tree_node *u, tree_node *v) {
			if (!u->parent)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;

			if (v)
				v->parent = u->parent;
		}

		void delete_fixup(tree_node *node) {
			while (node != _root && node->color == BLACK) {
				if (node == node->parent->left) {
					tree_node *sibling = node->parent->right;
					// type 1
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						left_rotate(node->parent);
						sibling = node->parent->right;
					}
					// type 2
					if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						// type 3
						if (sibling->right->color == BLACK) {
							sibling->left->color = BLACK;
							sibling->color = RED;
							right_rotate(sibling);
							sibling = node->parent->right;
						}
						// type 4
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->right->color = BLACK;
						left_rotate(node->parent);
						node = _root;
					}
				} else {
					tree_node *sibling = node->parent->left;
					// type 1
					if (sibling->color == RED) {
						sibling->color = BLACK;
						node->parent->color = RED;
						left_rotate(node->parent);
						sibling = node->parent->left;
					}
					// type 2
					if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
						sibling->color = RED;
						node = node->parent;
					} else {
						// type 3
						if (sibling->left->color == BLACK) {
							sibling->right->color = BLACK;
							sibling->color = RED;
							right_rotate(sibling);
							sibling = node->parent->left;
						}
						// type 4
						sibling->color = node->parent->color;
						node->parent->color = BLACK;
						sibling->left->color = BLACK;
						left_rotate(node->parent);
						node = _root;
					}
				}
			}
			node->color = BLACK;
		}
	};

	// NON-MEMBER FUNCTIONS
	template <class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;

		typename ft::set<Key, Compare, Alloc>::const_iterator lhs_iter = lhs.begin();
		typename ft::set<Key, Compare, Alloc>::const_iterator rhs_iter = rhs.begin();
		while (lhs_iter != lhs.end()) {
			if (*lhs_iter != *rhs_iter || *lhs_iter != *rhs_iter)
				return false;
			lhs_iter++;
			rhs_iter++;
		}
		return true;
	}
	template <class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) { return !(lhs == rhs); }
	template <class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}
	template <class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) { return !(rhs < lhs); }
	template <class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) { return rhs < lhs; }
	template <class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key, Compare, Alloc>& lhs,
					const ft::set<Key, Compare, Alloc>& rhs) { return !(lhs < rhs); }
}

#endif