#ifndef D_LIST_H_
#define D_LIST_H_

#include <cstdio>
#include <cstddef> //ptrdiff_t, size_t
#include <stdexcept> //throw
#include <utility> //std::move()
#include <initializer_list>
#include <type_traits>
//#include <algorithm>
#include "iterator.h"
#include <iterator> //distance()
#include "memory.h"
#include "algorithm.h"

namespace d_stl {

	template<class T>
	class list_node {
	public:
		using ptr_node = list_node<T>*;
		ptr_node prev;
		ptr_node next;
		T data;
	};

	template<class ListItem>
	class list_iterator :public d_stl::bidirectional_iterator<ListItem, std::ptrdiff_t> {
	public:
		using iterator_category = bidirectional_iterator_tag;
		using value_type = ListItem;
		using difference_type = std::ptrdiff_t;
		using pointer = ListItem*;
		using reference = ListItem&;
		using self = list_iterator<ListItem>;
		using node = list_node<ListItem>;
		using ptr_node = node*;

	private:
		ptr_node current;

	public:
		list_iterator() :current(nullptr) {
		}
		list_iterator(const ptr_node& item) :current(item) {
		}
		list_iterator(const self& it) :current(it.current) {
		}

		bool operator==(const self& other) const {
			return current == other.current;
		}
		bool operator!=(const self& other) const {
			return current != other.current;
		}

		const ptr_node data() const {
			return current;
		}

		self& operator=(const self& other) {
			if (this != &other) {
				current = other.data();
			}
			return *this;
		}

		reference operator*() const {
			return (*current).data;
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			current = current->next;
			return *this;
		}
		self& operator--() {
			current = current->prev;
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			ptr_node tmp = current;
			++*this;
			return tmp;
		}
		self operator--(int) {
			ptr_node tmp = current;
			--*this;
			return tmp;
		}

	};

	template<class ListItem>
	bool operator==(const list_iterator<ListItem>& lhs, const list_iterator<ListItem>& rhs) {
		return (lhs.current == rhs.current);
	}

	template<class ListItem>
	bool operator!=(const list_iterator<ListItem>& lhs, const list_iterator<ListItem>& rhs) {
		return (lhs.current != rhs.current);
	}

#define LIST_ALLOCATOR_
#ifdef LIST_ALLOCATOR_

	template<class T, class Allocator=d_stl::allocator<list_node<T>>>
	class list {
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		//using pointer = list_node<T>*;
		//using const_pointer = const list_node<T>*;
		using iterator = list_iterator<T>;
		using const_iterator = const list_iterator<T>;
		using reverse_iterator = d_stl::reverse_iterator<iterator>;
		using const_reverse_iterator = d_stl::reverse_iterator<const_iterator>;
		using node = list_node<T>;
		using ptr_node = list_node<T>*;
		using data_alloc = Allocator;

	private:
		ptr_node current;

	public:
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
			return current->next->data;
		}

		const_reference front() const {
			return current->next->data;
		}

		reference back() {
			return current->prev->data;
		}

		const_reference back() const {
			return current->prev->data;
		}

		//Iterators
		iterator begin() noexcept {
			return iterator(current->next);
		}
		const_iterator begin() const noexcept {
			return const_iterator(current->next);
		}
		const_iterator cbegin() const noexcept {
			return const_iterator(current->next);
		}
		iterator end() noexcept {
			return iterator(current);
		}
		const_iterator end() const noexcept {
			return const_iterator(current);
		}
		const_iterator cend() const noexcept {
			return const_iterator(current);
		}

		reverse_iterator rbegin() noexcept {
			return reverse_iterator(current);
		}
		const_reverse_iterator rbegin() const noexcept {
			return const_reverse_iterator(current);
		}
		const_reverse_iterator crbegin() const noexcept {
			return const_reverse_iterator(current);
		}
		reverse_iterator rend() noexcept {
			return iterator(current->next);
		}
		const_reverse_iterator rend() const noexcept {
			return const_reverse_iterator(current->next);
		}
		const_reverse_iterator crend() const noexcept {
			return const_reverse_iterator(current->next);
		}

		//Capacity
		bool empty() const noexcept {
			return current->next == current;
		}
		size_type size() const noexcept {
			size_type i = 0;
			ptr_node pt = current->next;
			while (pt != current) {
				i++;
				pt = pt->next;
			}
			return i;
		}

