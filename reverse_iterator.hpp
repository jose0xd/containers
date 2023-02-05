#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft
{
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