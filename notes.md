- Uso de friend en RandomAccessIterator
- Funcion base en RandomAccessIterator??
- Poner base Iterator con 5 argumentos en template?

# Iterators
Iterators can be thought of as an abstraction of pointers.

## LegacyIterator
_LegacyIterator_ is the base set of requirements used by other iterator types: LegacyInputIterator, LegacyOutputIterator, LegacyForwardIterator, LegacyBidirectionalIterator, and LegacyRandomAccessIterator.

### Requirement
The type `It` satisfies _LegacyIterator_ if
- satisfies CopyConstructible
- satisfies CopyAssignable
- satisfies Destructible
- satisfies Swappable
- std::iterator_traits<It> has member typedefs value_type, difference_type, reference, pointer and iterator_category
- Given `r` of type `It`, the following expressions must be valid: *r and ++r.


--------
# C++ crash course
## Output iterator
- *itr=t	Writes into the output iterator. After operation, iterator is incrementable but not necessarily dereferencable.
- ++itr / itr++	Increments the iterator. After operation, iterator is either dereferencable or exhausted (past the end) but is not necessarily incrementable.
- iterator-type{ itr }	Copy-constructs an iterator from itr.

## Input iterator
- *itr	Dereferences the pointed-to member. Might or might not be read-only.
- itr->mbr	Dereferences the member mbr of the object pointed-to by itr.
- ++itr / itr++	Increments the iterator. After operation, iterator is either dereferencable or exhausted (past the end).
- itr1 == itr2 / itr1 != itr2	Compares whether the iterators are equal (pointing to the same element).
- iterator-type{ itr }	Copy-constructs an iterator from itr.

## Forward Iterators
- *itr	Dereferences the pointed-to member. Might or might not be read-only.
- itr->mbr	Dereferences the member mbr of the object pointed-to by itr.
- ++itr / itr++	Increments the iterator so it points to the next element.
- itr1 == itr2 / itr1 != itr2	Compares whether the iterators are equal (pointing to the same element).
- iterator-type{}	Default constructs an iterator.
- iterator-type{ itr }	Copy-constructs an iterator from itr.
- itr1 = itr2	Assigns an iterator itr1 from itr2.

## Bidirectional Iterators
- *itr	Dereferences the pointed-to member. Might or might not be read-only.
- itr->mbr	Dereferences the member mbr of the object pointed-to by itr.
- ++itr / itr++	Increments the iterator so it points to the next element.
- --itr / itr--	Decrements the iterator so it points to the previous element.
- itr1 == itr2 / itr1 != itr2	Compares whether the iterators are equal (pointing to the same element).
- iterator-type{}	Default constructs an iterator.
- iterator-type{ itr }	Copy-constructs an iterator from itr.
- itr1 = itr2	Assigns an iterator itr1 from itr2.

## Random-Access Iterators
- itr[n]	Dereferences the element with index n.
- itr+n / itr-n	Returns the iterator at offset n from itr.
- itr2-itr1	Computes the distance between itr1 and itr2.
- *itr	Dereferences the pointed-to member. Might or might not be read-only.
- itr->mbr	Dereferences the member mbr of the object pointed to by itr.
- ++itr / itr++	Increments the iterator so it points to the next element.
- --itr / itr--	Decrements the iterator so it points to the previous element.
- itr1 == itr2 / itr1 != itr2	Compares whether the iterators are equal (pointing to the same element).
- iterator-type{}	Default constructs an iterator.
- iterator-type{ itr }	Copy-constructs an iterator from itr.
- itr1 < itr2 / itr1 > itr2 / itr1 <= itr2 / itr1 >= itr2	Performs the corresponding comparison to the iterators’ positions.

------
# srcs/map/ite_n1.cpp should not compile by this error
srcs/map/ite_n1.cpp: In function ‘int main()’:
srcs/map/ite_n1.cpp:10:49: error: conversion from
‘std::map<int, int>::const_iterator’
{aka ‘std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::const_iterator’} to non-scalar type ‘std::map<int, int>::iterator’
{aka ‘std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::iterator’} requested
   10 |         std::map<T1, T2>::iterator it = mp.begin(); // <-- error expected
      |                                         ~~~~~~~~^~