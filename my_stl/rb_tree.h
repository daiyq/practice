#ifndef D_RB_TREE_H_
#define D_RE_TREE_H_

#include "iterator.h"
#include "memory.h"
#include <functional> //std::less<>

namespace d_stl {

	using color_type = bool;
	const color_type re_tree_node_red = true;
	const color_type re_tree_node_black = false;

	template<class Value>
	class rb_tree_node {
	public:
		using ptr_node = rb_tree_node<Value>*;

		Value value;
		//the reason of existence of "parent" is iterator
		ptr_node parent;
		ptr_node left;
		ptr_node right;
		color_type color;
	};



	template<class Value>
	class rb_tree_iterator :public bidirectional_iterator<Value, std::ptrdiff_t> {
	public:
		using iterator_category = bidirectional_iterator_tag;
		using value_type = Value;
		using difference_type = std::ptrdiff_t;
		using pointer = Value*;
		using reference = Value&;

		using node = rb_tree_node<Value>;
		using ptr_node = node*;
		using self = rb_tree_iterator<Value>;

		rb_tree_iterator(const node& n) :current(n) {
		}

		const ptr_node data()const {
			return current;
		}

		self& operator=(const self& other) {
			if (this != &other) {
				current = other.data();
			}
			return *this;
		}

		reference operator*() const {
			return current.value;
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			precursor();
			return *this;
		}
		self& operator--() {
			successor();
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			self tmp = *this;
			precursor();
			return tmp;
		}
		self operator--(int) {
			self tmp = *this;
			successor();
			return tmp;
		}

	private:
		ptr_node current;
		void precursor();
		void successor();
	};


	template<class Value>
	void rb_tree_iterator<Value>::precursor() {
		if (current->left != nullptr) {
			current = current->left;
			while (current->right != nullptr) {
				current = current->right;
			}
		}
		else {
			ptr_node parent = current->parent;
			while (parent->left == current) {
				current = parent;
				parent = parent->parent;
			}
			//use of header
			current = parent;
		}
	}

	template<class Value>
	void rb_tree_iterator<Value>::successor() {
		if (current->right != nullptr) {
			current = current->right;
			while (current->left != nullptr) {
				current = current->left;
			}
		}
		else {
			ptr_node parent = current->parent;
			while (parent->right == current) {
				current = parent;
				parent = parent->parent;
			}
			//use of header
			current = parent;
		}
	}

	template<class Key, class Value, class Compare = std::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Value>>>
	class rb_tree {
	public:
		using key_type = Key;
		using value_type = Value;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using key_compare = Compare;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = rb_tree_iterator<Value>;
		using const_iterator = const rb_tree_iterator<Value>;

		using node = rb_tree_node<Value>;
		using ptr_node = node*;
		using data_alloc = Allocator;

		rb_tree();
		rb_tree(const rb_tree& other);
		rb_tree(rb_tree&& other);
		~rb_tree();

		rb_tree& operator=(rb_tree other);

		iterator begin();
		iterator end();
		
		bool empty();
		size_type size();

		ptr_node find(const key_type& key);
		void insert(const value_type& value);
		void erase(const key_type& key);

		void swap(rb_tree& other);

	private:
		//use of header:
		//use it as border checking node
		//header's parent is root
		//root's parent is header
		//and header's left and right are itself
		ptr_node header;

	private:
		ptr_node creat_node();
		ptr_node copy_node(ptr_node p);
		void delete_node(ptr_node p);
		void initialize();

		void clean();

		ptr_node find_base(ptr_node p, const key_type& key);
		ptr_node insert_base(ptr_node p, key_type key, value_type value);
		ptr_node erase_base(ptr_node p, key_type key);

		ptr_node erase_min(ptr_node p);
		ptr_node erase_max(ptr_node p);

		ptr_node balance(ptr_node p);
		ptr_node rotate_left(ptr_node p);
		ptr_node rotate_right(ptr_node p);
		void flip_color(ptr_node p);

		void root_normalize();

	};

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::rb_tree() {
		initialize();
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::rb_tree(const rb_tree& other) {

	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::rb_tree(rb_tree&& other) {
		if (this != &other) {
			header = other.header;
			other.header = nullptr;
		}
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::~rb_tree() {

	}

	//copy and swap
	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>& rb_tree<Key, Value, Compare, Allocator>::operator=(rb_tree other) {
		swap(other);
		return *this;
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::iterator rb_tree<Key, Value, Compare, Allocator>::begin() {
		if (empty()) {
			return end();
		}
		ptr_node root = header->parent;
		while (root->left != nullptr) {
			root = root->left;
		}
		return iterator(root);
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::iterator rb_tree<Key, Value, Compare, Allocator>::end() {
		return iterator(header);
	}

	template<class Key, class Value, class Compare, class Allocator>
	bool rb_tree<Key, Value, Compare, Allocator>::empty() {
		if (header->parent == header) {
			return true;
		}
		else {
			return false;
		}
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::size_type rb_tree<Key, Value, Compare, Allocator>::size() {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::find(const key_type& key) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::insert(const value_type& value) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::erase(const key_type& key) {

	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::swap(rb_tree& other) {

	}

	//private function
	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::creat_node() {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::copy_node(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::delete_node(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::initialize() {
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::clean() {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::find_base(ptr_node p, const key_type& key) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::insert_base(ptr_node p, key_type key, value_type value) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::erase_base(ptr_node p, key_type key) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::erase_min(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::erase_max(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::balance(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::rotate_left(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	rb_tree<Key, Value, Compare, Allocator>::ptr_node rb_tree<Key, Value, Compare, Allocator>::rotate_right(ptr_node p) {
	
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::flip_color(ptr_node p) {
	}

	template<class Key, class Value, class Compare, class Allocator>
	void rb_tree<Key, Value, Compare, Allocator>::root_normalize() {

	}
}
#endif 
