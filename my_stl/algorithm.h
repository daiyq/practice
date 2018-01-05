#ifndef D_ALGORITHM_H_
#define D_ALGORITHM_H_

namespace d_stl {
	template<class InputIt1, class InputIt2>
	InputIt2 copy(InputIt1 first, InputIt1 last, InputIt2 d_first) {
		for (; first != last;) {
			*(d_first++) = *(first++);
		}
		return d_first;
	}

	template<class BidirIt1, class BidirIt2>
	BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last) {
		for (; last >= first;) {
			*(--d_last) = *(--last);
		}
		return d_last;
	}


}
#endif  


