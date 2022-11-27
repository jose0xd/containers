#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
  struct input_iterator_tag { };
  struct output_iterator_tag { };
  struct forward_iterator_tag : public input_iterator_tag { };
  struct bidirectional_iterator_tag : public forward_iterator_tag { };
  struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <typename T>
	class RandomAccessIterator
	{
		// MEMBER TYPES
	public:
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T								value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef T*								pointer;
		typedef T&								reference;

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
