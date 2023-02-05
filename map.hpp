#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional> // TODO less is allowed
# include "utility.hpp"
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
        typedef Key key_type;
        typedef T   mapped_type;
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
        key_compare     _comp;
        allocator_type  _alloc;
        //tree ???

    public:
        // MEMBER FUNCTIONS
        //map() {}
        explicit map(const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {} // TODO
        template <class InputIt>
        map(InputIt first, InputIt last,
            const key_compare& comp = key_compare(),
            const allocator_type& alloc = allocator_type()) {} // TODO
        map(const map& other) {} // TODO
        ~map() {}
        map& operator=(const map& other);
        allocator_type get_allocator() const { return _alloc; }

        // Element access
        mapped_type& at(const key_type& key);
        const mapped_type& at(const key_type& key) const;
        mapped_type& operator[](const key_type& key);

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
        bool empty() const;
        size_type size() const;
        size_type max_size() const;

        // Modifiers
        void clear();
        ft::pair<iterator, bool> insert(const value_type& value);
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