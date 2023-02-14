#include <iostream>

#ifdef REAL_STL
	#include <vector>
	namespace ft = std;
#else
	#include "../containers/vector.hpp"
#endif
 
void test_iterators()
{
    ft::vector<int> s;
    s.push_back(5);
    s.push_back(15);
    s.push_back(25);
    s.push_back(35);

	ft::reverse_iterator rb = s.rbegin();
	std::cout << "\nrb[0]: " << rb[0] << "\n";
	std::cout << "rb[3]: " << rb[3] << "\n";

	ft::reverse_iterator re = s.rend();
	std::cout << "rb == re: " << (rb == re) << "\n";
	std::cout << "rb != re: " << (rb != re) << "\n";
	std::cout << "rb < re: " << (rb < re) << "\n";
	std::cout << "rb > re: " << (rb > re) << "\n";

	ft::vector<int>::iterator b = s.begin();
	std::cout << "\nb[0]: " << b[0] << "\n";
	std::cout << "b[3]: " << b[3] << "\n";

	ft::vector<int>::iterator e = s.end();
	std::cout << "b == e: " << (b == e) << "\n";
	std::cout << "b != e: " << (b != e) << "\n";
	std::cout << "b < e: " << (b < e) << "\n";
	std::cout << "b > e: " << (b > e) << "\n";

	std::cout << "e - b: " << (e - b) << "\n";
}
