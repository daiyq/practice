#ifndef D_TEST_VECTOR_H_
#define D_TEST_VECTOR_H_

#include <cstdio> //printf
#include <vector>
#include "vector.h"

namespace d_stl {

	static int test_vector_count = 0;
	static int test_vector_pass = 0;

#define EXPECT_EQ_BASE(equality, from_my, from_std, format) \
	do{\
		test_vector_count++;\
		if (equality){\
			test_vector_pass++;}\
		else{\
			std::printf("%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, from_my, from_std);}\
	} while (0)

	void test_vector_constructor() {
		d_stl::vector<int> my_vector_1;
		std::vector<int> s_vector_1;

		d_stl::vector<int> my_vector_2(5);
		std::vector<int> s_vector_2(5);

		d_stl::vector<int> my_vector_3(5, 1);
		std::vector<int> s_vector_3(5, 1);

		std::vector<int> for_iterator(5, 2);
		d_stl::vector<int> my_vector_4(for_iterator.begin(), for_iterator.end());
		std::vector<int> s_vector_4(for_iterator.begin(), for_iterator.end());

		d_stl::vector<int> for_lvalue1(5, 3);
		std::vector<int> for_lvalue2(5, 3);
		d_stl::vector<int> my_vector_5(for_lvalue1);
		std::vector<int> s_vector_5(for_lvalue2);

				
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

