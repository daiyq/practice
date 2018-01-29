#ifndef D_SET_H_
#define D_SET_H_

#include "rb_tree.h"
#include "memory.h"
#include <functional> //std::less<>

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
		using pointer = rb_tree_node<Key>*;
		using const_pointer = const rb_tree_node<Key>*;

		using iterator = 
		using const_iterator=const 


	};
}
#endif 