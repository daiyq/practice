#ifndef D_TEST_VECTOR_H_
#define D_TEST_VECTOR_H_

#include "test_initi.h"
#include "vector.h"
#include "list.h"
#include <vector>
#include <list>
#include <cstdio> //printf
#include <cassert>
#include <utility> //std::move()

namespace d_stl {

	void test_case_vector_member() {
		d_stl::vector<int> my_vector_1;
		std::vector<int> s_vector_1;
		printer_containter(my_vector_1, s_vector_1);
		assert(equal_containter(my_vector_1, s_vector_1));

		d_stl::vector<int> my_vector_2(5);
		std::vector<int> s_vector_2(5);
		printer_containter(my_vector_2, s_vector_2);
		assert(equal_containter(my_vector_2, s_vector_2));

		d_stl::vector<int> my_vector_3(5, 3);
		std::vector<int> s_vector_3(5, 3);
		printer_containter(my_vector_3, s_vector_3);
		assert(equal_containter(my_vector_3, s_vector_3));

		std::vector<int> for_iterator4(5, 4);
		d_stl::vector<int> my_vector_4(for_iterator4.begin(), for_iterator4.end());
		std::vector<int> s_vector_4(for_iterator4.begin(), for_iterator4.end());
		printer_containter(my_vector_4, s_vector_4);
		assert(equal_containter(my_vector_4, s_vector_4));

		std::list<int> for_iterator5(5, 5);
		d_stl::vector<int> my_vector_5(for_iterator5.begin(), for_iterator5.end());
		std::vector<int> s_vector_5(for_iterator5.begin(), for_iterator5.end());
		printer_containter(my_vector_5, s_vector_5);
		assert(equal_containter(my_vector_4, s_vector_4));
		
		d_stl::vector<int> my_lvalue6(5, 6);
		std::vector<int> s_lvalue6(5, 6);
		d_stl::vector<int> my_vector_6(my_lvalue6);
		std::vector<int> s_vector_6(s_lvalue6);
		printer_containter(my_vector_6, s_vector_6);
		assert(equal_containter(my_vector_6, s_vector_6));

		d_stl::vector<int> my_rvalue7(5, 7);
		std::vector<int> s_rvalue7(5, 7);
		d_stl::vector<int> my_vector_7(std::move(my_rvalue7));
		std::vector<int> s_vector_7(std::move(s_rvalue7));
		printer_containter(my_vector_7, s_vector_7);
		assert(equal_containter(my_vector_7, s_vector_7));
		
		d_stl::vector<int> my_vector_8;
		std::vector<int> s_vector_8;
		my_vector_8 = my_lvalue6;
		s_vector_8 = s_lvalue6;
		printer_containter(my_vector_8, s_vector_8);
		assert(equal_containter(my_vector_8, s_vector_8));

		d_stl::vector<int> my_vector_9;
		std::vector<int> s_vector_9;
		my_vector_9 = std::move(my_lvalue6);
		s_vector_9 = std::move(s_lvalue6);
		printer_containter(my_vector_9, s_vector_9);
		assert(equal_containter(my_vector_9, s_vector_9));

		d_stl::vector<int> my_vector_10;
		std::vector<int> s_vector_10;
		my_vector_10.assign(5, 10);
		s_vector_10.assign(5, 10);
		printer_containter(my_vector_10, s_vector_10);
		assert(equal_containter(my_vector_10, s_vector_10));

		d_stl::vector<int> my_vector_11;
		std::vector<int> s_vector_11;
		d_stl::vector<int> my_lvalue11(5, 11);
		std::vector<int> s_lvalue11(5, 11);
		my_vector_11.assign(my_lvalue11.begin(), my_lvalue11.end());
		s_vector_11.assign(s_lvalue11.begin(), s_lvalue11.end());
		printer_containter(my_vector_11, s_vector_11);
		assert(equal_containter(my_vector_11, s_vector_11));

		d_stl::vector<int> my_vector_12;
		std::vector<int> s_vector_12;
		std::list<int> s_lvalue12(5, 12);
		my_vector_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		s_vector_12.assign(s_lvalue12.begin(), s_lvalue12.end());
		printer_containter(my_vector_12, s_vector_12);
		assert(equal_containter(my_vector_12, s_vector_12));
		
		//initializer
		d_stl::vector<int> my_vector_13{ 7,8,9,2,3 };
		std::vector<int> s_vector_13{ 7,8,9,2,3 };
		printer_containter(my_vector_13, s_vector_13);
		assert(equal_containter(my_vector_13, s_vector_13));

		d_stl::list<int> my_vector_14;
		std::list<int> s_vector_14;
		my_vector_14 = { 14,15,16 };
		s_vector_14 = { 14,15,16 };
		printer_containter(my_vector_14, s_vector_14);
		assert(equal_containter(my_vector_14, s_vector_14));

		d_stl::list<int> my_vector_15;
		std::list<int> s_vector_15;
		my_vector_15.assign({ 15,16 });
		s_vector_15.assign({ 15,16 });
		printer_containter(my_vector_15, s_vector_15);
		assert(equal_containter(my_vector_15, s_vector_15));
	}

	void test_case_vector_iterator() {
		//has been used in equal_containter(),
		//so not test
	}

