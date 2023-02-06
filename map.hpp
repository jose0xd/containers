#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>

# include <memory>
# include <functional> // TODO less is allowed
# include <stdexcept>
# include "utility.hpp"
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
        typedef ft::mapIterator<T>                      iterator;
        typedef ft::mapIterator<const T>                const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
		typedef rbtNode<value_type>						tree_node;

        // MEMBER CLASSES
        class value_compare
        {
            //friend class map; ???
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
        tree_node		*_root;
        key_compare		_comp;
        allocator_type	_alloc;
        size_type       _size;
        // TODO: add _begin to return it in constant time

    public:
        // MEMBER FUNCTIONS
        //map() {}
        explicit map(const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _root(NULL), _comp(comp), _alloc(alloc), _size(0) {}

        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type())
            : _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
            insert(first, last);
        }

        map(const map& other) : _root(NULL), _comp(other._comp), _alloc(other._alloc), _size(0) {
            insert(other.begin(), other.end());
        }

        ~map() {} // TODO: delete

        map& operator=(const map& other) {
            _root = NULL;
            _comp = other._comp;
            _alloc = other._alloc;
            _size = other._size;
            insert(other.begin(), other.end());
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
        iterator begin();
        const_iterator begin() const;
        iterator end();
        const_iterator end() const;
        reverse_iterator rbegin();
        const_reverse_iterator rbegin() const;
        reverse_iterator rend();
        const_reverse_iterator rend() const;

        // Capacity
        bool empty() const { return _size == 0; }
        size_type size() const { return _size; }
        size_type max_size() const { return _alloc.max_size(); }

        // Modifiers
        void clear();
        // ft::pair<iterator, bool> insert(const value_type& value);
        ///////
		tree_node *insert(value_type value) {
			tree_node *new_node = new tree_node(value, RED);
			tree_node *parent = NULL;
			tree_node *tmp = _root;
			while (tmp) {
				parent = tmp;
				if (_comp(value.first, tmp->value.first))
					tmp = tmp->left;
				else
					tmp = tmp->right;
			}
			new_node->parent = parent;
			if (!parent)
				_root = new_node;
			else {
				if (_comp(new_node->value.first, parent->value.first))
					parent->left = new_node;
				else
					parent->right = new_node;
			}
			return new_node;
		}
        ////////
        iterator insert(iterator pos, const value_type& value);
        template <class InputIt>
        void insert(InputIt first, InputIt last);
        iterator erase(iterator pos);
        iterator erase(iterator first, iterator last);
        size_type erase(const key_type& key);
        void swap(map& other);

        // Lookup
        size_type count(const key_type& key) const;
        iterator find(const key_type& key);
        const_iterator find(const key_type& key) const;
        ft::pair<iterator, iterator> equal_range(const key_type& key);
        ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const;
        iterator lower_bound(const key_type& key);
        const_iterator lower_bound(const key_type& key) const;
        iterator upper_bound(const key_type& key);
        const_iterator upper_bound(const key_type& key) const;

        // Observers
        key_compare key_comp() const { return _comp; }
        value_compare value_comp() const { return value_compare(_comp); }
    };

    // NON-MEMBER FUNCTIONS
    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs,
                    const ft::map<Key, T, Compare, Alloc>& rhs);
}

#endif