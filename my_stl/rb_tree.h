#ifndef D_RB_TREE_H_
#define D_RE_TREE_H_

#include "iterator.h"
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
	
	//when current is root, its parent is nullptr
	template<class Value>
	void rb_tree_iterator<Value>::precursor() {
		if (current->left != nullptr) {
			current = current->left;
			while (current->right != nullptr) {
				current = current->right;
			}
		}
		else if (current->parent == nullptr) {
			//root, and left child is nullptr
		}
		else {
			ptr_node tmp = current;//reserve current
			ptr_node parent = current->parent;
			while (parent->left == current) {
				current = parent;
				parent = parent->parent;
			}
			if (parent != nullptr) {
				current = parent;
			}
			else {
				//current is max, so next is itself
				//use of reserved tmp;
				current = tmp;
			}
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
		else if (current->parent == nullptr) {
			//root, and right child is nullptr
		}
		else {
			ptr_node tmp = current;//reserve current
			ptr_node parent = current->parent;
			while (parent->right == current) {
				current = parent;
				parent = parent->parent;
			}
			if (parent != nullptr) {
				current = parent;
			}
			else {
				//current is max, so next is itself
				//use of reserved tmp;
				current = tmp;
			}
		}
	}
	
	template<class Key,class Value,class Compare=std::less<Key>,class Allocate=d_stl::allocator<rb_tree_node<Value>>>
	class rb_tree {
	public:
		using key_type = Key;
		using value_type = Key;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using key_compare = Compare;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;

		using node = rb_tree_node<Value>;
		using ptr_node = node*;

		void insert(const value_type& value);

	private:
		ptr_node root;

		ptr_node creat_node();

	};
		
}
#endif 
