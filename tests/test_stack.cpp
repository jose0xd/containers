#include <iostream>
#include <string>
#include <list>

#ifdef REAL_STL
	#include <stack>
    #include <vector>
	namespace ft = std;
#else
	#include "../containers/stack.hpp"
#endif

int main()
{
    ft::stack<std::string, std::list<std::string> > s1;
    ft::vector<int> vec(5, 2);
    ft::stack<int, ft::vector<int> > s2(vec);
    ft::stack<int, ft::vector<int> > s3(s2);
    ft::stack<int, ft::vector<int> > s4 = s3;

    std::cout << std::boolalpha;
    std::cout << "s4.top: " << s4.top() << std::endl;
    std::cout << "s1.empty: " << s1.empty() << std::endl;
    std::cout << "s1.size: " << s1.size() << std::endl;
    std::cout << "s4.empty: " << s4.empty() << std::endl;
    std::cout << "s4.size: " << s4.size() << std::endl;

    s4.push(3);
    std::cout << "s4.empty: " << s4.empty() << std::endl;
    std::cout << "s4.size: " << s4.size() << std::endl;
    s4.pop();
    std::cout << "s4.empty: " << s4.empty() << std::endl;
    std::cout << "s4.size: " << s4.size() << std::endl;

    s1.push("hey man");
    s4.push(33);
    // Compare non equal containers
    std::cout << "s2 == s3 returns " << (s2 == s3) << '\n';
    std::cout << "s2 != s3 returns " << (s2 != s3) << '\n';
    std::cout << "s2 <  s3 returns " << (s2 < s3) << '\n';
    std::cout << "s2 <= s3 returns " << (s2 <= s3) << '\n';
    std::cout << "s2 >  s3 returns " << (s2 > s3) << '\n';
    std::cout << "s2 >= s3 returns " << (s2 >= s3) << '\n';
 
    std::cout << '\n';
 
    // Compare equal containers
    std::cout << "s2 == s4 returns " << (s2 == s4) << '\n';
    std::cout << "s2 != s4 returns " << (s2 != s4) << '\n';
    std::cout << "s2 <  s4 returns " << (s2 < s4) << '\n';
    std::cout << "s2 <= s4 returns " << (s2 <= s4) << '\n';
    std::cout << "s2 >  s4 returns " << (s2 > s4) << '\n';
    std::cout << "s2 >= s4 returns " << (s2 >= s4) << '\n';

}