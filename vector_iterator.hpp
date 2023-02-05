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
}

#endif