	void test_case_vector_capacity() {
		d_stl::vector<int> my_vector_1;
		std::vector<int> s_vector_1;
		assert(my_vector_1.empty());
		assert(my_vector_1.empty() == s_vector_1.empty());

		d_stl::vector<int> my_vector_2(5);
		std::vector<int> s_vector_2(5);
		assert(my_vector_2.size() == s_vector_2.size());

		d_stl::vector<int> my_vector_3(5, 1);
		std::vector<int> s_vector_3(5, 1);
		auto v1 = my_vector_3[0];
		auto v2 = s_vector_3[0];
		auto v3 = my_vector_3.at(1);
		auto v4 = s_vector_3.at(1);
		assert(v1 == v2);
		assert(v3 == v4);
		auto v5 = my_vector_3.front();
		auto v6 = s_vector_3.front();
		auto v7 = my_vector_3.back();
		auto v8 = s_vector_3.back();
		assert(v5 == v6);
		assert(v7 == v8);

	}

	void test_case_vector_modifiers() {
		d_stl::vector<int> my_vector_1(5, 1);
		std::vector<int> s_vector_1(5, 1);
		my_vector_1.clear();
		s_vector_1.clear();
		assert(my_vector_1.empty());
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos1 = my_vector_1.begin();
		auto s_pos1 = s_vector_1.begin();
		int lvalue1 = 1;
		my_vector_1.insert(my_pos1, lvalue1);
		s_vector_1.insert(s_pos1, lvalue1);
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos2 = my_vector_1.begin();
		auto s_pos2 = s_vector_1.begin();
		my_vector_1.insert(my_pos2, 2);
		s_vector_1.insert(s_pos2, 2);
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos3 = my_vector_1.begin();
		auto s_pos3 = s_vector_1.begin();
		my_vector_1.insert(my_pos3, 2, lvalue1);
		s_vector_1.insert(s_pos3, 2, lvalue1);
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos4 = my_vector_1.begin();
		auto s_pos4 = s_vector_1.begin();
		my_pos4++;
		my_pos4++;
		s_pos4++;
		s_pos4++;
		d_stl::vector<int> my_lvalue1(5, 3);
		std::vector<int> s_lvalue1(5, 3);
		my_vector_1.insert(my_pos4, my_lvalue1.begin(), my_lvalue1.end());
		s_vector_1.insert(s_pos4, s_lvalue1.begin(), s_lvalue1.end());
		assert(equal_containter(my_vector_1, s_vector_1));
		
		auto my_pos5 = my_vector_1.begin();
		auto s_pos5 = s_vector_1.begin();
		std::list<int> s_lvalue2(5, 4);
		my_vector_1.insert(my_pos5, s_lvalue2.begin(), s_lvalue2.end());
		s_vector_1.insert(s_pos5, s_lvalue2.begin(), s_lvalue2.end());
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos6 = my_vector_1.begin();
		auto s_pos6 = s_vector_1.begin();
		my_pos6++;
		s_pos6++;
		my_vector_1.erase(my_pos6);
		s_vector_1.erase(s_pos6);
		printer_containter(my_vector_1, s_vector_1);
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos7 = my_vector_1.begin();
		auto s_pos7 = s_vector_1.begin();
		auto my_begin_pos7 = my_pos7;
		auto s_begin_pos7 = s_pos7;
		my_pos7++;
		my_pos7++;
		s_pos7++;
		s_pos7++;
		auto my_end_pos7 = my_pos7;
		auto s_end_pos7 = s_pos7;
		my_vector_1.erase(my_pos7, my_end_pos7);
		s_vector_1.erase(s_pos7, s_end_pos7);
		printer_containter(my_vector_1, s_vector_1);
		assert(equal_containter(my_vector_1, s_vector_1));

		auto my_pos8 = my_vector_1.begin();
		auto s_pos8 = s_vector_1.begin();
		my_pos8++;
		my_pos8++;
		s_pos8++;
		s_pos8++;
		my_vector_1.insert(my_pos8, { 3,6,9,14 });
		s_vector_1.insert(s_pos8, { 3,6,9,14 });
		printer_containter(my_vector_1, s_vector_1);
		assert(equal_containter(my_vector_1, s_vector_1));

		int lvalue7 = 7;
		my_vector_1.push_back(lvalue7);
		s_vector_1.push_back(lvalue7);
		assert(equal_containter(my_vector_1, s_vector_1));

		my_vector_1.push_back(8);
		s_vector_1.push_back(8);
		assert(equal_containter(my_vector_1, s_vector_1));

		my_vector_1.pop_back();
		s_vector_1.pop_back();
		assert(equal_containter(my_vector_1, s_vector_1));

		my_vector_1.resize(4);
		s_vector_1.resize(4);
		assert(equal_containter(my_vector_1, s_vector_1));

		my_vector_1.resize(17, 12);
		s_vector_1.resize(17, 12);
		assert(equal_containter(my_vector_1, s_vector_1));

		d_stl::vector<int> my_vector_2(5, 19);
		std::vector<int> s_vector_2(5, 19);
		my_vector_1.swap(my_vector_2);
		s_vector_1.swap(s_vector_2);
		assert(equal_containter(my_vector_1, s_vector_1));
	}

	void test_case_vector_compares() {
		d_stl::vector<int> my_vector_1(5, 0);
		d_stl::vector<int> my_vector_2(5, 0);
		assert(my_vector_1 == my_vector_2);

		my_vector_1.push_back(1);
		my_vector_2.push_back(2);
		assert(my_vector_1 != my_vector_2);

		assert(my_vector_1 <= my_vector_2);

		my_vector_1.clear();
		my_vector_2.clear();
		my_vector_1.push_back(1);
		my_vector_2.push_back(2);
		assert(my_vector_1 < my_vector_2);
	}

	void test_vector() {
		test_case_vector_member();
		test_case_vector_iterator();
		test_case_vector_capacity();
		test_case_vector_modifiers();
		test_case_vector_compares();

		//std::printf("%d/%d (%3.2%%) passed\n", test_vector_pass, test_vector_count, test_vector_pass*100.0 / test_vector_count);
	}

}

#endif // 

