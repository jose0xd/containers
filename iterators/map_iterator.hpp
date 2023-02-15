#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iterator> // for std::bidirectional_iterator_tag
# include <cstddef>  // for std::ptrdiff_t
# include "../utils/rbtNode.hpp"
# include "../utils/type_traits.hpp"

namespace ft
{
	template <typename T>
	class mapIterator
	{
		// MEMBER TYPES
	public:
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef std::bidirectional_iterator_tag						iterator_category;

		// DATA MEMBERS
	private:
		typedef struct rbtNode<T>	node_type;
		typedef node_type*			node_pointer;

		node_pointer _ptr;

		// MEMBER FUNCTIONS
	public:
		mapIterator() {}
		mapIterator(node_pointer ptr) { this->_ptr = ptr; }
		mapIterator(const mapIterator& other) { this->_ptr = other._ptr; }
		~mapIterator() {}

		mapIterator& operator=(const mapIterator& other)
		{
			this->_ptr = other._ptr;
			return *this;
		}

		// const conversion
		operator mapIterator<const T>() const {
			struct rbtNode<const T> *ptr = (struct rbtNode<const T>*) _ptr;
			return mapIterator<const T>(ptr);
		}

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