#include <iostream>
#include <string>

#ifdef REAL_STL
	#include <map>
    #include <utility>
	namespace ft = std;
#else
	#include "../containers/map.hpp"
	#include "../utils/utility.hpp"
#endif

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream& os, ft::pair<T1, T2> p) {
    os << "(" << p.first << "\t| " << p.second << "\t)"; 
    return os;
}

template <typename Key, typename T>
static void print(ft::map<Key, T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::map<Key, T>::iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

template <typename Key, typename T>
static void rprint(ft::map<Key, T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::map<Key, T>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void test_map()
{
    ft::map<int, std::string> m = ft::map<int, std::string>();
    ft::map<int, std::string> m1 = ft::map<int, std::string>();
    print(m1, "# empty constructor:");
    m1.insert(ft::make_pair(21, "abc"));
    m1.insert(ft::make_pair(32, "bcde"));
    m1.insert(ft::make_pair(42, "ccccc"));
    m1.insert(ft::make_pair(50, "dedido"));
    print(m1, "# after 4 inserts:");
    ft::map<int, std::string> m2(m1.begin(), --m1.end());
    print(m2, "# range constructor:");
    ft::map<int, std::string> m3(m2);
    print(m3, "# copy constructor:");
    ft::map<int, std::string> m4 = m3;
    print(m4, "# assigned constructor:");

    std::cout << "\n# m1.at(32): " << m1.at(32) << std::endl;
    try {
        std::cout << "\n# m1.at(23): " << m1.at(23) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exceptions: " << e.what() << std::endl;
    }
    std::cout << "m2[32]: " << m2[32] << std::endl;
    std::cout << "m2[32] = " << (m2[32] = "insert") << std::endl;
    std::cout << "m2[23] = " << (m2[23] = "new node") << std::endl;
    print(m2, "operator[]");

    rprint(m2, "reverse print");

    std::cout << std::boolalpha;
    std::cout << "\n# m.empty(): " << m.empty();
    std::cout << "\n# m2.empty(): " << m2.empty();
    std::cout << "\n# m.size(): " << m.size();
    std::cout << "\n# m2.size(): " << m2.size();
    std::cout << "\n# m2.max_size(): " << m2.max_size() << std::endl;

    print(m3, "m3 before clear");
    m3.clear();
    print(m3, "m3 after clear");
    std::cout << "\n# m3.size(): " << m3.size() << std::endl;

    print(m2, "m2 before inserts");
    std::cout << "m2.insert(make::pair(9, \"bacon\") -> "
        << *(m2.insert(ft::make_pair(9, "bacon")).first) << std::endl;
    std::cout << "m2.insert(m2.begin(), make::pair(10, \"frito\")" << std::endl;
    m2.insert(m2.begin(), ft::make_pair(10, "frito"));
    std::cout << "m2.insert(++m4.begin(), --m4.end())" << std::endl;
    m2.insert(++m4.begin(), m4.end());
    print(m4, "m4 map");
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

    // std::cout << "m4.equal_range(21): " << *(m4.equal_range(21).first)
    //     << ", " << *(m4.equal_range(21).second) << std::endl;
    std::cout << "m4.lower_bound(20): " << *(m4.lower_bound(20))
        <<  "\nm4.upper_bound(20): " << *(m4.upper_bound(20)) << std::endl;

    ft::map<int, std::string>::key_compare k_comp = m4.key_comp();
    ft::map<int, std::string>::value_compare v_comp = m4.value_comp();
    std::cout << "\nk_comp(10, m4.begin()->first): "
        << k_comp(10, m4.begin()->first) << std::endl;
    std::cout << "k_comp(8, m4.begin()->first): "
        << k_comp(8, m4.begin()->first) << std::endl;
    std::cout << "v_comp(make_pair(10, \"hey\"), *m4.begin()): "
        << v_comp(ft::make_pair(10, "hey"), *(m4.begin())) << std::endl;
    std::cout << "v_comp(make_pair(8, \"hey\"), *m4.begin()): "
        << v_comp(ft::make_pair(8, "hey"), *(m4.begin())) << std::endl;

    // Comparators
    ft::map<int, std::string> alice = m1;
    ft::map<int, std::string> bob = m4;
    ft::map<int, std::string> eve = m1;

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