#include <iostream>
#include "map.hpp"
#include "utility.hpp"

int main() {
    ft::map<int, int> m = ft::map<int, int>();

    auto n1 = m.insert(ft::make_pair(2, 4));
    auto n2 = m.insert(ft::make_pair(42, 34));
    auto n3 = m.insert(ft::make_pair(1, 10));

    std::cout << n1->value.first << " | " << n1->value.second << std::endl;
    std::cout << n1->right->value.first << " | " << n1->right->value.second << std::endl;
    std::cout << n1->left->value.first << " | " << n1->left->value.second << std::endl;

    int x = m.at(42);
    std::cout << "x: " << x << std::endl;
    const int y = m.at(2);
    std::cout << "y: " << y << std::endl;
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
    it++;
    std::cout << "it first: " << it->first << std::endl;
    it++;
    std::cout << "it first: " << it->first << std::endl;

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
}