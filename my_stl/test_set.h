#ifndef D_TEST_SET_H_
#define D_TEST_SET_H_

#include "test_initi.h"
#include "set.h"
#include <set>
#include <vector>

namespace d_stl {
	
	void test_case_set_member() {
		std::set<int> s_set_1;
		d_stl::set<int> my_set_1;
		printer_containter(my_set_1, s_set_1);
		assert(equal_containter(my_set_1, s_set_1));

		std::vector<int> it_value({ 1,2,3 });
		std::set<int> s_set_2(it_value.begin(), it_value.end());
		d_stl::set<int> my_set_2(it_value.begin(), it_value.end());
		printer_containter(my_set_2, s_set_2);
		assert(equal_containter(my_set_2, s_set_2));

		std::set<int> s_set_3(s_set_2);
		d_stl::set<int> my_set_3(my_set_2);
		printer_containter(my_set_3, s_set_3);
		assert(equal_containter(my_set_3, s_set_3));

		std::set<int> s_set_4(std::move(s_set_2));
		d_stl::set<int> my_set_4(std::move(my_set_2));
		printer_containter(my_set_4, s_set_4);
		assert(equal_containter(my_set_4, s_set_4));

		std::set<int> s_set_5({ 2,4,9,5 });
		d_stl::set<int> my_set_5({ 2,4,9,5 });
		printer_containter(my_set_5, s_set_5);
		assert(equal_containter(my_set_5, s_set_5));

		std::set<int> s_lvalue_6({ 1,4,6,9 });
		d_stl::set<int> my_lvalue_6({ 1,4,6,9 });
		std::set<int> s_set_6;
		d_stl::set<int> my_set_6;
		s_set_6 = s_lvalue_6;
		my_set_6 = my_lvalue_6;
		printer_containter(my_set_6, s_set_6);
		assert(equal_containter(my_set_6, s_set_6));

		std::set<int> s_lvalue_7({ 13,4,6,9 });
		d_stl::set<int> my_lvalue_7({ 13,4,6,9 });
		std::set<int> s_set_7;
		d_stl::set<int> my_set_7;
		s_set_7 = std::move(s_lvalue_7);
		my_set_7 = std::move(my_lvalue_7);
		printer_containter(my_set_7, s_set_7);
		assert(equal_containter(my_set_7, s_set_7));

		std::set<int> s_set_8;
		d_stl::set<int> my_set_8;
		s_set_8 = { 12,2,5,4 };
		my_set_8 = { 12,2,5,4 };
		printer_containter(my_set_8, s_set_8);
		assert(equal_containter(my_set_8, s_set_8));
	}

	void test_case_set_iterator() {

	}

	void test_cast_set_capacity() {
		std::set<int> s_set_1;
		d_stl::set<int> my_set_1;
		assert(my_set_1.empty());
		assert(my_set_1.empty() == s_set_1.empty());

		std::set<int> s_set_2({ 2,4,9,5 });
		d_stl::set<int> my_set_2({ 2,4,9,5 });
		assert(s_set_2.size() == my_set_2.size());

	}

	void test_case_set_modifiers() {
		std::set<int> s_set_1({ 2,4,9,5 });
		d_stl::set<int> my_set_1({ 2,4,9,5 });
		s_set_1.clear();
		my_set_1.clear();
		assert(s_set_1.size() == my_set_1.size());
		assert(equal_containter(my_set_1, s_set_1));

		int lvalue1 = 1;
		s_set_1.insert(lvalue1);
		my_set_1.insert(lvalue1);
		assert(equal_containter(my_set_1, s_set_1));

		s_set_1.insert(71);
		my_set_1.insert(71);
		assert(equal_containter(my_set_1, s_set_1));

		std::vector<int> it_value({ 15,22,39 });
		s_set_1.insert(it_value.begin(), it_value.end());
		my_set_1.insert(it_value.begin(), it_value.end());
		assert(equal_containter(my_set_1, s_set_1));

		s_set_1.insert({ 1,6,98,43,24 });
		my_set_1.insert({ 1,6,98,43,24 });
		assert(equal_containter(my_set_1, s_set_1));

		auto it_s_begin1 = s_set_1.begin();
		auto it_my_begin1 = my_set_1.begin();
		s_set_1.erase(it_s_begin1);
		my_set_1.erase(it_my_begin1);
		assert(equal_containter(my_set_1, s_set_1));

		s_set_1.erase(15);
		my_set_1.erase(15);
		assert(equal_containter(my_set_1, s_set_1));

		auto it_s_begin2 = s_set_1.begin();
		auto it_my_begin2 = my_set_1.begin();
		auto it_s_end2 = s_set_1.end();
		auto it_my_end2 = my_set_1.end();
		s_set_1.erase(it_s_begin2, it_s_end2);
		my_set_1.erase(it_my_begin2, it_my_end2);
		assert(equal_containter(my_set_1, s_set_1));

		std::set<int> s_set_2({ 2,4,9,5 });
		d_stl::set<int> my_set_2({ 2,4,9,5 });
		s_set_1.swap(s_set_2);
		my_set_1.swap(my_set_2);
		assert(equal_containter(my_set_1, s_set_1));
	}

	void test_case_set_lookup() {
		std::set<int> s_set_1({ 2,4,9,5 });
		d_stl::set<int> my_set_1({ 2,4,9,5 });
		assert(s_set_1.count(2) == 1);
		assert(my_set_1.count(2) == 1);

		assert(s_set_1.find(2) != s_set_1.end());
		assert(my_set_1.find(2) != my_set_1.end());

		assert(s_set_1.find(6) == s_set_1.end());
		assert(my_set_1.find(6) == my_set_1.end());

	}

	void test_case_set_compares() {
		d_stl::set<int> my_set_1({ 1,2,3,9 });
		d_stl::set<int> my_set_2({ 1,2,3,9 });

		assert((my_set_1 == my_set_2));

		my_set_1.insert(6);
		my_set_1.insert(7);
		assert((my_set_1 != my_set_2));

		assert((my_set_1 <= my_set_2));

		my_set_1.erase(6);
		my_set_1.erase(7);
		my_set_1.insert(7);
		my_set_1.insert(6);
		assert((my_set_1 >= my_set_2));

		d_stl::set<int> my_set_3({ 1,2,3,4 });
		d_stl::set<int> my_set_4({ 5,6,7,8 });
		assert((my_set_3 < my_set_4));
		assert((my_set_4 > my_set_3));

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

