#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include "iterator.hpp"
# include "algorithm.hpp"

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
			: _alloc(alloc), _size(count), _capacity(count)
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
			for (size_type i = 0; first != last; first++, i++)
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

		vector& operator=(const vector& other)
		{
			~vector();  // Velocidad?: aumentar capacidad solo si size > capacity
			_alloc = other._alloc; // Necessary?
			_size = other._size;
			_capacity = other._capacity;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], other._data[i]);
			return *this;
		}

		void assign(size_type count, const value_type& value)
		{
			~vector();
			_size = count;
			_capacity = count;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], value);
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{
			~vector();
			_size = _capacity = last - first;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; first != last; first++, i++)
				_alloc.construct(&_data[i], *first);
		}

		allocator_type get_allocator() const
		{
			return allocator_type(_alloc);
		}

		// Element access
		reference at(size_type pos)
		{
			if (!(pos < _size))
				throw std::out_of_range("vector");
			return _data[pos];
		}

		const_reference at(size_type pos) const
		{
			if (!(pos < _size))
				throw std::out_of_range("vector");
			return _data[pos];
		}

		reference operator[](size_type pos) { return _data[pos]; }
		const_reference operator[](size_type pos) const { return _data[pos]; }
		reference front() { return _data[0]; }
		const_reference front() const { return _data[0]; }
		reference back() { return _data[_size - 1]; }
		const_reference back() const { return _data[_size - 1]; }
		pointer data() { return _data; }
		const_pointer data() const { return _data; }

		// Iterators
		iterator begin() { return iterator(_data); }
		const_iterator begin() const { return const_iterator(_data); }
		iterator end() { return iterator(_data + _size); }
		const_iterator end() const { return const_iterator(_data + _size); }
		reverse_iterator rbegin() { return reverse_iterator(_data + _size); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_data + _size); }
		reverse_iterator rend() { return reverse_iterator(_data); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_data); }

		// Capacity
		bool empty() const { return _size == 0; }
		size_type size() const { return _size; }
		size_type max_size() const { return _alloc.max_size(); }
		void reserve(size_type new_cap)
		{
			if (new_cap > max_size())
				throw std::length_error("can't allocate region");
			if (new_cap > _capacity)
			{
				pointer new_data = _alloc.allocate(new_cap);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&new_data[i], _data[i]);
					_alloc.destroy(&_data[i]);
				}
				_alloc.deallocate(_data, _capacity);
				_capacity = new_cap;
				_data = new_data;
			}
		}

		size_type capacity() const { return _capacity; }

		// Modifiers
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_data[i]);
			_size = 0;
		}

		iterator insert(const_iterator pos, const_reference value)
		{
			return insert(pos, 1, value);
		}

		iterator insert(const_iterator pos, size_type count, const_reference value)
		{
			difference_type idx = pos - begin();
			// ?? check pos boundary
			if (_size == _capacity)
				reserve(_size + count <= _capacity * 2
						? _capacity * 2 : _capacity + count);
			for (size_type j = _size + count - 1; j > idx + count - 1; j--)
			{
				_alloc.construct(&_data[j], _data[j - count]);
				_alloc.destroy(&_data[j - count]);
			}
			for (size_type i = idx; i < count; i++)
				_alloc.construct(&_data[i], value);
			_size += count;
			return iterator(_data + idx);
		}

		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last)
		{
			difference_type idx = pos - begin();
			difference_type count = last - first;
			// ?? check pos boundary
			if (_size == _capacity)
				reserve(_size + count <= _capacity * 2
						? _capacity * 2 : _capacity + count);
			for (size_type j = _size + count - 1; j > idx + count - 1; j--)
			{
				_alloc.construct(&_data[j], _data[j - count]);
				_alloc.destroy(&_data[j - count]);
			}
			for (size_type i = idx; i < count; i++)
				_alloc.construct(&_data[i], *(first + i));
			_size += count;
			return iterator(_data + idx);
		}

		iterator erase(iterator pos)
		{
			difference_type idx = pos - begin();
			_alloc.destroy(&_data[idx]);
			_size--;
			for (size_type j = idx; j < _size - 1; j++)
				_data[j] = _data[j + 1];
			return iterator(idx);
		}

		iterator erase(iterator first, iterator last)
		{
			difference_type idx = first - begin();
			difference_type offset = last - first;
			for (iterator it = first; it != last; it++)
				_alloc.destroy(it);
			for (; first != last; first++)
				_data[first] = _data[first + offset];
			return iterator(idx + offset);
		}

		void push_back(const_reference value)
		{
			if (_size == _capacity)
				reserve(_capacity ? _capacity * 2 : 1);
			_alloc.construct(&_data[_size], value);
			_size++;
		}

		void pop_back()
		{
			if (_size)
			{
				_alloc.destroy(&_data[_size - 1]);
				_size--;
			}
		}

		void resize(size_type count, value_type value = value_type())
		{
			if (count > _size)
			{
				reserve(_size + count <= _capacity * 2
						? _capacity * 2 : _capacity + count);
				for (size_type i = _size; i < count; i++)
					_alloc.construct(&_data[i], value);
			}
			else
			{
				for (size_type i = count; i < _size; i++)
					_alloc.destroy(&_data[i]);
			}
			_size = count;
		}

		void swap(vector& other)
		{
			size_type tmp_size = other._size;
			size_type tmp_capacity = other._capacity;
			pointer tmp_data = other._data;

			other._size = _size;
			_size = tmp_size;
			other._capacity = _capacity;
			_capacity = tmp_capacity;
			other._data = _data;
			_data = tmp_data;
		}
	};

	// NON-MEMBER FUNCTIONS
	template <class T, class Alloc>
	bool operator==(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.first()));
	}

	template <class T, class Alloc>
	bool operator!=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs) { return !(rhs < lhs); }
	template <class T, class Alloc>
	bool operator>(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs) { return rhs < lhs; }
	template <class T, class Alloc>
	bool operator>=(const ft::vector<T, Alloc>& lhs,
					const ft::vector<T, Alloc>& rhs) { return !(lhs < rhs); }

	template <class T, class Alloc>
	void swap(ft::vector<T, Alloc>& lhs, ft::vector<T, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
