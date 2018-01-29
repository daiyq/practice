#ifndef D_SET_H_
#define D_SET_H_

#include "rb_tree.h"
#include "memory.h"
#include "iterator.h"
#include <functional> //std::less<>
#include <initializer_list>
#include <utility>//pair

namespace d_stl {

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
		using pointer = value_type*;
		using const_pointer = const value_type*;
		//using pointer = rb_tree_node<Key>*;
		//using const_pointer = const rb_tree_node<Key>*;

		using iterator = const rb_tree_iterator<value_type>;
		using const_iterator = const rb_tree_iterator<value_type>;
		using reverse_iterator = d_stl::reverse_iterator<iterator>;
		using const_reverse_iterator = d_stl::reverse_iterator<const_iterator>;
		
		//member function
		set() {}
		set(const value_type& value);
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
		void insert(std::initializer_list<T> ilist);
		template<class...Args>
		iterator emplace(Args&&...args);//directly construct
		iterator erase(const_iterator pos); //return the following removed element
		iterator erase(const_iterator first, const_iterator last);
		size_type erase(const key_type& value);
		void swap(set& other);

		//lookup
		size_type count(const Key& key);
		iterator find(const Key& key);
		const_iterator find(const Key& key) const;
		std::pair<iterator, iterator> equal_range(const Key& key);
		std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
		//the first element that is not less than the key
		iterator lower_bound(const Key& key);
		const_iterator lower_bound(const Key& key) const;
		//the first element that is greater than the key
		iterator upper_bound(const Key& key);
		const_iterator upper_bound(const Key& key) const;

	private:
		d_stl::rb_tree<Key, Key, Compare, Allocator> rb_set;

	};
	
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
}
#endif 