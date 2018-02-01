#ifndef D_RB_TREE_H_
#define D_RE_TREE_H_

#include "iterator.h"
#include "memory.h"
#include "functional.h" //std::less<>
#include <utility> //std::move() std::swap()

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

	template<class Key, class Value, class KeyOfValue = d_stl::identify<Value>, class Compare = d_stl::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Value>>>
	class rb_tree;

	template<class Key, class Value, class KeyOfValue = d_stl::identify<Value>, class Compare = d_stl::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Value>>>
	void swap(rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs, rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs);

	template<class Key, class Value, class KeyOfValue = d_stl::identify<Value>, class Compare = d_stl::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Value>>>
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

		friend void swap(rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs, rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs);
	private:
		//use of header:
		//use it as border checking node
		//root's parent is header
		//header's parent is nullptr
		//and header's left and right are itself
		ptr_node header;

	private:
		ptr_node creat_node();
		ptr_node creat_node(const value_type& value);
		ptr_node copy_node(ptr_node p);
		void delete_node(ptr_node p);
		void initialize();

		void clean();

		ptr_node find_base(ptr_node p, const key_type& key);
		ptr_node insert_base(ptr_node p, const value_type& value);
		ptr_node erase_base(ptr_node p, key_type key);

		size_type size_base(ptr_node p);

		ptr_node erase_min(ptr_node p);
		ptr_node erase_max(ptr_node p);

		ptr_node balance(ptr_node p);

		bool is_red(ptr_node p) {
			if (p == nullptr) {
				return false;
			}
			return p->color == re_tree_node_red;
		}

		//deal with the parent ptr_node
		ptr_node rotate_left(ptr_node p);
		ptr_node rotate_right(ptr_node p);
		void flip_color(ptr_node p);

	};

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rb_tree() {
		initialize();
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rb_tree(const rb_tree& other) {

	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rb_tree(rb_tree&& other) {
		if (this != &other) {
			header = other.header;
			other.header = nullptr;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::~rb_tree() {

	}

	//copy and swap
	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		operator=(rb_tree other) {
		swap(other);
		return *this;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		begin() {
		if (empty()) {
			return end();
		}
		ptr_node root = header->parent;
		while (root->left != nullptr) {
			root = root->left;
		}
		return iterator(root);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		end() {
		return iterator(header);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	bool rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::empty() {
		if (header->parent == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		size() {
		if (empty()) {
			return 0;
		}
		else {
			return size_base(header->parent);
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		find(const key_type& key) {
		return find_base(header->parent, key);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(const value_type& value) {
		insert_base(header->parent, KeyOfValue()(value), value);
		header->parent->color = re_tree_node_black;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const key_type& key) {
		
		erase_base(header->parent, key);
		if (!empty()) {
			header->parent->color = re_tree_node_black;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::swap(rb_tree& other) {
		if (this != other&) {
			std::swap(header, other.header);
		}
	}

	//private function
	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		creat_node() {
		return creat_node(value_type());
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		creat_node(const value_type& value) {
		ptr_node creat_node = data_alloc::allocate(1);
		node n;
		n.value = value;
		n.color = re_tree_node_red;
		uninitialized_fill_n(creat_node, 1, n);
		return creat_node;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		copy_node(ptr_node p) {
		ptr_node creat_node = data_alloc::allocate(1);
		node n;
		n.value = p->value;
		n.color = p->color;
		uninitialized_fill_n(creat_node, 1, n);
		return creat_node;
	}

	//for delete one node every time,
	//so not worry the memory, it would be sized as when allocated
	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::delete_node(ptr_node p) {
		data_alloc::destory(p);
		data_alloc::deallocate(p, 1);
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::initialize() {
		header = creat_node();
		header->left = header;
		header->right = header;
		header->parent = nullptr;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::clean() {
		
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		find_base(ptr_node p, const key_type& key) {
		if (p == nullptr) {
			return nullptr
		}
		//equal
		else if (!Compare()(key, KeyOfValue()(p->value)) && !Compare()(KeyOfValue()(p->value), key)) {
			return p;
		}
		//less
		else if (Compare()(key, KeyOfValue()(p->value))) {
			return find_base(p->left, key);
		}
		else {
			return find_base(p->right, key);
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		insert_base(ptr_node p, const value_type& value) {
		if (p == nullptr) {
			return creat_node(value);
		}

		//equal
		if (!Compare()(KeyOfValue()(value), KeyOfValue()(p->value)) && !Compare()(KeyOfValue()(p->value), KeyOfValue()(value))) {
			p->value = value;
		}
		//less
		else if (Compare()(KeyOfValue()(value), KeyOfValue()(p->value))) {
			return insert_base(p->left, value);
		}
		else {
			return insert_base(p->right, value);
		}

		if (is_red(p->right) && !is_red(p->left)) {
			p = rotate_left(p);
		}
		if (is_red(p->left) && is_red(p->left->left)) {
			p = rotate_right(p);
		}
		if (is_red(p->right) && is_red(p->left)) {
			flip_color(p);
		}
		return p;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		erase_base(ptr_node p, key_type key) {
	
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		size_base(ptr_node p) {
		if (p == nullptr) {
			return 0;
		}
		else {
			return size_base(p->left) + size_base(p->right) + 1;
		}
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		erase_min(ptr_node p) {
	
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		erase_max(ptr_node p) {
	
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		balance(ptr_node p) {
	
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		rotate_left(ptr_node p) {
		ptr_node p_parent = p->parent;
		ptr_node x = p->right;
		p->right = x->left;
		x->left = p;
		//the parent ptr_node
		p->parent = x;
		x->parent = p_parent;

		x->color = p->color;
		p->color = re_tree_node_red;
		return x;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::ptr_node rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::
		rotate_right(ptr_node p) {
		ptr_node p_parent = p->parent;
		ptr_node x = p->left;
		p->left = x->right;
		x->right = p;
		//the parent ptr_node
		p->parent = x;
		x->parent = p_parent;

		x->color = p->color;
		p->color = re_tree_node_red;
		return x;
	}

	template<class Key, class Value, class KeyOfValue, class Compare, class Allocator>
	void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::flip_color(ptr_node p) {
		p->color = re_tree_node_red;
		p->left->color = re_tree_node_black;
		p->right->color = re_tree_node_black;
	}

	
	template<class Key, class Value, class KeyOfValue = d_stl::identify<Value>, class Compare = d_stl::less<Key>, class Allocator = d_stl::allocator<rb_tree_node<Value>>>
	void swap(rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& lhs, rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rhs) {
		lhs.swap(rhs);
	}
}
#endif 
