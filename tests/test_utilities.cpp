#include <iostream>

#ifdef REAL_STL
	#include <algorithm>
	#include <type_traits>
	#include <utility>
	namespace ft = std;
#else
	#include "../utils/algorithm.hpp"
	#include "../utils/type_traits.hpp"
	#include "../utils/utility.hpp"
#endif

template <typename T>
static void check_int(T n, typename ft::enable_if<ft::is_integral<T>::value>::type* = NULL)
{
	(void)n;
	std::cout << "It's integral\n";
}

template <typename T>
static void check_int(T n, typename ft::enable_if<!ft::is_integral<T>::value>::type* = NULL)
{
	(void)n;
	std::cout << "It's not integral\n";
}

static bool binary_pred(int a, int b)
{
	return a == b;
}

static bool binary_comp(char a, char b)
{
	return a < b;
}

void test_utilities()
{
	// ENABLE_IF & IS_INTEGRAL
	{
		bool				b = true;
		char				c = 'a';
		// char16_t			c16 = 'a';
		// char32_t			c32 = 'a';
		wchar_t				wc = 'a';
		short				s = 0;
		int					i = 0;
		long				l = 0;
		long long			ll = 0;
		unsigned char		uc = 'a';
		unsigned short		us = 0;
		unsigned int		ui = 0;
		unsigned long		ul = 0;
		unsigned long long	ull = 0;
		signed char			sc = 'a';
		short int			si = 0;
		signed short		ss = 0;

		float				f = 0.f;
		double				d = 0.0;

		check_int(b);
		check_int(c);
		// check_int(c16);
		// check_int(c32);
		check_int(wc);
		check_int(s);
		check_int(i);
		check_int(l);
		check_int(ll);
		check_int(uc);
		check_int(us);
		check_int(ui);
		check_int(ul);
		check_int(ull);
		check_int(sc);
		check_int(si);
		check_int(ss);
		check_int(f);
		check_int(d);
	}

	// EQUAL & LEXICOGRAPHICAL_COMPARE
	{
		int num_list1[6] = {0, 1, 2, 3, 4, 5};
		int num_list2[6] = {0, 1, 2, 3, 9, 8};
		int num_list3[6] = {6, 7, 0, 3, 9, 8};
		char str1[20] = "string number 1";
		char str2[20] = "string number 2";
		char str3[20] = "String number 1";

		std::cout << "\nstd::equal\n";
		std::cout << ft::equal(&num_list1[0], &num_list1[6], &num_list2[0]) << "\n";
		std::cout << ft::equal(&num_list2[0], &num_list2[6], &num_list3[0]) << "\n";
		std::cout << ft::equal(&num_list2[3], &num_list2[6], &num_list3[3]) << "\n";

		std::cout << ft::equal(&num_list1[0], &num_list1[6], &num_list2[0], binary_pred) << "\n";
		std::cout << ft::equal(&num_list2[0], &num_list2[6], &num_list3[0], binary_pred) << "\n";
		std::cout << ft::equal(&num_list2[3], &num_list2[6], &num_list3[3], binary_pred) << "\n";

		std::cout << "\nstd::lexicographical_compare\n";
		std::cout << ft::lexicographical_compare(&str1[0], &str1[15], &str2[0], &str2[15]) << "\n";
		std::cout << ft::lexicographical_compare(&str1[0], &str1[15], &str3[0], &str3[15]) << "\n";
		std::cout << ft::lexicographical_compare(&str2[0], &str2[15], &str3[0], &str3[15]) << "\n";

		std::cout << ft::lexicographical_compare(&str1[0], &str1[15], &str2[0], &str2[15], binary_comp) << "\n";
		std::cout << ft::lexicographical_compare(&str1[0], &str1[15], &str3[0], &str3[15], binary_comp) << "\n";
		std::cout << ft::lexicographical_compare(&str2[0], &str2[15], &str3[0], &str3[15], binary_comp) << "\n";
	}

	// PAIR & MAKE_PAIR
	{
		ft::pair<int, char> p1(42, 'Z');
		ft::pair<int, char> p2 = ft::make_pair<int, char>(42, 'X');
		ft::pair<int, char> p3 = p1;

		std::cout << "\nstd::pair and std::make_pair\n";
		std::cout << "p1.first: " << p1.first << ", p1.second: " << p1.second << "\n";
		std::cout << "p2.first: " << p2.first << ", p2.second: " << p2.second << "\n";
		std::cout << "p3.first: " << p3.first << ", p3.second: " << p3.second << "\n";

		std::cout << "p1 == p2: " << (p1 == p2) << "\n";
		std::cout << "p1 == p3: " << (p1 == p3) << "\n";
		std::cout << "p3.first = 21\n";
		p3.first = 21;
		std::cout << "p1 == p3: " << (p1 == p3) << "\n";
		std::cout << "p1 != p2: " << (p1 != p2) << "\n";
		std::cout << "p1 < p2: " << (p1 < p2) << "\n";
		std::cout << "p1 <= p2: " << (p1 <= p2) << "\n";
		std::cout << "p1 > p2: " << (p1 > p2) << "\n";
		std::cout << "p1 >= p2: " << (p1 >= p2) << "\n";
	}
}
