#ifndef MAP_HPP
# define MAP_HPP

// TODO
#include <iostream>
#include <deque>
////
//#include <limits>

# include <memory>
# include <functional>
# include <stdexcept>
# include "utility.hpp"
# include "algorithm.hpp"
# include "rbtNode.hpp"
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        // MEMBER TYPES
        typedef Key                                     key_type;
        typedef T                                       mapped_type;
        typedef ft::pair<const Key, T>                  value_type;
        typedef std::size_t                             size_type;
        typedef std::ptrdiff_t                          difference_type;
        typedef Compare                                 key_compare;
        typedef Allocator                               allocator_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_reference;
        typedef typename Allocator::pointer             pointer;
        typedef typename Allocator::const_pointer       const_pointer;
        typedef ft::mapIterator<value_type>             iterator;
        typedef ft::mapIterator<const value_type>       const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

        // MEMBER CLASSES
        class value_compare
        {
            friend class map;
        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {}

        public:
            typedef bool        result_type;
            typedef value_type  first_argument_type;
            typedef value_type  second_argument_type;
            result_type operator()(const value_type& lhs, const value_type& rhs) const {
                return comp(lhs.first, rhs.first);
            }
        };

    private:
		typedef rbtNode<value_type>						                tree_node;
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
        //map() {}
        explicit map(const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
            _end = _alloc.allocate(1);
            _alloc.construct(_end, value_type());
            _end->parent = _root;
        }

        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
            _end = _alloc.allocate(1);
            _alloc.construct(_end, value_type());
            _end->parent = _root;
            insert(first, last);
        }

        map(const map& other) : _root(NULL), _comp(other._comp), _alloc(other._alloc), _size(0) {
            _end = _alloc.allocate(1);
            _alloc.construct(_end, value_type());
            _end->parent = _root;
            insert(other.begin(), other.end());
        }

        ~map() {
            if (_size)
                clear();
            _alloc.destroy(_end);
            _alloc.deallocate(_end, 1);
        }

        map& operator=(const map& other) {
            _root = NULL;
            _comp = other._comp;
            _alloc = other._alloc;
            _size = 0;
            insert(other.begin(), other.end());
            return *this;
        }

        allocator_type get_allocator() const { return _alloc; }

        // Element access
        mapped_type& at(const key_type& key) {
            tree_node *node = _root;
            while (node) {
                if (!_comp(node->value.first, key) && !_comp(key, node->value.first))
                    return node->value.second;
                if (_comp(key, node->value.first))
                    node = node->left;
                else
                    node = node->right;
            }
            throw std::out_of_range("map::at : key does not exist");
        }
        const mapped_type& at(const key_type& key) const {
            tree_node *node = _root;
            while (node) {
                if (!_comp(node->value.first, key) && !_comp(key, node->value.first))
                    return node->value.second;
                if (_comp(key, node->value.first))
                    node = node->left;
                else
                    node = node->right;
            }
            throw std::out_of_range("map::at : key does not exist");
        }
        mapped_type& operator[](const key_type& key) {
            return (*(insert(ft::make_pair(key, mapped_type())).first)).second;
        }

        // Iterators
        iterator begin() { return iterator(rbtNode<value_type>::minimum(_root)); }
        const_iterator begin() const {
            return const_iterator((const_tree_node*)rbtNode<value_type>::minimum(_root));
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
                if (!_comp(value.first, tmp->value.first) && !_comp(tmp->value.first, value.first))
                    return ft::make_pair(iterator(tmp), false);

				parent = tmp;
				if (_comp(value.first, tmp->value.first))
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
				if (_comp(new_node->value.first, parent->value.first))
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
            erase(pos->first);
            return last;
        }

        iterator erase(iterator first, iterator last) {
            while (first != last) {
                key_type key = first->first;
                first++;
                erase(key);
            }
            return last;
        }

        size_type erase(const key_type& key) {
            tree_node *tmp;
            tree_node *pos = search(key); // TODO rename pos
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

        void swap(map& other) {
			swapAny(_root, other._root);
			swapAny(_comp, other._comp);
			swapAny(_alloc, other._alloc);
			swapAny(_size, other._size);
			swapAny(_end, other._end);
		}

        // Lookup
        size_type count(const key_type& key) const {
			tree_node *node = _root;
			while (node && key != node->value.first) {
				if (_comp(key, node->value.first))
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
			tree_node *node = _root;
			while (node && key != node->value.first) {
				if (_comp(key, node->value.first)) {
                    if (node->left)
                        node = node->left;
                    else
                        break;
                }
				else {
                    if (node->right)
                        node = node->right;
                    else
                        break;
                }
			}
            if (node)
                return iterator(node);
            return iterator(_end);
        }
        const_iterator lower_bound(const key_type& key) const {
			tree_node *node = _root;
			while (node && key != node->value.first) {
				if (_comp(key, node->value.first)) {
                    if (node->left)
                        node = node->left;
                    else
                        break;
                }
				else {
                    if (node->right)
                        node = node->right;
                    else
                        break;
                }
			}
            if (node)
                return const_iterator((const_tree_node*)node);
            return const_iterator((const_tree_node*)_end);
        }
        iterator upper_bound(const key_type& key) {
            iterator it = lower_bound(key);
            if (it != _end && !_comp(it->first, key) && !_comp(key, it->first))
                ++it;
            return it;
        }
        const_iterator upper_bound(const key_type& key) const {
            const_iterator it = lower_bound(key);
            const_tree_node *the_end = (const_tree_node*)_end;
            if (it != the_end && !_comp(it->first, key) && !_comp(key, it->first))
                ++it;
            return it;
        }

        // Observers
        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return value_compare(_comp); }

        // TODO: Remove
        void print() const {
            std::deque<tree_node*> queue;
            queue.push_back(_root);

            while (!queue.empty()) {
                tree_node *node = queue.front();
                std::cout << node->value.first << " | " << node->value.second
                    << " c: " << node->color << std::endl;
                if (node->left) queue.push_back(node->left);
                if (node->right) queue.push_back(node->right);
                queue.pop_front();
            }
            std::cout << std::endl;
        }

    private:
		template <class Type>
		void swapAny(Type& a, Type& b) {
			Type tmp(a);
			a = b;
			b = tmp;
		}

        tree_node *search(const key_type& key) const {
			tree_node *node = _root;
			while (node && key != node->value.first) {
				if (_comp(key, node->value.first))
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
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) {
        if (lhs.size() != rhs.size())
            return false;

        typename ft::map<Key, T, Compare, Alloc>::const_iterator lhs_iter = lhs.begin();
        typename ft::map<Key, T, Compare, Alloc>::const_iterator rhs_iter = rhs.begin();
        while (lhs_iter != lhs.end()) {
            if (lhs_iter->first != rhs_iter->first || lhs_iter->second != rhs_iter->second)
                return false;
            lhs_iter++;
            rhs_iter++;
        }
        return true;
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) { return !(rhs < lhs); }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) { return rhs < lhs; }
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs) { return !(lhs < rhs); }
}

#endif