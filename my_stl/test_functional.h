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

		using d_stl_less = d_stl::less<int>;
		std::cout << d_stl_less()(5, 20) << '\n';
		std::cout << d_stl_less()(100, 10) << '\n';
		std::cout << d_stl_less()(5, 5) << '\n';
		std::cout << d_stl_less()(100, 100) << '\n';
	}
}
#endif 
