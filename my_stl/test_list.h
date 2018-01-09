#ifndef D_TEST_LIST_H_
#define D_TEST_LIST_H_

#include "test_initi.h"
#include "list.h"
#include <list>
#include <vector>
#include <cstdio> //printf
#include <cassert>
#include <utility> //std::move()

namespace d_stl {

	void test_case_list_member() {
		/*
		d_stl::list<int> my_list_1;
		std::list<int> s_list_1;
		assert(equal_containter(my_list_1, s_list_1));

		d_stl::list<int> my_list_2(5);
		std::list<int> s_list_2(5);
		assert(equal_containter(my_list_2, s_list_2));

		d_stl::list<int> my_list_3(5, 1);
		std::list<int> s_list_3(5, 1);
		assert(equal_containter(my_list_3, s_list_3));

		std::list<int> for_iterator4(5, 2);
		d_stl::list<int> my_list_4(for_iterator4.begin(), for_iterator4.end());
		std::list<int> s_list_4(for_iterator4.begin(), for_iterator4.end());
		assert(equal_containter(my_list_4, s_list_4));

		std::vector<int> for_iterator5(5, 2);
		d_stl::list<int> my_list_5(for_iterator5.begin(), for_iterator5.end());
		std::list<int> s_list_5(for_iterator5.begin(), for_iterator5.end());
		assert(equal_containter(my_list_5, s_list_5));

		d_stl::list<int> my_lvalue6(5, 3);
		std::list<int> s_lvalue6(5, 3);
		d_stl::list<int> my_list_6(my_lvalue6);
		std::list<int> s_list_6(s_lvalue6);
		assert(equal_containter(my_list_6, s_list_6));

		d_stl::list<int> my_rvalue7(5, 3);
		std::list<int> s_rvalue7(5, 3);
		d_stl::list<int> my_list_7(std::move(my_rvalue7));
		std::list<int> s_list_7(std::move(s_rvalue7));
		assert(equal_containter(my_list_7, s_list_7));

		d_stl::list<int> my_vector_8;
		std::list<int> s_vector_8;
		my_vector_8 = my_lvalue6;
		s_vector_8 = s_lvalue6;
		assert(equal_containter(my_vector_8, s_vector_8));

		d_stl::list<int> my_vector_9;
		std::list<int> s_vector_9;
		my_vector_9 = std::move(my_lvalue6);
		s_vector_9 = std::move(s_lvalue6);
		assert(equal_containter(my_vector_9, s_vector_9));

		d_stl::list<int> my_vector_10;
		std::list<int> s_vector_10;
		my_vector_10.assign(5, 4);
		s_vector_10.assign(5, 4);
		assert(equal_containter(my_vector_10, s_vector_10));

		d_stl::list<int> my_list_11;
		std::list<int> s_list_11;
		d_stl::list<int> my_lvalue11(5, 3);
		std::list<int> s_lvalue11(5, 3);
		my_list_11.assign(my_lvalue11.begin(), my_lvalue11.end());
		s_list_11.assign(s_lvalue11.begin(), s_lvalue11.end());
		assert(equal_containter(my_list_11, s_list_11));

		d_stl::list<int> my_list_12;
		std::list<int> s_list_12;
		std::vector<int> s_lvalue12(5, 3);
		my_list_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		s_list_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		assert(equal_containter(my_list_12, s_list_12));

		*/
	}

	void test_case_list_iterator() {

	}

	void test_cast_list_capacity() {

	}

	void test_case_list_modifiers() {
	}
	
	void test_case_list_operations() {
	}

	void test_case_list_compares() {
	}

	void test_list() {
		test_case_list_member();
		test_case_list_iterator();
		test_cast_list_capacity();
		test_case_list_modifiers();
		test_case_list_operations();
		test_case_list_compares();
	}
}
#endif 

