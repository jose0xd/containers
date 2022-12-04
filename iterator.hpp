#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	// Tags of iterator type
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// ITERATOR_TRAITS
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	}

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	}

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	}

	// RANDOM ACCESS ITERATOR
	template <typename It>
	class RandomAccessIterator
	{
		// MEMBER TYPES
	public:
		typedef typename ft::iterator_traits<It*>::value_type		value_type;
		typedef typename ft::iterator_traits<It*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<It*>::pointer			pointer;
		typedef typename ft::iterator_traits<It*>::reference		reference;
		typedef ft::random_access_iterator_tag						iterator_category;

		// DATA MEMBERS
	private:
		pointer _ptr;

		// MEMBER FUNCTIONS
	public:
		RandomAccessIterator() {}
		RandomAccessIterator(pointer ptr) { this->_ptr = ptr; }
		RandomAccessIterator(const RandomAccessIterator& other) { this->_ptr = other._ptr; }
		~RandomAccessIterator() {}

		RandomAccessIterator& operator=(const RandomAccessIterator& other)
		{
			this->_ptr = other._ptr;
			return *this;
		}

		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return this->_ptr; }
		reference operator[](difference_type c) const { return *(this->_ptr + c); }

		RandomAccessIterator& operator++() {this->_ptr++; return *this; }
		RandomAccessIterator operator++(int) {
			RandomAccessIterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		RandomAccessIterator& operator+=(difference_type c) { this->_ptr += c; return *this; }
		RandomAccessIterator operator+(difference_type c) const {
			return RandomAccessIterator(this->_ptr + c);
		}
		RandomAccessIterator& operator--() {this->_ptr--; return *this; }
		RandomAccessIterator operator--(int) {
			RandomAccessIterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		RandomAccessIterator& operator-=(difference_type c) { this->_ptr -= c; return *this; }
		RandomAccessIterator operator-(difference_type c) const {
			return RandomAccessIterator(this->_ptr - c);
		}

		// NON-MEMBER FUNCTIONS
		friend bool operator==(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l == *r;
		}
		friend bool operator!=(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l != *r;
		}
		friend bool operator<(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l < *r;
		}
		friend bool operator<=(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l <= *r;
		}
		friend bool operator>(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l > *r;
		}
		friend bool operator>=(const RandomAccessIterator& l, const RandomAccessIterator& r) {
			return *l >= *r;
		}
	};
}

#endif
