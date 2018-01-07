#ifndef D_LIST_H_
#define D_LIST_H_

#include <cstdio>
#include <cstddef> //ptrdiff_t, size_t
#include <stdexcept> //throw
#include <initializer_list>
#include <type_traits>
//#include <algorithm>
#include "iterator.h"
#include <iterator> //distance()
#include "memory.h"
#include "algorithm.h"

namespace d_stl {

	template<class ListItem>
	class ListIterator {
	private:

	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef ListItem                   value_type;
		typedef std::ptrdiff_t             difference_type;
		typedef ListItem*                  pointer;
		typedef ListItem&                  reference;
		typedef ListIterator<ListItem> self;

		reference operator*() const {
			
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			
			return *this;
		}
		self& operator--() {
			
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			
		}
		self operator--(int) {
			
		}


	};

	template<class T, class Allocator=d_stl::allocator<T>>
	class list {
	private:


	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		//iterator
		typedef ListIterator<T> iterator;
		typedef const ListIterator<T> const_iterator;
		typedef d_stl::reverse_iterator<iterator> reverse_iterator;
		typedef d_stl::reverse_iterator<const_iterator> const_reverse_iterator;

		list();
		explicit list(size_type count);
		list(size_type count, const T& value);
		template<class InputIt>
		list(InputIt first, InputIt last);
		list(const list& other);
		list(list&& other);
		list(std::initializer_list<T> init);


	};

}
#endif 
