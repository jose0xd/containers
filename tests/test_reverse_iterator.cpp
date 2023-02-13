#include <cstddef>
#include <iostream>
#include "iterator.hpp"
 
template <typename T, std::size_t SIZE>
class Stack
{
    T arr[SIZE];
    std::size_t pos = 0;
public:
    T pop()
    {
        return arr[--pos];
    }
    Stack& push(const T& t)
    {
        arr[pos++] = t;
        return *this;
    }
    // we wish that looping on Stack would be in LIFO order
    // thus we use std::reverse_iterator as an adaptor to existing iterators
    // (which are in this case the simple pointers: [arr, arr+pos)

    //auto begin() { return ft::reverse_iterator(arr + pos); }
    //auto end() { return ft::reverse_iterator(arr); }

    auto rbegin() { return ft::reverse_iterator(arr + pos); }
    auto rend() { return ft::reverse_iterator(arr); }
    auto begin() { return ft::RandomAccessIterator<T>(arr); }
    auto end() { return ft::RandomAccessIterator<T>(arr + pos); }
};
 
int main()
{
    Stack<int, 8> s;
    s.push(5).push(15).push(25).push(35);
    for (int val: s)
        std::cout << val << ' ';

	ft::reverse_iterator rb = s.rbegin();
	std::cout << "\nrb[0]: " << rb[0] << "\n";
	std::cout << "rb[3]: " << rb[3] << "\n";

	ft::reverse_iterator re = s.rend();
	std::cout << "rb == re: " << (rb == re) << "\n";
	std::cout << "rb != re: " << (rb != re) << "\n";
	std::cout << "rb < re: " << (rb < re) << "\n";
	std::cout << "rb > re: " << (rb > re) << "\n";

    for (int val: s)
        std::cout << val << ' ';

	ft::RandomAccessIterator b = s.begin();
	std::cout << "\nb[0]: " << b[0] << "\n";
	std::cout << "b[3]: " << b[3] << "\n";

	ft::RandomAccessIterator e = s.end();
	std::cout << "b == e: " << (b == e) << "\n";
	std::cout << "b != e: " << (b != e) << "\n";
	std::cout << "b < e: " << (b < e) << "\n";
	std::cout << "b > e: " << (b > e) << "\n";

	std::cout << "e - b: " << (e - b) << "\n";
}
