#ifndef D_TEST_H_
#define D_TEST_H_

#include <iterator>

namespace d_stl {

	static int test_count = 0;
	static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
	do{\
		test_count++;\
		if (equality){\
			test_pass++;}\
		else{\
			std::printf("%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);}\
	} while (0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect)==(actual), expect, actual, "%d")



template<class Containter1, class Containter2>
bool equal_containter(Containter1 c1, Containter2 c2) {
	auto first1 = std::begin(c1);
	auto last1 = std::end(c1);
	auto first2 = std::begin(c2);
	auto last2 = std::end(c2);
	for (; first1 != last1&&first2 != last2; ++first1, ++first2) {
		if (*first1 != *first2) {
			return false;
		}
	}
	return (first1 == last1) && (first2 == last2);
}


}
#endif // !D_TEST_H_

