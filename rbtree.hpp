#ifndef RBTREE_HPP
# define RBTREE_HPP

# include "map_iterator.hpp"

namespace ft
{
	template <typename T, typename Compare>
	class rbtree
	{
	public:
		typedef T				value_type;
		typedef struct node<T>	node_type;
		typedef node_type*		node_pointer;
	};
}

#endif