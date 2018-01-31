#ifndef D_FUNCTIONAL_H_
#define D_FUNCTIONAL_H_

namespace d_stl {
	//used as function object
	template<class T1, class T2>
	class pair {
	public:
		using first_type = T1;
		using second_type = T2;

		first_type first;
		second_type second;
	};

	template<class T>
	class identify {
	public:
		const T& operator()(const T& t) {
			return t;
		}
	};

	
	template<class T1, class T2>
	class identify<pair<T1, T2>> {
	public:
		const T1& operator()(const pair<T1, T2>& t) {
			return t.first;
		}
	};
	
	template<class T>
	class less {
	public:
		bool operator()(const T& lhs, const T& rhs) {
			return lhs < rhs;
		}
	};
}
#endif 

