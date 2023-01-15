#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iterator> // for std::random_access_iterator_tag
# include <cstddef>

namespace ft
{
	/**
	 * ITERATOR_TRAITS
	 */
	template <class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	/**
	 * RANDOM ACCESS ITERATOR
	 */
	template <typename It>
	class RandomAccessIterator
	{
		// MEMBER TYPES
	public:
		typedef typename ft::iterator_traits<It*>::value_type		value_type;
		typedef typename ft::iterator_traits<It*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<It*>::pointer			pointer;
		typedef typename ft::iterator_traits<It*>::reference		reference;
		typedef std::random_access_iterator_tag						iterator_category;

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

		difference_type operator-(RandomAccessIterator<It> it) const {
			return _ptr - it._ptr;
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


	/**
	 * REVERSE ITERATOR
	 */
	template <class Iter>
	class reverse_iterator
	{
		// MEMBER TYPES
	public:
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

		// DATA MEMBERS
	private:
		iterator_type _ptr;

		// MEMBER FUNCTIONS
	public:
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type x) { this->_ptr = x; }
		template <class U>
		reverse_iterator(const reverse_iterator<U>& other) { *this = other; }

		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other)
		{
			this->_ptr = other.base();
			return *this;
		}

		iterator_type base() const { return this->_ptr; }
		reference operator*() const { return *(this->_ptr - 1);
		}
		pointer operator->() const { return this->_ptr; }
		reference operator[] (difference_type n) const { return *(this->_ptr - n - 1); }

		reverse_iterator& operator++() { this->_ptr--; return *this; }
		reverse_iterator& operator--() { this->_ptr++; return *this; }
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(this->_ptr - n);
		}
		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(this->_ptr + n);
		}
		reverse_iterator& operator+=(difference_type n) {
			this->_ptr -= n;
			return *this;
		}
		reverse_iterator& operator-=(difference_type n) {
			this->_ptr += n;
			return *this;
		}
	};

	// NON-MEMBER FUNCTIONS
	template <class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
			const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() == rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() != rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() > rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() >= rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() < rhs.base();
	}
	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class Iter>
	reverse_iterator<Iter>
		operator+(typename reverse_iterator<Iter>::difference_type n,
				const reverse_iterator<Iter>& it) {
		return ft::reverse_iterator<Iter>(it.base() - n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
		operator-(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif
