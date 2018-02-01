#ifndef D_TEST_FUNCTIONAL_H_
#define D_TEST_FUNCTIONAL_H_

#include "functional.h"
#include <functional>
#include <iostream>

namespace d_stl {
	void test_case_functional_less() {
		using std_less = std::less<int>;
		std::cout << std_less()(5, 20) << '\n';
		std::cout << std_less()(100, 10) << '\n';
		std::cout << std_less()(5, 5) << '\n';
		std::cout << std_less()(100, 100) << '\n';

		using d_less = d_stl::less<int>;
		std::cout << d_less()(5, 20) << '\n';
		std::cout << d_less()(100, 10) << '\n';
		std::cout << d_less()(5, 5) << '\n';
		std::cout << d_less()(100, 100) << '\n';
	}

	void test_case_functional_identify() {
		using d_identify_single = d_stl::identify<int>;
		std::cout << d_identify_single()(5) << '\n';

		using d_identify_pair = d_stl::identify<d_stl::pair<int, int>>;
		d_stl::pair<int, int> tem_pair(5, 5);
		std::cout << d_identify_pair()(tem_pair) << '\n';
	}

	void test_case_functional() {
		test_case_functional_less();
		test_case_functional_identify();
	}
}
#endif 
