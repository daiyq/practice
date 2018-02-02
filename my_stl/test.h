#ifndef D_TEST_H_
#define D_TEST_H_

#include "test_functional.h"
#include "test_vector.h"
#include "test_list.h"


namespace d_stl {

	void casual_test() {
		std::list<int> i_list(5, 1);
		i_list.clear();
		assert(i_list.begin()==i_list.end());
		if (i_list.empty()) {
			std::printf("the container is empty \n"); //yes
		}

		/*
		//test examples
		std::list<int> s_list_6{ 1,2,5,3,67,34,56,43,67,33,91 };
		s_list_6.sort();
		printer_containter(s_list_6, s_list_6);
		auto f = [](const int& lhs, const int& rhs) {
			return lhs > rhs;
		};
		s_list_6.sort(f);
		printer_containter(s_list_6, s_list_6);
		assert(equal_containter(s_list_6, s_list_6));
		
		std::list<int> s_lvalue6(4, 6);
		std::list<int> s_list_6(s_lvalue6);
		printer_containter(s_list_6, s_list_6);
		assert(equal_containter(s_list_6, s_list_6));

		std::list<int> s_rvalue7(4, 7);
		std::list<int> s_list_7(std::move(s_rvalue7));
		printer_containter(s_list_7, s_list_7);
		assert(equal_containter(s_list_7, s_list_7));
		*/
	
		
	}

	void test() {
		casual_test();
		d_stl::test_case_functional();
		d_stl::test_vector();
		d_stl::test_list();



	}
}
#endif 

