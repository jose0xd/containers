#ifndef RBTREE_HPP
# define RBTREE_HPP

namespace ft
{
  template <typename T, typename Compare>
  class rbtree
  {
  public:
    typedef T   value_type;
    typedef struct node
    {
      value_type  value;
      node        *parent;
      node        *left;
      node        *right;
    };
    typedef struct node node_type;
    typedef node_type*  node_pointer;
  };
}

#endif