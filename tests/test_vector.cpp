#include <iostream>
#include <string>

#ifdef REAL_STL
	#include <vector>
	namespace ft = std;
#else
	#include "../containers/vector.hpp"
#endif

template <typename T>
void print(ft::vector<T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::vector<T>::iterator it = v.begin(); it != v.end(); it++)
        std::cout << *it << ", ";
    std::cout << std::endl;
}

template <typename T>
void rprint(ft::vector<T> v, std::string title = "") {
    std::cout << title << std::endl;
    for (typename ft::vector<T>::reverse_iterator it = v.rbegin(); it != v.rend(); it++)
        std::cout << *it << ", ";
    std::cout << std::endl;
}

int main()
{
    // Constructors
    ft::vector<std::string> v_empty = ft::vector<std::string>();
    ft::vector<int> v_count(10, 42);
    v_count[3] = 3;
    ft::vector<int>::iterator it = v_count.begin();
    ft::vector<int> v_range(it + 3, it + 7);
    ft::vector<int> v_copy(v_count);
    ft::vector<int> v_assig = v_copy;
    v_copy[5] = 5;
    v_assig[5] = 10;

    print(v_empty, "empty constructor");
    print(v_count, "count constructor");
    print(v_range, "range constructor");
    print(v_copy, "copy constructor");
    print(v_assig, "assigned constructor");

    std::cout << "\n# assign method:" << std::endl;
    v_copy.assign(5, 6);
    v_assig.assign(it + 3, it + 6);
    print(v_copy, "v_copy: assign 5 values of 6");
    print(v_assig, "v_assig: assign range with iterators");

    int ref = v_count.at(3);
    std::cout << "\n# at method:\nv_count.at(3): " << ref << std::endl;
    try {
        v_count.at(20);
    } catch (const std::exception& e) {
        std::cout << "Exceptions: " << e.what() << std::endl;
    }

    std::cout << "\n# front: " << v_assig.front();
    std::cout << "\n# back: " << v_assig.back();
    const int *data = v_assig.data();
    std::cout << "\n# data: " << *data << ", " << data[1] << std::endl;

    std::cout << "\n# reverse iterators:" << std::endl;
    rprint(v_assig);

    std::cout << std::boolalpha;
    std::cout << "\n# v_empty.empty(): " << v_empty.empty();
    std::cout << "\n# v_assign.empty(): " << v_assig.empty();
    std::cout << "\n# v_empty.size(): " << v_empty.size();
    std::cout << "\n# v_assign.size(): " << v_assig.size();
    std::cout << "\n# v_assign.max_size(): " << v_assig.max_size();

    std::cout << "\n# v_assign.capacity(): " << v_assig.capacity();
    std::cout << "\n# v_assign.reserve(42): ";
    v_assig.reserve(42);
    std::cout << "\n# v_assign.capacity(): " << v_assig.capacity() << std::endl;

    print(v_assig, "v_assign before clear");
    v_assig.clear();
    print(v_assig, "v_assign after clear");

    v_count.insert(v_count.begin(), 33);
    v_count.insert(v_count.begin() + 2, 4, 9);
    print(v_count, "\n# insert in v_count:");
    v_copy.insert(v_copy.begin() + 3, v_count.begin(), v_count.begin() + 3);
    print(v_copy, "\n# insert in v_copy:");

    v_copy.erase(v_copy.begin() + 3);
    print(v_copy, "\n# erase in v_copy:");
    v_count.erase(v_count.begin() + 9, v_count.end());
    print(v_count, "\n# erase in v_count:");

    v_copy.push_back(11);
    print(v_copy, "\n# push 11 in v_copy:");
    v_copy.pop_back();
    print(v_copy, "\n# and pop :");

    v_copy.resize(20, 88);
    print(v_copy, "\n# resize to 20, default value 88 :");

    v_copy.swap(v_count);
    print(v_copy, "\n# v_copy swap with v_count:");
    print(v_count, "\n# v_count swap with v_copy:");

    std::cout << "\n# Comparators" << std::endl;
    ft::vector<int> alice(3), bob(4), eve(3);
    alice[1] = 1;
    alice[2] = 2;
    eve[1] = 1;
    eve[2] = 2;
    bob[0] = 3; bob[1] = 4; bob[2] = 5; bob[3] = 6;
    print(alice, "alice");
    print(bob, "bob");
    print(eve, "eve");

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