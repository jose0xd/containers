#include <iostream>
#include "map.hpp"
#include "utility.hpp"
#include <stdlib.h>

// #include <map>
// #define ft std

void leaks() {
    system("leaks -q a.out");
}

int main() {
    atexit(leaks);

    ft::map<int, int> m = ft::map<int, int>();

    auto n1 = m.insert(ft::make_pair(2, 4));
    m.print();
    auto n2 = m.insert(ft::make_pair(42, 34));
    m.print();
    auto n3 = m.insert(ft::make_pair(1, 10));
    m.print();
    auto n4 = m.insert(ft::make_pair(5, 83));
    m.print();

    std::cout << n1.first->first << " | " << n1.first->second << ", " << n1.second << std::endl;
    std::cout << n2.first->first << " | " << n2.first->second << ", " << n2.second << std::endl;
    std::cout << n3.first->first << " | " << n3.first->second << ", " << n3.second << std::endl;
    std::cout << n4.first->first << " | " << n4.first->second << ", " << n4.second << std::endl;

    m.erase(n1.first, n2.first);
    m.erase(8);
    m.print();

    int x = m.at(42);
    std::cout << "x: " << x << std::endl;
    // const int y = m.at(2);
    // std::cout << "y: " << y << std::endl;
    // m.at(3);
    auto it = m.begin();
    auto last = m.end();
    std::cout << "last: " << last->first << std::endl;
    last--;
    std::cout << "last: " << last->first << std::endl;
    std::cout << "it first: " << it->first << std::endl;
    std::cout << "it second: " << it->second << std::endl;
    it++;
    std::cout << "it first: " << it->first << std::endl;
    // it++;
    // std::cout << "it first: " << it->first << std::endl;
    // it++;
    // std::cout << "it first: " << it->first << std::endl;

    std::cout << "it == m.end(): " << (it == m.end()) << std::endl;
    std::cout << "it == last: " << (it == last) << std::endl;
    for (auto iter = m.begin(); iter != m.end(); ++iter)
        std::cout << "oldschool: " << iter->first << " " << std::endl;
    std::cout << std::endl;
    for (auto elem : m) {
        std::cout << elem.first << " " << std::endl;
    }
    std::cout << std::endl;

    auto f = m.find(1);
    auto e = m.find(3);
    std::cout << "e->second: " << e->second << std::endl;
    std::cout << "f->second: " << f->second << std::endl;
    std::cout << "count(1): " << m.count(1) << ", count(3): " << m.count(3) << std::endl;

    std::cout << "lower(10): " << m.lower_bound(10)->first << std::endl;
    std::cout << "lower(2): " << m.lower_bound(2)->first << std::endl;
    std::cout << "lower(42): " << m.lower_bound(42)->first << std::endl;
    std::cout << "lower(43): " << m.lower_bound(43)->first << ", " << m.lower_bound(43)->second << std::endl;
    std::cout << "upper(10): " << m.upper_bound(10)->first << std::endl;
    std::cout << "upper(2): " << m.upper_bound(2)->first << std::endl;
    std::cout << "upper(42): " << m.upper_bound(42)->first << std::endl;
    std::cout << "upper(43): " << m.upper_bound(43)->first << ", " << m.upper_bound(43)->second << std::endl;

    auto p = m.equal_range(1);
    for (auto& q = p.first; q != p.second; ++q) {
        std::cout << "m[" << q->first << "] = " << q->second << '\n';
    }

    // Comparators
    ft::map<int, char> alice = ft::map<int, char>();
    alice.insert(ft::make_pair(1, 'a'));
    alice.insert(ft::make_pair(2, 'b'));
    alice.insert(ft::make_pair(3, 'c'));
    ft::map<int, char> bob = ft::map<int, char>();
    bob.insert(ft::make_pair(7, 'Z'));
    bob.insert(ft::make_pair(8, 'Y'));
    bob.insert(ft::make_pair(9, 'X'));
    bob.insert(ft::make_pair(10, 'W'));
    ft::map<int, char> eve = ft::map<int, char>();
    eve.insert(ft::make_pair(1, 'a'));
    eve.insert(ft::make_pair(2, 'b'));
    eve.insert(ft::make_pair(3, 'c'));
 
    std::cout << std::boolalpha;
 
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

    /////
    ft::map<int, std::string> mp;
    typedef ft::map<int, std::string>::value_type PAIR;
    mp.insert(PAIR(42, "lol"));
    mp.print();
    mp.insert(PAIR(42, "mdr"));
    mp.print();
    mp.insert(PAIR(50, "mdr"));
    mp.print();
}