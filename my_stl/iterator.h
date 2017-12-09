#ifndef D_ITERATOR_
#define D_ITERATOR_

#include <cstddef> //size_t

namespace d_stl {
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag :public input_iterator_tag {};
	struct bidirecional_iterator_tag :public forward_iterator_tag {};
	struct random_access_iterator_tag :public bidirecional_iterator_tag {};
	
	template<class Category,class T,class Distance=std::ptrdiff_t,class Pointer=T*,class Reference =T&>
	struct iterator {
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<typename IterT>
	struct iterator_traits {
		typedef typename IterT::iterator_category iterator_category;
		typedef typename IterT::value_type value_type;
		typedef typename IterT::difference_type difference_type;
		typedef typename IterT::pointer pointer;
		typedef typename IterT::reference reference;
	};

	template<typename IterT>
	struct iterator_traits<IterT*> {
		typedef typename random_access_iterator_tag iterator_category;
		typedef typename IterT value_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename IterT* pointer;
		typedef typename IterT& reference;
	};
	
	template<typename IterT>
	struct iterator_traits<const IterT*> {
		typedef typename random_access_iterator_tag iterator_category;
		typedef typename IterT value_type;
		typedef typename std::ptrdiff_t difference_type;
		typedef typename IterT* pointer;
		typedef typename IterT& reference;
	};

	template<class InputIt>
	typename iterator_traits<InputIt>::difference_type
		distance(InputIt first, InputIt last) {

	}

	template<class Iterator>
	class reverse_iterator {
	private:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef Iterator iterator_type;
		typedef reverse_iterator<Iterator> self;

		reverse_iterator();
		explicit reverse_iterator(Iterator it);
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other);
		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other);

		Iterator base() const {
			return current;
		}

		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			--current;
			return *this;
		}
		self& operator--() {
			++current;
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}
		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}

		self operator+(difference_type n) const {
			return self(current - n);
		}
		self operator-(difference_type n) const {
			return self(current + n);
		}
		self& operator+=(difference_type n) const {
			current -= n;
			return *this;
		}
		self& operator-=(difference_type n) const {
			current += n;
			return *this;
		}

	};

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator() {}

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(Iterator it) :current(it) {}

	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator=(const reverse_iterator<U>& other) {
		current = other.base();
	}

}
#endif