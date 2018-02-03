#ifndef D_SET_H_
#define D_SET_H_

#include "rb_tree.h"
#include "memory.h"
#include "iterator.h"
#include "functional.h"
//#include <functional> //std::less<>
#include <initializer_list>
#include <utility>//pair, std::swap

namespace d_stl {

	template<class Key, class Compare = std::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Key>>>
	class set;

	template<class Key, class Compare = std::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Key>>>
	void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs);

	template<class Key,class Compare=std::less<Key>,class Allocator=d_stl::allocator<rb_tree_node<Key>>>
	class set {
	public:
		using key_type = Key;
		using value_type = Key;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using key_compare = Compare;
		using value_compare = Compare;
		using reference = value_type&;
		using const_reference = const value_type&;
		//using pointer = value_type*;
		//using const_pointer = const value_type*;
		//using pointer=Allocator::pointer
		using pointer = rb_tree_node<Key>*;
		using const_pointer = const rb_tree_node<Key>*;

		using iterator = const rb_tree_iterator<value_type>;//same as rb_tree
		using const_iterator = const rb_tree_iterator<value_type>;
		using reverse_iterator = d_stl::reverse_iterator<iterator>;
		using const_reverse_iterator = d_stl::reverse_iterator<const_iterator>;
		
		//member function
		set();
		template<class InputIt>
		set(InputIt first, Input last);
		set(const set& other);
		set(set&& other);
		set(std::initializer_list<value_type> ilist);
		~set();

		set& operator=(const set& other);
		set& operator=(set&& other);
		set& operator=(std::initializer_list<value_type> ilist);

		//iterator
		iterator begin() noexcept {

		}
		const_iterator begin() const noexcept {
			
		}
		const_iterator cbegin() const noexcept {
			
		}
		iterator end() noexcept {
			
		}
		const_iterator end() const noexcept {
			
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

		//capacity
		bool empty() const;
		size_type size() const;

		//modifiers
		void clear();
		iterator insert(const value_type& value); // return the element inserted
		iterator insert(value_type&& value);
		template<class InputIt>
		void insert(InputIt first, InputIt last);
		void insert(std::initializer_list<value_type> ilist);
		//directly construct, and inserted if there is no equal key
		//which can avoid unnecessary copy or move operations
		template<class...Args>
		iterator emplace(Args&&...args);
		iterator erase(const_iterator pos); //return the following removed element
		iterator erase(const_iterator first, const_iterator last);
		size_type erase(const key_type& key);
		void swap(set& other);

		//lookup
		size_type count(const Key& key) const;
		iterator find(const Key& key);
		const_iterator find(const Key& key) const;
		//return type whose the first iterator pointing to the first element not less than the key, 
		//the second iterator pointing to the first element greater than the key
		pair<iterator, iterator> equal_range(const Key& key);
		pair<const_iterator, const_iterator> equal_range(const Key& key) const;
		//the first element that is not less than the key
		iterator lower_bound(const Key& key);
		const_iterator lower_bound(const Key& key) const;
		//the first element that is greater than the key
		iterator upper_bound(const Key& key);
		const_iterator upper_bound(const Key& key) const;

		friend void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs);

	private:
		d_stl::rb_tree<Key, Key, d_stl::identify_set<value_type>, Compare, Allocator> rb_set;

		
	};
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set() {

	}

	template<class Key, class Compare, class Allocator>
	template<class InputIt>
	set<Key, Compare, Allocator>::set(InputIt first, Input last) {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(const set& other) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(set&& other) {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(std::initializer_list<value_type> ilist) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::~set() {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(const set& other) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(set&& other) {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(std::initializer_list<value_type> ilist) {
	
	}

	template<class Key, class Compare, class Allocator>
	bool set<Key, Compare, Allocator>::empty() const {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::size() const {

	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::clear() {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::insert(const value_type& value) {

	}
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::insert(value_type&& value) {
	
	}

	template<class Key, class Compare, class Allocator>
	template<class InputIt>
	void set<Key, Compare, Allocator>::insert(InputIt first, InputIt last) {
	
	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::insert(std::initializer_list<value_type> ilist) {

	}

	template<class Key, class Compare, class Allocator>
	template<class...Args>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::emplace(Args&&...args) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::erase(const_iterator pos) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::erase(const_iterator first, const_iterator last) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::erase(const key_type& key) {
	
	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::swap(set& other) {

	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::count(const Key& key) const {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::find(const Key& key) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::find(const Key& key) const {
	
	}
	
	template<class Key, class Compare, class Allocator>
	pair<set<Key, Compare, Allocator>::iterator, set<Key, Compare, Allocator>::iterator> set<Key, Compare, Allocator>::
		equal_range(const Key& key) {

	}

	template<class Key, class Compare, class Allocator>
	pair<set<Key, Compare, Allocator>::const_iterator, set<Key, Compare, Allocator>::const_iterator> set<Key, Compare, Allocator>::
		equal_range(const Key& key) const {
	
	}
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::lower_bound(const Key& key) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::lower_bound(const Key& key) const {
	
	}
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::upper_bound(const Key& key) {
	
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::upper_bound(const Key& key) const {
	
	}


	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}
	
	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {

	}

	template<class Key, class Compare = std::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Key>>>
	void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs) {
		lhs.swap(rhs);
	}

}
#endif 