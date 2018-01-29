#ifndef D_RB_TREE_H_
#define D_RE_TREE_H_

namespace d_stl {

	using color_type = bool;
	const color_type re_tree_node_red = true;
	const color_type re_tree_node_black = false;

	template<class Value>
	class rb_tree_node {
	public:
		using ptr_node = rb_tree_node<Value>*;

		color_type color;
		ptr_node left;
		ptr_node right;
		Value value;

	};
		
}
#endif 
