#ifndef D_TEST_SET_H_
#define D_TEST_SET_H_

#include "test_initi.h"
#include "set.h"
#include <set>
#include <vector>

namespace d_stl {
	using My_Set_Int = d_stl::set<int>;
	using Std_Set_Int = std::set<int>;

	void test_case_set_member() {
		Std_Set_Int s_set_1;
		My_Set_Int my_set_1;
		printer_containter(my_set_1, s_set_1);
		assert(equal_containter(my_set_1, s_set_1));

		std::vector<int> It_value({ 1,2,3 });
		Std_Set_Int s_set_2(It_value.begin(), It_value.end());
		My_Set_Int my_set_2(It_value.begin(), It_value.end());
		printer_containter(my_set_2, s_set_2);
		assert(equal_containter(my_set_2, s_set_2));

		Std_Set_Int s_set_3(s_set_2);
		My_Set_Int my_set_3(my_set_2);
		printer_containter(my_set_3, s_set_3);
		assert(equal_containter(my_set_3, s_set_3));

		Std_Set_Int s_set_4(std::move(s_set_2));
		My_Set_Int my_set_4(std::move(my_set_2));
		printer_containter(my_set_4, s_set_4);
		assert(equal_containter(my_set_4, s_set_4));

		Std_Set_Int s_set_5({ 2,4,9,5 });
		My_Set_Int my_set_5({ 2,4,9,5 });
		printer_containter(my_set_5, s_set_5);
		assert(equal_containter(my_set_5, s_set_5));
	}

	void test_case_set_iterator() {
	}

	void test_cast_set_capacity() {
	}

	void test_case_set_modifiers() {
		std::set<int> s_set_1;
		s_set_1.find(1);
	}

	void test_case_set_lookup() {
	}

	void test_case_set_compares() {

	}

	void test_set() {
		test_case_set_member();
		test_case_set_iterator();
		test_cast_set_capacity();
		test_case_set_modifiers();
		test_case_set_lookup();
		test_case_set_compares();
	}
}
#endif 