		//Modifiers
		void clear();
		iterator insert(const_iterator pos, const value_type& value); // return the first element inserted
		iterator insert(const_iterator pos, value_type&& value);
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);
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
		void unique();
		template<class BinaryPredicate>
		void unique(BinaryPredicate p);
		void sort();
		template<class Compare>
		void sort(Compare comp);

	private:
		ptr_node allocate();
		void initialize();//initialize the header
		void deallocate(ptr_node p);

		void destory(ptr_node p);
		void delete_data_and_memory();
		void delete_context();//reserve header
		
		iterator insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		iterator insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type);

		iterator insert_node(const_iterator pos, const value_type& value);
		iterator delete_node(iterator pos);
		void delete_node(ptr_node p);

		template<class Compare>
		ptr_node merge_sort(ptr_node first, Compare comp);
		template<class Compare>
		ptr_node merge_base(ptr_node first1, ptr_node first2, Compare comp);

		void relink(ptr_node first, ptr_node last);
	};

	template<class T,class Allocator>
	list<T, Allocator>::list() {
		initialize();
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value_type(), typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count, const value_type& value) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	list<T, Allocator>::list(InputIt first, InputIt last) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(const list& other) {
		initialize();
		const_iterator pos = cbegin();
		const_iterator first = other.begin();
		const_iterator last = other.end();
		insert_base(pos, first, last, typename std::is_integral<const_iterator>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(list&& other) {
		current = other.current;
		other.current = nullptr;
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(std::initializer_list<T> ilist) {
		initialize();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::~list() {
		delete_data_and_memory();
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(const list& other) {
		if (this != &other) {
			delete_context();
			const_iterator pos = cbegin();
			const_iterator first = other.begin();
			const_iterator last = other.end();
			insert_base(pos, first, last, typename std::is_integral<const_iterator>::type());
		}
		return *this;
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(list&& other) {
		if (this != &other) {
			delete_data_and_memory();
			current = other.current;
			other.current = nullptr;
		}
		return *this;
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(std::initializer_list<T> ilist) {
		delete_context();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
		return *this;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(size_type count, const value_type& value) {
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	void list<T, Allocator>::assign(InputIt first, InputIt last) {
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(std::initializer_list<T> ilist) {
		delete_context();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T, class Allocator>
	void list<T, Allocator>::clear() {
		delete_context();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, const value_type& value) {
		return insert_node(pos, value);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, value_type&& value) {
		return insert_node(pos, value_type(value));
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, size_type count, const value_type& value) {
		return insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
		return insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
		const T* first = ilist.begin();
		const T* last = ilist.end();
		return insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos) {
		if (pos == cend()) {
			return pos;
		}
		return delete_node(pos);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last) {
		if (first == last) {
			return last;
		}

		ptr_node p_first = first.data();
		ptr_node p_last = last.data();
		ptr_node pre_p_first = p_first->prev;

		ptr_node first_next;
		while (p_first != p_last) {
			first_next = p_first->next;
			destory(p_first);
			deallocate(p_first);
			p_first = first_next;
		}
		relink(pre_p_first, p_first);
		return iterator(p_last);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(const value_type& value) {
		const_iterator p = cend();
		insert(p, value);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_back(value_type&& value) {
		const_iterator p = cend();
		insert(p, value_type(value));
	}

	template<class T, class Allocator>
	void list<T, Allocator>::pop_back() {
		iterator pos = end();
		--pos;
		erase(pos);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(const value_type& value) {
		const_iterator p = cbegin();
		insert(p, value);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::push_front(value_type&& value) {
		const_iterator p = cbegin();
		insert(p, value_type(value));
	}

	template<class T, class Allocator>
	void list<T, Allocator>::pop_front() {
		const_iterator pos = cbegin();
		erase(pos);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::resize(size_type count) {
		resize(count, value_type());
	}

	template<class T, class Allocator>
	void list<T, Allocator>::resize(size_type count, const value_type& value) {
		if (count > size()) {
			const_iterator p = cend();
			size_type add = count - size();
			insert(p, add, value);
		}
		else if (count < size()) {
			size_type add = size() - count;
			while (add != 0) {
				pop_back();
				--add;
			}
		}
		else
			return;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::swap(list& other) {
		if (this != &other) {
			std::swap(current, other.current);	
		}
	}

	template<class T, class Allocator>
	void list<T, Allocator>::merge(list& other) {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		merge(other, less);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::merge(list&& other) {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		merge(std::move(other), less);
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::merge(list& other, Compare comp) {
		if (other.empty()) {
			return;
		}
		ptr_node other_current = other.end().data();
		if (empty()) {
			ptr_node tmp = other_current;
			other_current = current;
			current = tmp;
			return;
		}

		ptr_node first1 = current->next;
		current->prev->next = nullptr;
		ptr_node first2 = other_current->next;
		other_current->prev->next = nullptr;

		first1 = merge_base(first1, first2, comp);
		ptr_node last1 = first1;
		while (last1->next != nullptr) {
			last1 = last1->next;
		}

		relink(current, first1);
		relink(last1, current);
		relink(other_current, other_current);
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::merge(list&& other, Compare comp) {
		if (other.empty()) {
			return;
		}
		ptr_node other_current = other.end().data();
		if (empty()) {
			ptr_node tmp = other_current;
			other_current = current;
			current = tmp;
			return;
		}

		ptr_node first1 = current->next;
		current->prev->next = nullptr;
		ptr_node first2 = other_current->next;
		other_current->prev->next = nullptr;

		first1 = merge_base(first1, first2, comp);
		ptr_node last1 = first1;
		while (last1->next != nullptr) {
			last1 = last1->next;
		}

		relink(current, first1);
		relink(last1, current);
		relink(other_current, other_current);
	}
	
	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other) {
		if (other.empty()) {
			return;
		}

		const_iterator first = other.cbegin();
		const_iterator last = other.cend();
		splice(pos, other, first, last);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other) {
		if (other.empty()) {
			return;
		}

		const_iterator first = other.cbegin();
		const_iterator last = other.cend();
		splice(pos, other, first, last);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator it) {
		const_iterator first = it;
		ptr_node it_ptr = it.data();
		const_iterator last = const_iterator(it_ptr->next);
		splice(pos, other, first, last);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other, const_iterator it) {
		const_iterator first = it;
		ptr_node it_ptr = it.data();
		const_iterator last = const_iterator(it_ptr->next);
		splice(pos, other, first, last);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
		ptr_node pos_ptr = pos.data();
		ptr_node first_ptr = first.data();
		ptr_node last_ptr = last.data();
		ptr_node pre_last_ptr = last_ptr->prev;
		//re_link in other
		relink(first_ptr->prev, last_ptr);
		//"insert"
		relink(pos_ptr->prev, first_ptr);
		relink(pre_last_ptr, pos_ptr);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::splice(const_iterator pos, list&& other, const_iterator first, const_iterator last) {
		ptr_node pos_ptr = pos.data();
		ptr_node first_ptr = first.data();
		ptr_node last_ptr = last.data();
		ptr_node pre_last_ptr = last_ptr->prev;
		//re_link in other
		relink(first_ptr->prev, last_ptr);
		//"insert"
		relink(pos_ptr->prev, first_ptr);
		relink(pre_last_ptr, pos_ptr);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::remove(const value_type& value) {
		auto it = begin();
		while (it != end()) {
			if (*it == value) {
				it = erase(it);
			}
			else {
				it++;
			}
		}
	}

	template<class T, class Allocator>
	template<class UnaryPredicate>
	void list<T, Allocator>::remove_if(UnaryPredicate p) {
		auto it = begin();
		while (it != end()) {
			if (p(*it)) {
				it = erase(it);
			}
			else {
				it++;
			}
		}
	}

	template<class T, class Allocator>
	void list<T, Allocator>::reverse() {
		ptr_node ptr = current;
		ptr_node ptr_next = ptr->next;
		while (ptr_next != current) {
			ptr_next = ptr->next;
			auto tmp = ptr->prev;
			ptr->prev = ptr->next;
			ptr->next = tmp;
			ptr = ptr_next;
		}
	}

	template<class T, class Allocator>
	void list<T, Allocator>::unique() {
		ptr_node first = current->next;
		while (first->next != current) {
			if (first->data == first->next->data) {
				delete_node(first->next);
			}
			else {
				first = first->next;
			}
		}
	}

	template<class T, class Allocator>
	template<class BinaryPredicate>
	void list<T, Allocator>::unique(BinaryPredicate p) {
		ptr_node first = current->next;
		while (first->next != current) {
			if (p(first->data, first->next->data)) {
				delete_node(first->next);
			}
			else {
				first = first->next;
			}
		}
	}

	template<class T, class Allocator>
	void list<T, Allocator>::sort() {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		sort(less);
	}

	template<class T, class Allocator>
	template<class Compare>
	void list<T, Allocator>::sort(Compare comp) {
		if (empty()) {
			return;
		}
		ptr_node first = current->next;
		current->prev->next = nullptr;

		first = merge_sort(first, comp);
		ptr_node last = first;
		while (last->next != nullptr) {
			last = last->next;
		}
		relink(current, first);
		relink(last, current);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::ptr_node list<T, Allocator>::allocate() {
		ptr_node n = data_alloc::allocate(1);
		return n;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::initialize() {
		current = allocate();
		node n;
		uninitialized_fill_n(current, 1, n);
		relink(current, current);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::deallocate(ptr_node p) {
		data_alloc::deallocate(p, 1);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::destory(ptr_node p) {
		data_alloc::destory(p);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::delete_data_and_memory() {
		if (current == nullptr) {
			return;
		}
		delete_context();
		destory(current);
		deallocate(current);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::delete_context() {
		ptr_node tmp = current->next;
		while (current->next != current) {
			delete_node(tmp);
			tmp = current->next;
		}
	}
	
	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type) {
		iterator it = pos;
		while (count != 0) {
			iterator it1 = insert_node(it, value);
			it = it1;
			count--;
		}
		return it;
	}
	
	template<class T, class Allocator>
	template<class InputIt>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type) {	
		auto it = last;
		iterator pos1 = pos;
		iterator pos2;
		while (it != first) {
			it--;
			pos2 = insert_node(pos1, value_type(*it));
			pos1 = pos2;
		}
		return pos2;
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert_node(const_iterator pos, const value_type& value) {
		ptr_node insert_node = allocate();
		node n;
		n.data = value;
		uninitialized_fill_n(insert_node, 1, n);

		ptr_node p_pos = pos.data();
		ptr_node pre_p_pos = p_pos->prev;
		relink(pre_p_pos, insert_node);
		relink(insert_node, p_pos);

		return iterator(insert_node);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::delete_node(iterator pos) {
		ptr_node p = pos.data();
		ptr_node pre = p->prev;
		ptr_node post = p->next;
		destory(p);
		deallocate(p);
		relink(pre, post);
		return iterator(post);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::delete_node(ptr_node p) {
		ptr_node pre = p->prev;
		ptr_node post = p->next;
		destory(p);
		deallocate(p);
		relink(pre, post);
	}

	template<class T, class Allocator>
	template<class Compare>
	typename list<T, Allocator>::ptr_node list<T, Allocator>::merge_sort(ptr_node first, Compare comp) {
		if (first->next == nullptr) {
			return first;
		}

		ptr_node slow = first;
		ptr_node fast = first;
		//find the middle
		while (fast != nullptr&&fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		//get two child lists
		slow->prev->next = nullptr;
		ptr_node first_ptr = merge_sort(first, comp);
		ptr_node second_ptr = merge_sort(slow, comp);
		return merge_base(first_ptr, second_ptr, comp);
	}

	template<class T, class Allocator>
	template<class Compare>
	typename list<T, Allocator>::ptr_node list<T, Allocator>::merge_base(ptr_node first1, ptr_node first2, Compare comp) {
		//end with nullptr, 
		ptr_node return_ptr;
		ptr_node tmp;
		//find the less value  
		if (comp(first2->data, first1->data)) {
			ptr_node ptr = first1;
			first1 = first2;
			first2 = ptr;
		}
		return_ptr = first1;
		tmp = first1;
		first1 = first1->next;

		//bidirectional
		while (first1 != nullptr && first2 != nullptr) {
			if (comp(first2->data, first1->data)) {
				relink(tmp, first2);
				tmp = tmp->next;
				first2 = first2->next;
			}
			else {
				relink(tmp, first1);
				tmp = tmp->next;
				first1 = first1->next;
			}
		}
		if (first1 != nullptr) {
			relink(tmp, first1);
		}
		if (first2 != nullptr) {
			relink(tmp, first2);
		}

		return return_ptr;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::relink(ptr_node first, ptr_node last) {
		first->next = last;
		last->prev = first;
	}



	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator==(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (; l_iterator != lhs.cend(); ++l_iterator, ++r_iterator) {
			if (*l_iterator != *r_iterator)
				return false;
		}
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator!=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<=(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!((*l_iterator == *r_iterator) || (*l_iterator < *r_iterator)))
				return false;
		}
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<(const list<T, Allocator>& lhs, const list<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!(*l_iterator < *r_iterator))
				return false;
		}
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
#endif // LIST_ALLOCATOR_

//NO ALLOCATOR
#ifndef LIST_ALLOCATOR_

	template<class T>
	class list {
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = ListIterator<T>;
		using const_iterator = const ListIterator<T>;
		using reverse_iterator = d_stl::reverse_iterator<iterator>;
		using const_reverse_iterator = d_stl::reverse_iterator<const_iterator>;
		using node = ListNode<T>;
		using ptr_node = ListNode<T>*;
		
	private:
		ptr_node current;

	public:
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

		//UB
		reference front() {
			return current->next->data;
		}

		const_reference front() const {
			return current->next->data;
		}

		reference back() {
			return current->prev->data;
		}

		const_reference back() const {
			return current->prev->data;
		}

		//Iterators
		iterator begin() noexcept {
			return iterator(current->next);
		}
		const_iterator begin() const noexcept {
			return const_iterator(current->next);
		}
		const_iterator cbegin() const noexcept {
			return const_iterator(current->next);
		}
		iterator end() noexcept {
			return iterator(current);
		}
		const_iterator end() const noexcept {
			return const_iterator(current);
		}
		const_iterator cend() const noexcept {
			return const_iterator(current);
		}

		reverse_iterator rbegin() noexcept {
			return reverse_iterator(current);
		}
		const_reverse_iterator rbegin() const noexcept {
			return const_reverse_iterator(current);
		}
		const_reverse_iterator crbegin() const noexcept {
			return const_reverse_iterator(current);
		}
		reverse_iterator rend() noexcept {
			return iterator(current->next);
		}
		const_reverse_iterator rend() const noexcept {
			return const_reverse_iterator(current->next);
		}
		const_reverse_iterator crend() const noexcept {
			return const_reverse_iterator(current->next);
		}

		//Capacity
		bool empty() const noexcept {
			return current->next == current;
		}
		size_type size() const noexcept {
			size_type i = 0;
			ptr_node pt = current->next;
			while (pt != current) {
				i++;
				pt = pt->next;
			}
			return i;
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
		// has been sorted into ascending order
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
		//just for consecutive duplicate elements
		void unique();
		template<class BinaryPredicate>
		void unique(BinaryPredicate p);
		//stable sort
		//merge sort
		void sort();
		template<class Compare>
		void sort(Compare comp);

	private:
		void initialize();//initialize the header
		void delete_data_and_memory();
		void delete_context();//reserve header

		iterator insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		iterator insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type);

		iterator insert_node(const_iterator pos, const value_type& value);
		iterator delete_node(iterator pos);
		void delete_node(ptr_node p);

		template<class Compare>
		ptr_node merge_sort(ptr_node first, Compare comp);
		template<class Compare>
		ptr_node merge_base(ptr_node first1, ptr_node first2, Compare comp);

		void relink(ptr_node first, ptr_node last);
		
	};

	template<class T>
	list<T>::list() {
		initialize();
	}

	template<class T>
	list<T>::list(size_type count) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value_type(), typename std::is_integral<size_type>::type());
	}

	template<class T>
	list<T>::list(size_type count, const value_type& value) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T>
	template<class InputIt>
	list<T>::list(InputIt first, InputIt last) {
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T>
	list<T>::list(const list& other) {
		initialize();
		const_iterator pos = cbegin();
		const_iterator first = other.begin();
		const_iterator last = other.end();
		insert_base(pos, first, last, typename std::is_integral<const_iterator>::type());
	}

	template<class T>
	list<T>::list(list&& other) {
		current = other.current;
		other.current = nullptr;
	}

	template<class T>
	list<T>::list(std::initializer_list<T> ilist) {
		initialize();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T>
	list<T>::~list() {
		delete_data_and_memory();
	}

	template<class T>
	list<T>& list<T>::operator=(const list& other) {
		if (this != &other) {
			delete_context();
			const_iterator pos = cbegin();
			const_iterator first = other.begin();
			const_iterator last = other.end();
			insert_base(pos, first, last, typename std::is_integral<const_iterator>::type());
		}
		return *this;
	}

	template<class T>
	list<T>& list<T>::operator=(list&& other) {
		if (this != &other) {
			delete_data_and_memory();
			current = other.current;
			other.current = nullptr;
		}
		return *this;
	}

	template<class T>
	list<T>& list<T>::operator=(std::initializer_list<T> ilist) {
		delete_context();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
		return *this;
	}

	template<class T>
	void list<T>::assign(size_type count, const value_type& value) {
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T>
	template<class InputIt>
	void list<T>::assign(InputIt first, InputIt last) {
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T>
	void list<T>::assign(std::initializer_list<T> ilist) {
		delete_context();
		const_iterator pos = cbegin();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T>
	void list<T>::clear() {
		delete_context();
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const_iterator pos, const value_type& value) {
		return insert_node(pos, value);
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const_iterator pos, value_type&& value) {
		return insert_node(pos, value_type(value));
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const_iterator pos, size_type count, const value_type& value) {
		return insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T>
	template<class InputIt>
	typename list<T>::iterator list<T>::insert(const_iterator pos, InputIt first, InputIt last) {
		return insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T>
	typename list<T>::iterator list<T>::insert(const_iterator pos, std::initializer_list<T> ilist) {
		const T* first = ilist.begin();
		const T* last = ilist.end();
		return insert_base(pos, first, last, typename std::is_integral<const T*>::type());
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(const_iterator pos) {
		if (pos == cend()) {
			return pos;
		}
		return delete_node(pos);
	}

	template<class T>
	typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
		if (first == last) {
			return last;
		}

		ptr_node p_first = first.data();
		ptr_node p_last = last.data();
		ptr_node pre_p_first = p_first->prev;

		ptr_node first_next;
		while (p_first != p_last) {
			first_next = p_first->next;
			delete p_first;
			p_first = first_next;
		}
		relink(pre_p_first, p_first);
		return iterator(p_last);
	}

	template<class T>
	void list<T>::push_back(const value_type& value) {
		const_iterator p = cend();
		insert(p, value);
	}

	template<class T>
	void list<T>::push_back(value_type&& value) {
		const_iterator p = cend();
		insert(p, value_type(value));
	}

	template<class T>
	void list<T>::pop_back() {
		iterator pos = end();
		--pos;
		erase(pos);
	}

	template<class T>
	void list<T>::push_front(const value_type& value) {
		const_iterator p = cbegin();
		insert(p, value);
	}

	template<class T>
	void list<T>::push_front(value_type&& value) {
		const_iterator p = cbegin();
		insert(p, value_type(value));
	}

	template<class T>
	void list<T>::pop_front() {
		const_iterator pos = cbegin();
		erase(pos);
	}

	template<class T>
	void list<T>::resize(size_type count) {
		resize(count, value_type());
	}

	template<class T>
	void list<T>::resize(size_type count, const value_type& value) {
		if (count > size()) {
			const_iterator p = cend();
			size_type add = count - size();
			insert(p, add, value);
		}
		else if (count < size()) {
			size_type add = size() - count;
			while (add != 0) {
				pop_back();
				--add;
			}
		}
		else
			return;
	}

	template<class T>
	void list<T>::swap(list& other) {
		if (this != &other) {
			std::swap(current, other.current);
		}
	}

	template<class T>
	void list<T>::merge(list& other) {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		merge(other, less);
	}

	template<class T>
	void list<T>::merge(list&& other) {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		merge(std::move(other), less);
	}

	template<class T>
	template<class Compare>
	void list<T>::merge(list& other, Compare comp) {
		if (other.empty()) {
			return;
		}
		ptr_node other_current = other.end().data();
		if (empty()) {
			ptr_node tmp = other_current;
			other_current = current;
			current = tmp;
			return;
		}

		ptr_node first1 = current->next;
		current->prev->next = nullptr;
		ptr_node first2 = other_current->next;
		other_current->prev->next = nullptr;

		first1 = merge_base(first1, first2, comp);
		ptr_node last1 = first1;
		while (last1->next != nullptr) {
			last1 = last1->next;
		}

		relink(current, first1);
		relink(last1, current);
		relink(other_current, other_current);
	}

	template<class T>
	template<class Compare>
	void list<T>::merge(list&& other, Compare comp) {
		if (other.empty()) {
			return;
		}
		ptr_node other_current = other.end().data();
		if (empty()) {
			ptr_node tmp = other_current;
			other_current = current;
			current = tmp;
			return;
		}

		ptr_node first1 = current->next;
		current->prev->next = nullptr;
		ptr_node first2 = other_current->next;
		other_current->prev->next = nullptr;

		first1 = merge_base(first1, first2, comp);
		ptr_node last1 = first1;
		while (last1->next != nullptr) {
			last1 = last1->next;
		}

		relink(current, first1);
		relink(last1, current);
		relink(other_current, other_current);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list& other) {
		if (other.empty()) {
			return;
		}
		const_iterator first = other.cbegin();
		const_iterator last = other.cend();
		splice(pos, other, first, last);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list&& other) {
		if (other.empty()) {
			return;
		}
		const_iterator first = other.cbegin();
		const_iterator last = other.cend();
		splice(pos, other, first, last);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list& other, const_iterator it) {
		const_iterator first = it;
		ptr_node it_ptr = it.data();
		const_iterator last = const_iterator(it_ptr->next);
		splice(pos, other, first, last);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list&& other, const_iterator it) {
		const_iterator first = it;
		ptr_node it_ptr = it.data();
		const_iterator last = const_iterator(it_ptr->next);
		splice(pos, other, first, last);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
		ptr_node pos_ptr = pos.data();
		ptr_node first_ptr = first.data();
		ptr_node last_ptr = last.data();
		ptr_node pre_last_ptr = last_ptr->prev;
		//re_link in other
		relink(first_ptr->prev, last_ptr);
		//"insert"
		relink(pos_ptr->prev, first_ptr);
		relink(pre_last_ptr, pos_ptr);
	}

	template<class T>
	void list<T>::splice(const_iterator pos, list&& other, const_iterator first, const_iterator last) {
		ptr_node pos_ptr = pos.data();
		ptr_node first_ptr = first.data();
		ptr_node last_ptr = last.data();
		ptr_node pre_last_ptr = last_ptr->prev;
		//re_link in other
		relink(first_ptr->prev, last_ptr);
		//"insert"
		relink(pos_ptr->prev, first_ptr);
		relink(pre_last_ptr, pos_ptr);
	}

	template<class T>
	void list<T>::remove(const value_type& value) {
		auto it = begin();
		while (it != end()) {
			if (*it == value) {
				it = erase(it);
			}
			else {
				it++;
			}
		}
	}

	template<class T>
	template<class UnaryPredicate>
	void list<T>::remove_if(UnaryPredicate p) {
		auto it = begin();
		while (it != end()) {
			if (p(*it)) {
				it = erase(it);
			}
			else {
				it++;
			}
		}
	}

	template<class T>
	void list<T>::reverse() {
		ptr_node ptr = current;
		ptr_node ptr_next = ptr->next;
		while (ptr_next != current) {
			ptr_next = ptr->next;
			auto tmp = ptr->prev;
			ptr->prev = ptr->next;
			ptr->next = tmp;
			ptr = ptr_next;
		}
	}

	template<class T>
	void list<T>::unique() {
		ptr_node first = current->next;
		while (first->next != current) {
			if (first->data == first->next->data) {
				delete_node(first->next);
			}
			else {
				first = first->next;
			}
		}
	}

	template<class T>
	template<class BinaryPredicate>
	void list<T>::unique(BinaryPredicate p) {
		ptr_node first = current->next;
		while (first->next != current) {
			if (p(first->data, first->next->data)) {
				delete_node(first->next);
			}
			else {
				first = first->next;
			}
		}
	}

	template<class T>
	void list<T>::sort() {
		auto less = [](const value_type& lhs, const value_type& rhs) {
			return lhs < rhs;
		};
		sort(less);
	}

	template<class T>
	template<class Compare>
	void list<T>::sort(Compare comp) {
		if (empty()) {
			return;
		}
		ptr_node first = current->next;
		current->prev->next = nullptr;

		first = merge_sort(first, comp);
		ptr_node last = first;
		while (last->next != nullptr) {
			last = last->next;
		}
		relink(current, first);
		relink(last, current);

	}

	template<class T>
	void list<T>::initialize() {
		current = new node;
		relink(current, current);
	}

	template<class T>
	void list<T>::delete_data_and_memory() {
		if (current == nullptr) {
			return;
		}
		delete_context();
		delete current;
	}

	template<class T>
	void list<T>::delete_context() {	
		ptr_node tmp = current->next;
		while (current->next != current) {
			delete_node(tmp);
			tmp = current->next;
		}
	}

	template<class T>
	typename list<T>::iterator list<T>::insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type) {
		iterator it = pos;
		while (count != 0) {
			iterator it1 = insert_node(it, value);
			it = it1;
			count--;
		}
		return it;
	}

	template<class T>
	template<class InputIt>
	typename list<T>::iterator list<T>::insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type) {
		auto it = last;
		iterator pos1 = pos;
		iterator pos2;
		while (it != first) {
			it--;
			pos2 = insert_node(pos1, value_type(*it));
			pos1 = pos2;
		}
		return pos2;
	}

	template<class T>
	typename list<T>::iterator list<T>::insert_node(const_iterator pos, const value_type& value) {
		
		ptr_node insert_node = new node;
		insert_node->data = value;

		ptr_node p_pos = pos.data();
		ptr_node pre_p_pos = p_pos->prev;
		relink(pre_p_pos, insert_node);
		relink(insert_node, p_pos);

		return iterator(insert_node);
	}

	template<class T>
	typename list<T>::iterator list<T>::delete_node(iterator pos) {
		ptr_node p = pos.data();
		ptr_node pre = p->prev;
		ptr_node post = p->next;
		delete p;
		relink(pre, post);
		return iterator(post);
	}

	template<class T>
	void list<T>::delete_node(ptr_node p) {
		ptr_node pre = p->prev;
		ptr_node post = p->next;
		delete p;
		relink(pre, post);
	}

	template<class T>
	template<class Compare>
	typename list<T>::ptr_node list<T>::merge_sort(ptr_node first, Compare comp) {
		if (first->next == nullptr) {
			return first;
		}

		ptr_node slow = first;
		ptr_node fast = first;
		//find the middle
		while (fast != nullptr&&fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;
		}
		//get two child lists
		slow->prev->next = nullptr;
		ptr_node first_ptr = merge_sort(first, comp);
		ptr_node second_ptr = merge_sort(slow, comp);
		return merge_base(first_ptr, second_ptr, comp);
	}

	template<class T>
	template<class Compare>
	typename list<T>::ptr_node list<T>::merge_base(ptr_node first1, ptr_node first2, Compare comp) {
		//end with nullptr, 
		ptr_node return_ptr;
		ptr_node tmp;
		//find the less value  
		if (comp(first2->data, first1->data)) {
			ptr_node ptr = first1;
			first1 = first2;
			first2 = ptr;
		}
		return_ptr = first1;
		tmp = first1;
		first1 = first1->next;

		//bidirectional
		while (first1 != nullptr && first2 != nullptr) {
			if (comp(first2->data, first1->data)) {
				relink(tmp, first2);
				tmp = tmp->next;
				first2 = first2->next;
			}
			else {
				relink(tmp, first1);
				tmp = tmp->next;
				first1 = first1->next;
			}
		}
		if (first1 != nullptr) {
			relink(tmp, first1);
		}
		if (first2 != nullptr) {
			relink(tmp, first2);
		}

		return return_ptr;
	}

	template<class T>
	void list<T>::relink(ptr_node first, ptr_node last) {
		first->next = last;
		last->prev = first;
	}


	template<class T>
	bool operator==(const list<T>& lhs, const list<T>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (; l_iterator != lhs.cend(); ++l_iterator, ++r_iterator) {
			if (*l_iterator != *r_iterator)
				return false;
		}
		return true;
	}

	template<class T>
	bool operator!=(const list<T>& lhs, const list<T>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class T>
	bool operator<=(const list<T>& lhs, const list<T>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!((*l_iterator == *r_iterator) || (*l_iterator < *r_iterator)))
				return false;
		}
		return true;
	}

	template<class T>
	bool operator<(const list<T>& lhs, const list<T>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!(*l_iterator < *r_iterator))
				return false;
		}
		return true;
	}

	template<class T>
	bool operator>=(const list<T>& lhs, const list<T>& rhs) {
		return (!operator<(lhs, rhs));
	}

	template<class T>
	bool operator>(const list<T>& lhs, const list<T>& rhs) {
		return (!operator<=(lhs, rhs));
	}

#endif // !LIST_ALLOCATOR_
}
#endif 
