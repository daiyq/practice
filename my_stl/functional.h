#ifndef D_FUNCTIONAL_H_
#define D_FUNCTIONAL_H_

namespace d_stl {
	//used as function object
	template<class T1, class T2>
	class pair {
	public:
		using first_type = T1;
		using second_type = T2;

		pair() :first(), second() {
		}
		pair(const T1& lhs, const T2& rhs) :first(lhs), second(rhs) {
		}

		first_type first;
		second_type second;
	};

	template<class T1,class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		if (lhs.first == rhs.first&&lhs.second == rhs.second) {
			return true;
		}
		else {
			return false;
		}
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		if (lhs.first < rhs.first) {
			return true;
		}
		else if (rhs.first < lhs.first) {
			return false;
		}
		else if (lhs.second < rhs.second) {
			return true;
		}
		else {
			return false;
		}
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!operator<(rhs, lhs));
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return operator<(rhs, lhs);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return (!operator<(lhs, rhs));
	}



	template<class T>
	class identify_set {
	public:
		const T& operator()(const T& t) {
			return t;
		}
	};

	//this template is to get the specialization(pair<>)
	template<class T>
	class identify_map {
	public:
		const T& operator()(const T& t) {
			return t;
		}
	};

	template<class T1, class T2>
	class identify_map<pair<T1, T2>> {
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

