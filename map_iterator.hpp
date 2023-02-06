#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iterator> // for std::bidirectional_iterator_tag
# include <cstddef>
# include "rbtree.hpp"

namespace ft
{
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