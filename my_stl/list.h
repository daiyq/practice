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

	template<class T>
	class ListNode {
	public:
		T* prev;
		T* next;
		T data;
	};

	template<class ListItem>
	class ListIterator {
	public:
		using iterator_category = bidirectional_iterator_tag;
		using value_type = ListItem;
		using difference_type = std::ptrdiff_t;
		using pointer = ListItem*;
		using reference = ListItem&;
		using self = ListIterator<ListItem>;
		using ptr_node = ListNode<ListItem>*;

	private:
		ptr_node current;

	public:
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

		//Member functions
		list();
		explicit list(size_type count);
		list(size_type count, const value_type& value);
		template<class InputIt>
		list(InputIt first, InputIt last);
		list(const list& other);
		list(list&& other);
		list(std::initializer_list<T> ilist);
		~list();

		list& operator=(const list& other);
		list& operator=(list&& other);
		list& operator=(std::initializer_list<T> ilist);

		void assign(size_type count, const value_type& value);
		template<class InputIt>
		void assign(InputIt first, InputIt last);
		void assign(std::initializer_list<T> ilist);

		reference front() {
		}

		const_reference front() const {
		}

		reference back() {
		}

		const_reference back() const {
		}

		//Iterators
		iterator begin() noexcept {
			
		}
		const_iterator begin() const noexcept {
			
		}
		const_iterator cbegin() const noexcept {
			
		}
		iterator end() noexcept {
			
		}
		iterator end() const noexcept {
			
		}
		const_iterator cend() const noexcept {
			
		}

		reverse_iterator rbegin() noexcept {
			
		}
		const_reverse_iterator rbegin() const noexcept {
			
		}
		const_reverse_iterator crbegin() const noexcept {
			
		}
		reverse_iterator rend() noexcept {
			
		}
		const_reverse_iterator rend() const noexcept {
			
		}
		const_reverse_iterator crend() const noexcept {
			
		}

		//Capacity
		bool empty() const noexcept {
			
		}
		size_type size() const noexcept {
			
		}

		//Modifiers
		void clear();
		iterator insert(const_iterator pos, const value_type& value); // return the first element inserted
		iterator insert(const_iterator pos, value_type&& value);
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);//not finished
		iterator erase(const_iterator pos); //return the following removed element
		iterator erase(const_iterator first, const_iterator last);
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back();
		void push_front(const value_type& value);
		void push_front(value_type&& value);
		void pop_front();
		void resize(size_type count);
		void resize(size_type count, const value_type& value);
		void swap(list& other);

		//Operations
		//from other to *this

		//no copy, and other becomes empty
		void merge(list& other);
		void merge(list&& other);
		template<class Compare>
		void merge(list& other, Compare comp);
		template<class Compare>
		void merge(list&& other, Compare comp);
		//no copy or move, but the internal pointers are re_pointed
		void splice(const_iterator pos, list& other);
		void splice(const_iterator pos, list&& other);
		void splice(const_iterator pos, list& other, const_iterator it);
		void splice(const_iterator pos, list&& other, const_iterator it);
		void splice(const_iterator pos, list& other, const_iterator first, const_iterator last);
		void splice(const_iterator pos, list&& other, const_iterator first, const_iterator last);
		void remove(const value_type& value);
		template<class UnaryPredicate>
		void remove_if(UnaryPredicate p);
		void reverse();
		void unipue();
		template<class BinaryPredicate>
		void unique(BinaryPredicate p);
		void sort();
		template<class Compare>
		void sort(Compare comp);

	};

	template<class T,class Allocator>
	list<T, Allocator>::list() {
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count) {
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count, const value_type& value) {
	
	}

	template<class T, class Allocator>
	template<class InputIt>
	list<T, Allocator>::list(InputIt first, InputIt last) {
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(const list& other) {
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(list&& other) {
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(std::initializer_list<T> ilist) {
	}

	template<class T, class Allocator>
	list<T, Allocator>::~list() {
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(const list& other) {
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(list&& other) {
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(std::initializer_list<T> ilist) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(size_type count, const value_type& value) {
	}

	template<class T, class Allocator>
	template<class InputIt>
	void list<T, Allocator>::assign(InputIt first, InputIt last) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(std::initializer_list<T> ilist) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::clear() {

	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, const value_type& value) {
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, value_type&& value) {
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, size_type count, const value_type& value) {
	}

	template<class T, class Allocator>
	template<class InputIt>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos) {
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(const value_type& value) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(value_type&& value) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::pop_back() {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(const value_type& value) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(value_type&& value) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::pop_front() {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::resize(size_type count) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::resize(size_type count, const value_type& value) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::swap(list& other) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::merge(list& other) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::merge(list&& other) {
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::merge(list& other, Compare comp) {
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::merge(list&& other, Compare comp) {
	}
	
	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator it) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other, const_iterator it) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other, const_iterator first, const_iterator last) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::remove(const value_type& value) {
	}

	template<class T, class Allocator>
	template<class UnaryPredicate>
	void list<T, Allocator>::remove_if(UnaryPredicate p) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::reverse() {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::unipue() {
	}

	template<class T, class Allocator>
	template<class BinaryPredicate>
	void list<T, Allocator>::unique(BinaryPredicate p) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::sort() {
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::sort(Compare comp) {
	}






	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator==(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		

		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator!=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return (!operator<(lhs, rhs));
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return (!operator<=(lhs, rhs));
	}

}
#endif 
