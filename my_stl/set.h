#ifndef D_SET_H_
#define D_SET_H_

#include "rb_tree.h"
#include "memory.h"
#include "iterator.h"
#include "functional.h"
//#include <functional> //std::less<>
#include <initializer_list>
#include <utility>//pair, std::swap, std::move(), std::forward()

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
		
		using KeyOfValue = d_stl::identify_set<value_type>;

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
		d_stl::rb_tree<Key, Key, KeyOfValue, Compare, Allocator> t;

		
	};
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set() :t() {
	}

	template<class Key, class Compare, class Allocator>
	template<class InputIt>
	set<Key, Compare, Allocator>::set(InputIt first, Input last) : t() {
		for (; first != last; first++) {
			t.insert(*first);
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(const set& other) :t(other.t) {
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(set&& other) {
		if (this != &other) {
			t(std::move(other.t));
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::set(std::initializer_list<value_type> ilist) {
		const value_type* first = ilist.begin();
		const value_type* last = ilist.end();
		for (; first != last; first++) {
			t.insert(*first);
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::~set() {
		t.~rb_tree();
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(const set& other) {
		if (this != &other) {
			t = other.t;
		}
		return *this;
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(set&& other) {
		if (this != &other) {
			t = std::move(other.t);
		}
		return *this;
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(std::initializer_list<value_type> ilist) {
		t.clean_tree();
		const value_type* first = ilist.begin();
		const value_type* last = ilist.end();
		for (; first != last; first++) {
			t.insert(*first);
		}
		return *this;
	}

	template<class Key, class Compare, class Allocator>
	bool set<Key, Compare, Allocator>::empty() const {
		return t.empty();
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::size() const {
		return t.size();
	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::clear() {
		t.clean_tree();
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::insert(const value_type& value) {
		//return type
		t.insert(value);
	}
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::insert(value_type&& value) {
		//return type
		t.insert(value);
	}

	template<class Key, class Compare, class Allocator>
	template<class InputIt>
	void set<Key, Compare, Allocator>::insert(InputIt first, InputIt last) {
		for (; first != last; first++) {
			t.insert(*first);
		}
	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::insert(std::initializer_list<value_type> ilist) {
		const value_type* first = ilist.begin();
		const value_type* last = ilist.end();
		for (; first != last; first++) {
			t.insert(*first);
		}
	}

	template<class Key, class Compare, class Allocator>
	template<class...Args>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::emplace(Args&&...args) {
		value_type tmp = std::forward<Args>(args);
		if (find(KeyOfValue()(tmp)) == end()) {
			//return type
			insert(tmp);

		}
		else {
			return end();
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::erase(const_iterator pos) {
		t.erase(KeyOfValue()(*pos));
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::erase(const_iterator first, const_iterator last) {
		for (; first != last; first++) {
			t.erase(KeyOfValue()(*first));
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::erase(const key_type& key) {
		t.erase(key);
	}

	template<class Key, class Compare, class Allocator>
	void set<Key, Compare, Allocator>::swap(set& other) {
		t.swap(other);
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::size_type set<Key, Compare, Allocator>::count(const Key& key) const {
		if (find(key) == end()) {
			return 0;
		}
		else {
			return 1;
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::find(const Key& key) {
		pointer tmp = t.find(key);
		if (tmp == nullptr) {
			return end();
		}
		else {
			return iterator(tmp);
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::find(const Key& key) const {
		const_pointer tmp = t.find(key);
		if (tmp == nullptr) {
			return end();
		}
		else {
			return const_iterator(tmp);
		}
	}
	
	template<class Key, class Compare, class Allocator>
	pair<set<Key, Compare, Allocator>::iterator, set<Key, Compare, Allocator>::iterator> set<Key, Compare, Allocator>::
		equal_range(const Key& key) {
		pair<iterator, iterator> p;
		pointer tmp = t.find_lower_bound(key);
		if (tmp->value == value_type(key)) {
			iterator first = iterator(tmp);	
		}
		else {
			iterator first = ++iterator(tmp);;
		}
		iterator second = ++iterator(tmp);
		return p(first, second);
	}

	template<class Key, class Compare, class Allocator>
	pair<set<Key, Compare, Allocator>::const_iterator, set<Key, Compare, Allocator>::const_iterator> set<Key, Compare, Allocator>::
		equal_range(const Key& key) const {
		pair<const_iterator, const_iterator> p;
		pointer tmp = t.find_lower_bound(key);
		if (tmp->value == value_type(key)) {
			const_iterator first = const_iterator(tmp);
		}
		else {
			const_iterator first = ++const_iterator(tmp);;
		}
		const_iterator second = ++const_iterator(tmp);
		return p(first, second);
	}
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::lower_bound(const Key& key) {
		pointer tmp = t.find_lower_bound(key);
		if (tmp->value == value_type(key)) {
			return iterator(tmp);
		}
		else {
			return ++iterator(tmp);
		}
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::lower_bound(const Key& key) const {
		const_pointer tmp = t.find_lower_bound(key);
		if (tmp->value == value_type(key)) {
			return const_iterator(tmp);
		}
		else {
			return ++const_iterator(tmp);
		}
	}
	
	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::iterator set<Key, Compare, Allocator>::upper_bound(const Key& key) {
		pointer tmp = t.find_lower_bound(key);
		return ++iterator(tmp);
	}

	template<class Key, class Compare, class Allocator>
	set<Key, Compare, Allocator>::const_iterator set<Key, Compare, Allocator>::upper_bound(const Key& key) const {
		const_pointer tmp = t.find_lower_bound(key);
		return ++const_iterator(tmp);
	}


	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
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
	
	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!(*l_iterator < *r_iterator))
				return false;
		}
		return true;
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		auto l_iterator = lhs.cbegin();
		auto r_iterator = rhs.cbegin();
		for (std::size_t i = 0; i < size; ++i, ++l_iterator, ++r_iterator) {
			if (!((*l_iterator == *r_iterator) || (*l_iterator < *r_iterator)))
				return false;
		}
		return true;
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!operator<=(lhs, rhs));
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc>& lhs, const set<Key, Compare, Alloc>& rhs) {
		return (!operator<(lhs, rhs));
	}

	template<class Key, class Compare = std::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Key>>>
	void swap(set<Key, Compare, Allocator>& lhs, set<Key, Compare, Allocator>& rhs) {
		lhs.swap(rhs);
	}

}
#endif 