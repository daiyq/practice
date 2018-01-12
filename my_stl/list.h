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
		using ptr_node = ListNode<T>*;
		ptr_node prev;
		ptr_node next;
		T data;
	};

	template<class ListItem>
	class ListIterator :public d_stl::bidirectional_iterator<ListItem, std::ptrdiff_t> {
	public:
		using iterator_category = bidirectional_iterator_tag;
		using value_type = ListItem;
		using difference_type = std::ptrdiff_t;
		using pointer = ListItem*;
		using reference = ListItem&;
		using self = ListIterator<ListItem>;
		using node = ListNode<ListItem>;
		using ptr_node = node*;

	private:
		ptr_node current;

	public:
		ListIterator() :current(nullptr) {
		}
		ListIterator(const ptr_node& item) :current(item) {
		}
		ListIterator(const self& it) :current(it.current) {
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
				current = other.current;
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
	bool operator==(const ListIterator<ListItem>& lhs, const ListIterator<ListItem>& rhs) {
		return (lhs.current == rhs.current);
	}

	template<class ListItem>
	bool operator!=(const ListIterator<ListItem>& lhs, const ListIterator<ListItem>& rhs) {
		return (lhs.current != rhs.current);
	}

	template<class T, class Allocator=d_stl::allocator<ListNode<T>>>
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
			while (current->next != current) {
				i++;
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

	private:
		ptr_node allocate(size_type size);
		void initialize();//initialize the header
		//void deallocate(ptr_node p, size_type size);
		void deallocate(ptr_node p);
		void destory(ptr_node p);
		void delete_data_and_memory();
		void delete_context();//reserve header
		
		/*
		void list_base(size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		void list_base(InputIt first, InputIt last, std::false_type);
		
		void assign_base(size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		void assign_base(InputIt first, InputIt last, std::false_type);
		*/

		iterator insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		iterator insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type);

		iterator insert_node(const_iterator pos, const value_type& value);
		void delete_node(ptr_node p);
	};

	template<class T,class Allocator>
	list<T, Allocator>::list() {
		//list_base(0, value_type(), typename std::is_integral<size_type>::type());
		initialize();
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count) {
		//list_base(count, value_type(), typename std::is_integral<size_type>::type());
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value_type(), typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(size_type count, const value_type& value) {
		//list_base(count, value, typename std::is_integral<size_type>::type());
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	list<T, Allocator>::list(InputIt first, InputIt last) {
		//list_base(first, last, typename std::is_integral<InputIt>::type());
		initialize();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	list<T, Allocator>::list(const list& other) {
		//const_iterator tmp_first = other.begin();
		//const_iterator tmp_end = other.end();
		//list_base(tmp_first, tmp_end, typename std::is_integral<const_iterator>::type());
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
	}

	template<class T, class Allocator>
	list<T, Allocator>::~list() {
		delete_data_and_memory();
	}

	template<class T, class Allocator>
	list<T, Allocator>& list<T, Allocator>::operator=(const list& other) {
		if (this != &other) {
			/*
			delete_data_and_memory();
			const_iterator tmp_first = other.begin();
			const_iterator tmp_end = other.end();
			list_base(tmp_first, tmp_end, typename std::is_integral<const_iterator>::type());
			*/
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
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(size_type count, const value_type& value) {
		//assign_base(count, value, typename std::is_integral<size_type>::type());
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	void list<T, Allocator>::assign(InputIt first, InputIt last) {
		//assign_base(first, last, typename std::is_integral<InputIt>::type());
		delete_context();
		const_iterator pos = cbegin();
		insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	void list<T, Allocator>::assign(std::initializer_list<T> ilist) {
	}

	template<class T, class Allocator>
	void list<T, Allocator>::clear() {
		delete_context();
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, const value_type& value) {
		//return insert_base(pos, 1, value, typename std::is_integral<size_type>::type());
		return insert_node(pos, value);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::insert(const_iterator pos, value_type&& value) {
		//return insert_base(pos, 1, value_type(value), typename std::is_integral<size_type>::type());
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
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator pos) {
		const_iterator post_pos = pos;
		++post_pos;
		erase(pos, post_pos);
	}

	template<class T, class Allocator>
	typename list<T, Allocator>::iterator list<T, Allocator>::erase(const_iterator first, const_iterator last) {

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
		const_iterator pos = cend();
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


	template<class T, class Allocator>
	typename list<T, Allocator>::ptr_node list<T, Allocator>::allocate(size_type size) {
		ptr_node n = data_alloc::allocate(size);
		return n;
	}

	template<class T, class Allocator>
	void list<T, Allocator>::initialize() {
		current = allocate(1);
		node n;
		uninitialized_fill_n(current, 1, n);
		current->prev = current;
		current->next = current;
	}

	/*
	template<class T, class Allocator>
	void list<T, Allocator>::deallocate(ptr_node p, size_type size) {
		data_alloc::deallocate(p, size);
	}
	*/

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
		//deallocate(current, 1);
		deallocate(current);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::delete_context() {
		/*
		ptr_node tmp = current->next;
		while (current->next != current) {
			current->next = tmp->next;
			destory(tmp);
			deallocate(tmp, 1);

			tmp = current->next;
		}
		current->prev = current;
		*/
		ptr_node tmp = current->next;
		while (current->next != current) {
			delete_node(tmp);
			tmp = current->next;
		}
	}


	//allocate a array for initialize list, but something is wrong with initialization
	//maybe memory distributed?
	//so, allocate one by one
	//size_type size = static_cast<size_type>(d_stl::distance(first, last));
	/*
	size_type size = 0;
	auto it = first;
	while (it != last) {
	it++;
	size += 1;
	}

	ptr_node insert_node = allocate(size);
	node n;
	uninitialized_fill_n(insert_node, size, n);

	ptr_node tmp = insert_node;
	for (std::size_t i = 0; i < size - 1; i++) {
	tmp->data = *first;
	++first;

	tmp->next = tmp + 1;
	tmp->next->prev = tmp;
	++tmp;
	}

	//ptr_node p_pos = pos.current;
	ptr_node p_pos = pos.data();
	ptr_node pre_p_pos = p_pos->prev;
	pre_p_pos->next = insert_node;
	insert_node->prev = pre_p_pos;
	tmp->next = p_pos;
	p_pos->prev = tmp;

	return iterator(insert_node);
	*/
	/*
	template<class T, class Allocator>
	void list<T, Allocator>::list_base(size_type count, const value_type& value, std::true_type) {
		
		initialize();
		if (count == 0) {
			return;
		}
		
		iterator it = begin();
		while (count != 0) {
			iterator it1 = insert_node(it, value);
			it = it1;
			count--;
		}
		
	}
	
	template<class T, class Allocator>
	template<class InputIt>
	void list<T, Allocator>::list_base(InputIt first, InputIt last, std::false_type) {
		
		initialize();
		
		auto it = last;
		iterator pos1 = begin();
		iterator pos2;
		while (it != first) {
			it--;
			pos2 = insert_node(pos1, value_type(*it));
			pos1 = pos2;
		}
		
	}
	*/
	

	/*
	template<class T, class Allocator>
	void list<T, Allocator>::assign_base(size_type count, const value_type& value, std::true_type) {
		delete_data_and_memory();
		list_base(count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	void list<T, Allocator>::assign_base(InputIt first, InputIt last, std::false_type) {
		delete_data_and_memory();
		list_base(first, last, typename std::is_integral<InputIt>::type());
	}
	*/

	
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
		ptr_node insert_node = allocate(1);
		node n;
		n.data = value;
		uninitialized_fill_n(insert_node, 1, n);

		ptr_node p_pos = pos.data();
		ptr_node pre_p_pos = p_pos->prev;
		pre_p_pos->next = insert_node;
		insert_node->prev = pre_p_pos;
		insert_node->next = p_pos;
		p_pos->prev = insert_node;

		return iterator(insert_node);
	}

	template<class T, class Allocator>
	void list<T, Allocator>::delete_node(ptr_node p) {
		ptr_node pre = p->prev;
		ptr_node post = p->next;
		destory(p);
		deallocate(p);
		pre->next = post;
		post->prev = pre;
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

}
#endif 
