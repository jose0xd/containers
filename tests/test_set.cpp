#include <iostream>
#include <string>

#ifdef REAL_STL
	#include <set>
    #include <utility>
	namespace ft = std;
#else
	#include "../containers/set.hpp"
	#include "../utils/utility.hpp"
#endif

template <typename T>
static void print(ft::set<T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::set<T>::iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename T>
static void rprint(ft::set<T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::set<T>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void test_set()
{
    ft::set<int> m = ft::set<int>();
    ft::set<int> m1 = ft::set<int>();
    print(m1, "# empty constructor:");
    m1.insert(11);
    m1.insert(21);
    m1.insert(42);
    m1.insert(50);
    print(m1, "# after 4 inserts:");
    ft::set<int> m2(m1.begin(), --m1.end());
    print(m2, "# range constructor:");
    ft::set<int> m3(m2);
    print(m3, "# copy constructor:");
    ft::set<int> m4 = m3;
    print(m4, "# assigned constructor:");

    rprint(m4, "reverse print");

    std::cout << std::boolalpha;
    std::cout << "\n# m.empty(): " << m.empty();
    std::cout << "\n# m4.empty(): " << m4.empty();
    std::cout << "\n# m.size(): " << m.size();
    std::cout << "\n# m4.size(): " << m4.size();
    std::cout << "\n# m4.max_size(): " << m4.max_size() << std::endl;

    print(m3, "m3 before clear");
    m3.clear();
    print(m3, "m3 after clear");
    std::cout << "\n# m3.size(): " << m3.size() << std::endl;

    print(m2, "m2 before inserts");
    std::cout << "m2.insert(make::pair(9, \"bacon\") -> "
        << *(m2.insert(9).first) << std::endl;
    std::cout << "m2.insert(m2.begin(), make::pair(10, \"frito\")" << std::endl;
    m2.insert(m2.begin(), 10);
    std::cout << "m2.insert(++m4.begin(), --m4.end())" << std::endl;
    m2.insert(++m4.begin(), m4.end());
    print(m4, "m4 set");
    print(m2, "m2 after inserts");

    std::cout << "m2.erase(m2.begin())" << std::endl;
    m2.erase(m2.begin());
    print(m2, "m2 after erase");

    std::cout << "m4.erase(++m4.begin(), m4.end())" << std::endl;
    m4.erase(++m4.begin(), m4.end());
    print(m4, "m4 after erase");

    std::cout << "m2.erase(42)" << std::endl;
    m2.erase(42);
    print(m2, "m2 after erase");

    std::cout << "\n# m2.swap(m4)" << std::endl;
    m2.swap(m4);
    print(m2, "m2:");
    print(m4, "m4:");

    std::cout << "\n# m4.count(21): " << m4.count(21)
        << ", m4.count(22): " << m4.count(22) << std::endl;
    std::cout << "m4.find(21): " << *(m4.find(21)) << std::endl;

    std::cout << "m4.equal_range(11): " << *(m4.equal_range(11).first)
        << ", " << *(m4.equal_range(11).second) << std::endl;
    std::cout << "m4.lower_bound(20): " << *(m4.lower_bound(20))
        <<  "\nm4.upper_bound(20): " << *(m4.upper_bound(20)) << std::endl;

    ft::set<int>::key_compare k_comp = m4.key_comp();
    ft::set<int>::value_compare v_comp = m4.value_comp();
    std::cout << "\nk_comp(11, m4.begin()->first): "
        << k_comp(11, *(m4.begin())) << std::endl;
    std::cout << "k_comp(8, m4.begin()->first): "
        << k_comp(8, *(m4.begin())) << std::endl;
    std::cout << "v_comp(make_pair(11, \"hey\"), *m4.begin()): "
        << v_comp(11, *(m4.begin())) << std::endl;
    std::cout << "v_comp(make_pair(10, \"hey\"), *m4.begin()): "
        << v_comp(10, *(m4.begin())) << std::endl;

    // Comparators
    ft::set<int> alice = m1;
    ft::set<int> bob = m4;
    ft::set<int> eve = m1;

    // Compare non equal containers
    std::cout << "alice == bob returns " << (alice == bob) << '\n';
    std::cout << "alice != bob returns " << (alice != bob) << '\n';
    std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    std::cout << "alice >= bob returns " << (alice >= bob) << '\n';
 
    std::cout << '\n';
 
    // Compare equal containers
    std::cout << "alice == eve returns " << (alice == eve) << '\n';
    std::cout << "alice != eve returns " << (alice != eve) << '\n';
    std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    std::cout << "alice >= eve returns " << (alice >= eve) << '\n';
}