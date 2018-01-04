#ifndef D_TEST_VECTOR_H_
#define D_TEST_VECTOR_H_

#include "test.h"
#include "vector.h"
#include <vector>
#include <cstdio> //printf
#include <cassert>

namespace d_stl {

	void test_vector_constructor() {
		d_stl::vector<int> my_vector_1;
		std::vector<int> s_vector_1;
		assert(equal_containter(my_vector_1, s_vector_1));

		d_stl::vector<int> my_vector_2(5);
		std::vector<int> s_vector_2(5);
		assert(equal_containter(my_vector_2, s_vector_2));

		d_stl::vector<int> my_vector_3(5, 1);
		std::vector<int> s_vector_3(5, 1);
		assert(equal_containter(my_vector_3, s_vector_3));

		std::vector<int> for_iterator(5, 2);
		d_stl::vector<int> my_vector_4(for_iterator.begin(), for_iterator.end());
		std::vector<int> s_vector_4(for_iterator.begin(), for_iterator.end());
		assert(equal_containter(my_vector_4, s_vector_4));

		d_stl::vector<int> for_lvalue1(5, 3);
		std::vector<int> for_lvalue2(5, 3);
		d_stl::vector<int> my_vector_5(for_lvalue1);
		std::vector<int> s_vector_5(for_lvalue2);
		assert(equal_containter(my_vector_5, s_vector_5));

	}

	void test_vector_size() {
	}

	void test_vector_insert() {
	}

	void test_vector() {
		test_vector_constructor();
		test_vector_size();
		test_vector_insert();

		//std::printf("%d/%d (%3.2%%) passed\n", test_vector_pass, test_vector_count, test_vector_pass*100.0 / test_vector_count);
	}

}

#endif // 

