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
	

		d_stl::list<int> my_list_1;
		std::list<int> s_list_1;
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		d_stl::list<int> my_list_2(4);
		std::list<int> s_list_2(4, 0);
		printer_containter(my_list_2, s_list_2);
		assert(equal_containter(my_list_2, s_list_2));
		
		d_stl::list<int> my_list_3(4, 3);
		std::list<int> s_list_3(4, 3);
		printer_containter(my_list_3, s_list_3);
		assert(equal_containter(my_list_3, s_list_3));

		std::list<int> for_iterator4(4, 4);
		d_stl::list<int> my_list_4(for_iterator4.begin(), for_iterator4.end());
		std::list<int> s_list_4(for_iterator4.begin(), for_iterator4.end());
		printer_containter(my_list_4, s_list_4);
		assert(equal_containter(my_list_4, s_list_4));

		std::vector<int> for_iterator5(4, 5);
		d_stl::list<int> my_list_5(for_iterator5.begin(), for_iterator5.end());
		std::list<int> s_list_5(for_iterator5.begin(), for_iterator5.end());
		printer_containter(my_list_5, s_list_5);
		assert(equal_containter(my_list_5, s_list_5));
		
		d_stl::list<int> my_lvalue6(4, 6);
		d_stl::list<int> my_list_6(my_lvalue6);
		std::list<int> s_lvalue6(4, 6);
		std::list<int> s_list_6(s_lvalue6);
		printer_containter(my_list_6, s_list_6);
		assert(equal_containter(my_list_6, s_list_6));
		
		d_stl::list<int> my_rvalue7(4, 7);
		std::list<int> s_rvalue7(4, 7);
		d_stl::list<int> my_list_7(std::move(my_rvalue7));
		std::list<int> s_list_7(std::move(s_rvalue7));
		printer_containter(my_list_7, s_list_7);
		assert(equal_containter(my_list_7, s_list_7));
		
		d_stl::list<int> my_lvalue8(4, 8);
		std::list<int> s_lvalue8(4, 8);
		d_stl::list<int> my_list_8;
		std::list<int> s_list_8;
		my_list_8 = my_lvalue8;
		s_list_8 = s_lvalue8;
		printer_containter(my_list_8, s_list_8);
		assert(equal_containter(my_list_8, s_list_8));
		
		d_stl::list<int> my_rvalue9(4, 9);
		std::list<int> s_rvalue9(4, 9);
		d_stl::list<int> my_list_9;
		std::list<int> s_list_9;
		my_list_9 = std::move(my_rvalue9);
		s_list_9 = std::move(s_rvalue9);
		printer_containter(my_list_9, s_list_9);
		assert(equal_containter(my_list_9, s_list_9));
		
		d_stl::list<int> my_list_10;
		std::list<int> s_list_10;
		my_list_10.assign(4, 10);
		s_list_10.assign(4, 10);
		printer_containter(my_list_10, s_list_10);
		assert(equal_containter(my_list_10, s_list_10));
		
		d_stl::list<int> my_list_11;
		std::list<int> s_list_11;
		d_stl::list<int> my_lvalue11(4, 11);
		std::list<int> s_lvalue11(4, 11);
		my_list_11.assign(my_lvalue11.begin(), my_lvalue11.end());
		s_list_11.assign(s_lvalue11.begin(), s_lvalue11.end());
		printer_containter(my_list_11, s_list_11);
		assert(equal_containter(my_list_11, s_list_11));
		
		d_stl::list<int> my_list_12;
		std::list<int> s_list_12;
		d_stl::vector<int> s_lvalue12(4, 12);
		my_list_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		s_list_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		printer_containter(my_list_12, s_list_12);
		assert(equal_containter(my_list_12, s_list_12));
		
		//initializer 
		d_stl::list<int> my_list_13{ 1,2,3,4,5 };
		std::list<int> s_list_13{ 1,2,3,4,5 };
		printer_containter(my_list_13, s_list_13);
		assert(equal_containter(my_list_13, s_list_13));

		d_stl::list<int> my_list_14;
		std::list<int> s_list_14;
		my_list_14 = { 14,15,16 };
		s_list_14 = { 14,15,16 };
		printer_containter(my_list_14, s_list_14);
		assert(equal_containter(my_list_14, s_list_14));

		d_stl::list<int> my_list_15;
		std::list<int> s_list_15;
		my_list_15.assign({ 15,16 });
		s_list_15.assign({ 15,16 });
		printer_containter(my_list_15, s_list_15);
		assert(equal_containter(my_list_15, s_list_15));
	}

	void test_case_list_iterator() {
		//has been used in equal_containter(),
		//so not test
	}

	void test_cast_list_capacity() {
		
		d_stl::list<int> my_list_1;
		std::list<int> s_list_1;
		assert(my_list_1.empty());
		assert(my_list_1.empty() == s_list_1.empty());

		d_stl::list<int> my_list_2(4);
		std::list<int> s_list_2(4);
		assert(my_list_2.size() == s_list_2.size());
		
		d_stl::list<int> my_list_3(4, 3);
		std::list<int> s_list_3(4, 3);
		auto v1 = my_list_3.front();
		auto v2 = my_list_3.front();
		auto v3 = s_list_3.back();
		auto v4 = s_list_3.back();
		assert(v1 == v2);
		assert(v3 == v4);
	}

	void test_case_list_modifiers() {
		
		d_stl::list<int> my_list_1(5);
		std::list<int> s_list_1(5);
		my_list_1.clear();
		s_list_1.clear();
		assert(my_list_1.empty());
		assert(equal_containter(my_list_1, s_list_1));

		auto my_pos1 = my_list_1.begin();
		auto s_pos1 = s_list_1.begin();
		int lvalue2 = 2;
		my_list_1.insert(my_pos1, lvalue2);
		s_list_1.insert(s_pos1, lvalue2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		auto my_pos2 = my_list_1.begin();
		auto s_pos2 = s_list_1.begin();
		my_list_1.insert(my_pos2, 2);
		s_list_1.insert(s_pos2, 2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		auto my_pos3 = my_list_1.begin();
		auto s_pos3 = s_list_1.begin();
		int lvalue4 = 4;
		my_list_1.insert(my_pos3, 2, lvalue4);
		s_list_1.insert(s_pos3, 2, lvalue4);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		auto my_pos4 = my_list_1.begin();
		auto s_pos4 = s_list_1.begin();
		d_stl::list<int> my_lvalue1(5, 3);
		std::list<int> s_lvalue1(5, 3);
		my_list_1.insert(my_pos4, my_lvalue1.begin(), my_lvalue1.end());
		s_list_1.insert(s_pos4, s_lvalue1.begin(), s_lvalue1.end());
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		auto my_pos5 = my_list_1.begin();
		auto s_pos5 = s_list_1.begin();
		my_list_1.erase(my_pos5);
		s_list_1.erase(s_pos5);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		auto my_pos6 = my_list_1.begin();
		auto s_pos6 = s_list_1.begin();
		my_pos6++;
		my_pos6++;
		s_pos6++;
		s_pos6++;
		auto my_pos61 = my_list_1.end();
		auto s_pos61 = s_list_1.end();
		my_list_1.erase(my_pos6, my_pos61);
		s_list_1.erase(s_pos6, s_pos61);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		int lvalue8 = 8;
		my_list_1.push_back(lvalue8);
		s_list_1.push_back(lvalue8);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.push_back(9);
		s_list_1.push_back(9);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.pop_back();
		s_list_1.pop_back();
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		int lvalue11 = 11;
		my_list_1.push_front(lvalue11);
		s_list_1.push_front(lvalue11);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.push_front(12);
		s_list_1.push_front(12);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.pop_front();
		s_list_1.pop_front();
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		std::size_t size = my_list_1.size();
		my_list_1.resize(size + 2);
		s_list_1.resize(size + 2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.resize(size + 4, 10);
		s_list_1.resize(size + 4, 10);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.resize(size - 2, 10);
		s_list_1.resize(size - 2, 10);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		d_stl::list<int> my_list_2(5, 14);
		std::list<int> s_list_2(5, 14);
		my_list_1.swap(my_list_2);
		s_list_1.swap(s_list_2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
	}
	
	void test_case_list_operations() {
		d_stl::list<int> my_list_1;
		std::list<int> s_list_1;
		int i = 9;
		while (i >= 0) {
			my_list_1.push_back(i);
			s_list_1.push_back(i);
			i--;
		}
		//printer_containter(my_list_1, s_list_1);
		//assert(equal_containter(my_list_1, s_list_1));

		my_list_1.sort();
		s_list_1.sort();
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		/*
		auto f = [](const int& lhs, const int& rhs) {
			if (lhs > rhs)
				return true;
			return false;
		};
		my_list_1.sort(f);
		s_list_1.sort(f);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		*/
		d_stl::list<int> my_list_2;
		std::list<int> s_list_2;
		int j = 12;
		while (j >= 6) {
			my_list_2.push_back(j);
			s_list_2.push_back(j);
			j--;
		}
		my_list_2.sort();
		s_list_2.sort();
		printer_containter(my_list_2, s_list_2);
		my_list_1.merge(my_list_2);
		s_list_1.merge(s_list_2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		j = 20;
		while (j >= 15) {
			my_list_2.push_back(j);
			s_list_2.push_back(j);
			j--;
		}
		//printer_containter(my_list_2, s_list_2);
		auto my_it = my_list_1.cbegin();
		auto s_it = s_list_1.cbegin();
		my_list_1.splice(my_it, my_list_2);
		s_list_1.splice(s_it, s_list_2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_it = my_list_1.cbegin();
		s_it = s_list_1.cbegin();
		j = 30;
		while (j >= 26) {
			my_list_2.push_back(j);
			s_list_2.push_back(j);
			j--;
		}
		auto my_it_2 = my_list_2.cbegin();
		auto s_it_2 = s_list_2.cbegin();
		my_it_2++;
		my_it_2++;
		s_it_2++;
		s_it_2++;
		my_list_1.splice(my_it, my_list_2, my_it_2);
		s_list_1.splice(s_it, s_list_2, s_it_2);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
		my_it = my_list_1.cbegin();
		s_it = s_list_1.cbegin();
		auto my_it_2_begin = my_list_2.cbegin();
		auto s_it_2_begin = s_list_2.cbegin();
		auto my_it_2_end = my_list_2.cend();
		auto s_it_2_end = s_list_2.cend();
		my_list_1.splice(my_it, my_list_2, my_it_2_begin, my_it_2_end);
		s_list_1.splice(s_it, s_list_2, s_it_2_begin, s_it_2_end);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.remove(8);
		s_list_1.remove(8);
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		my_list_1.reverse();
		s_list_1.reverse();
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));

		
		my_list_1.unique();
		s_list_1.unique();
		printer_containter(my_list_1, s_list_1);
		assert(equal_containter(my_list_1, s_list_1));
		
	}

	void test_case_list_compares() {
		d_stl::list<int> my_list_1(5, 0);
		d_stl::list<int> my_list_2(4, 0);
		my_list_2.push_back(0);
		assert((my_list_1 == my_list_2));

		my_list_1.push_back(1);
		my_list_2.push_back(0);
		assert((my_list_1 != my_list_2));

		assert((my_list_1 >= my_list_2));

		d_stl::list<int> my_list_3(2, 0);
		d_stl::list<int> my_list_4(2, 0);
		my_list_3.push_back(0);
		my_list_4.push_back(1);
		assert((my_list_3 <= my_list_4));

		d_stl::list<int> my_list_5;
		d_stl::list<int> my_list_6;
		my_list_5.push_back(0);
		my_list_6.push_back(1);
		assert((my_list_5 < my_list_6));

		my_list_5.pop_back();
		my_list_6.pop_back();
		my_list_5.push_back(1);
		my_list_6.push_back(0);
		assert((my_list_5 > my_list_6));
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

