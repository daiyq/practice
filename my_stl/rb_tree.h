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
		using self = rb_tree_iterator<Value>;

		rb_tree_iterator(const node& n) :root(n) {
		}

		const node data()const {
			return root;
		}

		self& operator=(const self& other) {
			if (this != &other) {
				root = other.data();
			}
			return *this;
		}

		reference operator*() const {
			return root.value;
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			increment();
			return *this;
		}
		self& operator--() {
			decrement();
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			self tmp = *this;
			increment();
			return tmp;
		}
		self operator--(int) {
			self tmp = *this;
			decrement();
			return tmp;
		}

	private:
		node root;
		void increment();
		void decrement();
	};
	
	template<class Value>
	void rb_tree_iterator<Value>::increment() {

	}

	template<class Value>
	void rb_tree_iterator<Value>::decrement() {

	}
	
	template<class Key,class Value,class Compare=std::less<Key>,class Allocate=d_stl::allocator<rb_tree_node<Value>>>
	class rb_tree {



	};
		
}
#endif 
