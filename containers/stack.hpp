#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		// MEMBER TYPES
		typedef Container                           container_type;
		typedef typename Container::value_type      value_type;
		typedef typename Container::size_type       size_type;
		typedef typename Container::reference       reference;
		typedef typename Container::const_reference const_reference;

	protected:
		// MEMBER OBJECTS
		container_type c;

	public:
		// MEMBER FUNCTIONS
		explicit stack(const container_type& cont=container_type()) {
			c = cont;
		}
		stack(const stack& other) { *this = other; }
		~stack() {}
		stack& operator=(const stack& other) {
			c = other.c;
			return *this;
		}

		// Element access
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }

		// Capacity
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }

		// Modifiers
		void push(const value_type& value) { c.push_back(value); }
		void pop() { c.pop_back(); }

		// NON-MEMBER FUNCTIONS
		friend bool operator==(const stack& lhs, const stack& rhs) { return lhs.c == rhs.c; }
		friend bool operator!=(const stack& lhs, const stack& rhs) { return lhs.c != rhs.c; }
		friend bool operator<(const stack& lhs, const stack& rhs) { return lhs.c < rhs.c; }
		friend bool operator<=(const stack& lhs, const stack& rhs) { return lhs.c <= rhs.c; }
		friend bool operator>(const stack& lhs, const stack& rhs) { return lhs.c > rhs.c; }
		friend bool operator>=(const stack& lhs, const stack& rhs) { return lhs.c >= rhs.c; }
	};
}

#endif