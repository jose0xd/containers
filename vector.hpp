#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		// MEMBER TYPES
	public:
		typedef T												value_type;
		typedef Allocator										allocator_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef value_type*										pointer;
		typedef const value_type*								const_pointer;
		typedef RandomAccessIterator<value_type>				iterator;
		typedef RandomAccessIterator<const value_type>			const_iterator;
		typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// DATA MEMBERS
	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_data;

		// MEMBER FUNCTIONS
	public:
		//vector();

		explicit vector(const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0), _data(nullptr) {}

		explicit vector(size_type count,
				const value_type& value = value_type(),
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], value);
		}

		template <class InputIt>
		vector(InputIt first, InputIt last,
				const allocator_type& alloc = allocator_type())
			: _alloc(alloc)
		{
			_size = _capacity = last - first;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; first < last; first++, i++)
				_alloc.construct(&_data[i], *first);
		}

		vector(const vector& other)
			: _alloc(other._alloc), _size(other._size), _capacity(other._capacity)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], other._data[i]);
		}

		~vector()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_alloc.deallocate(_data, _capacity);
		}

		vector& operator=(const vector& other);

		void assign(size_type count, const value_type& value);
		template <class InputIt>
		void assign(InputIt first, InputIt last);
		allocator_type get_allocator() const;

		// Element access
		reference at(size_type pos);
		const_reference at(size_type pos) const;
		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		pointer data();
		const_pointer data() const;

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
		void reserve(size_type new_cap);
		size_type capacity() const;

		// Modifiers
		void clear();
		iterator insert(const_iterator pos, const_reference value);
		iterator insert(const_iterator pos, size_type count, const_reference value);
		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		void push_back(const_reference value);
		void pop_back();
		void resize(size_type count, value_type value = value_type());
		void swap(vector& other);
	};

	// NON-MEMBER FUNCTIONS
	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs);
}

#endif
