#ifndef D_TEST_H_
#define D_TEST_H_

#include "test_vector.h"
#include "test_list.h"

namespace d_stl {

	void casual_test() {
		std::list<int> i_list(5, 1);
		i_list.clear();
		assert(i_list.begin()==i_list.end());
		if (i_list.empty()) {
			std::printf("the container is empty"); //yes
		}


	}

	void test() {
		casual_test();
		d_stl::test_vector();
		d_stl::test_list();



	}
}
#endif 

