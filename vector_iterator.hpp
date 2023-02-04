#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <iterator> // for std::random_access_iterator_tag
# include <cstddef>

namespace ft
{
	template <typename T>
	class vectorIterator
	{
		// MEMBER TYPES
	public:
		typedef std::ptrdiff_t					difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;

		// DATA MEMBERS
	private:
		pointer _ptr;

		// MEMBER FUNCTIONS
	public:
		vectorIterator() {}
		vectorIterator(pointer ptr) { this->_ptr = ptr; }
		vectorIterator(const vectorIterator& other) { this->_ptr = other._ptr; }
		~vectorIterator() {}

		vectorIterator& operator=(const vectorIterator& other)
		{
			this->_ptr = other._ptr;
			return *this;
		}

 		// const conversion
 		operator vectorIterator<const T>() const { return vectorIterator<const T>(_ptr); }

		reference operator*() const { return *this->_ptr; }
		pointer operator->() const { return this->_ptr; }
		reference operator[](difference_type c) const { return *(this->_ptr + c); }

		vectorIterator& operator++() {this->_ptr++; return *this; }
		vectorIterator operator++(int) {
			vectorIterator tmp(*this);
			this->_ptr++;
			return tmp;
		}
		vectorIterator& operator+=(difference_type c) { this->_ptr += c; return *this; }
		vectorIterator operator+(difference_type c) const {
			return vectorIterator(this->_ptr + c);
		}
		friend vectorIterator operator+(difference_type c, vectorIterator it) {
			return vectorIterator(c + it._ptr);
		}

		vectorIterator& operator--() {this->_ptr--; return *this; }
		vectorIterator operator--(int) {
			vectorIterator tmp(*this);
			this->_ptr--;
			return tmp;
		}
		vectorIterator& operator-=(difference_type c) { this->_ptr -= c; return *this; }
		vectorIterator operator-(difference_type c) const {
			return vectorIterator(this->_ptr - c);
		}

		// NON-MEMBER FUNCTIONS
		friend difference_type operator-(const vectorIterator& left, const vectorIterator& right) {
			return left._ptr - right._ptr;
		}

		friend bool operator==(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) == &(*r);
		}
		friend bool operator!=(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) != &(*r);
		}
		friend bool operator<(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) < &(*r);
		}
		friend bool operator<=(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) <= &(*r);
		}
		friend bool operator>(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) > &(*r);
		}
		friend bool operator>=(const vectorIterator& l, const vectorIterator& r) {
			return &(*l) >= &(*r);
		}
	};


	template <class Iter>
	class reverse_iterator
	{
		// MEMBER TYPES
	public:
		typedef Iter								iterator_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;

		// DATA MEMBERS
	private:
		iterator_type _iter;

		// MEMBER FUNCTIONS
	public:
		reverse_iterator() {}
		explicit reverse_iterator(iterator_type x) { this->_iter = x; }
		template <class U>
		reverse_iterator(const reverse_iterator<U>& other) { *this = other; }

		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other)
		{
			this->_iter = other.base();
			return *this;
		}

		iterator_type base() const { return this->_iter; }
		reference operator*() const { return *(this->_iter - 1);
		}
		pointer operator->() const { return &(*(this->_iter - 1)); }
		reference operator[] (difference_type n) const { return *(this->_iter - n - 1); }

		reverse_iterator& operator++() { this->_iter--; return *this; }
		reverse_iterator& operator--() { this->_iter++; return *this; }
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);
			this->_iter--;
			return tmp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			this->_iter++;
			return tmp;
		}
		reverse_iterator operator+(difference_type n) const {
			return reverse_iterator(this->_iter - n);
		}
		reverse_iterator operator-(difference_type n) const {
			return reverse_iterator(this->_iter + n);
		}
		reverse_iterator& operator+=(difference_type n) {
			this->_iter -= n;
			return *this;
		}
		reverse_iterator& operator-=(difference_type n) {
			this->_iter += n;
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
		return reverse_iterator<Iter>(it.base() - n);
	}
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
		operator-(const reverse_iterator<Iterator1>& lhs,
				const reverse_iterator<Iterator2>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif