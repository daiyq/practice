#ifndef D_ITERATOR_
#define D_ITERATOR_

#include <cstddef> //size_t
#include <type_traits>

namespace d_stl {
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class T, class Distance> struct input_iterator
	{
		typedef input_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distance           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class T, class Distance> struct forward_iterator
	{
		typedef forward_iterator_tag iterator_category;
		typedef T                    value_type;
		typedef Distance             difference_type;
		typedef T*                   pointer;
		typedef T&                   reference;
	};

	template <class T, class Distance> struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template <class T, class Distance> struct random_access_iterator
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category			iterator_category;
		typedef T                   value_type;
		typedef Distance            difference_type;
		typedef Pointer             pointer;
		typedef Reference           reference;
	};

	template<class,class=void>
	struct iterator_traits_base {
		//primary template handles types that have no nested ::type member
	};
	
	//specialization recognizes
	//pay attention to meaning of void_t
	template<class Iterator>
	struct iterator_traits_base<Iterator, std::void_t<
		typename Iterator::iterator_category,
		typename Iterator::value_type,
		typename Iterator::difference_type,
		typename Iterator::pointer,
		typename Iterator::reference
		>>
	{
		using iterator_category = typename Iterator::iterator_category;
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;
	};

	//An iterator traits which value_type is always the vlau_type
	template <class Iterator>
	struct iterator_traits : iterator_traits_base<Iterator>
	{
		
	};

	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef ptrdiff_t                  difference_type;
		typedef const T*                   pointer;
		typedef const T&                   reference;
	};



	template<class InputIt>
	typename iterator_traits<InputIt>::difference_type
		distance(InputIt first, InputIt last) {
		typename iterator_traits<InputIt>::difference_type distance = 0;
		if (typename iterator_traits<InputIt>::iterator_category == random_access_iterator_tag) {
			return (last - first);
		}
		for (; first != last; first++) {
			distance++;
		}
		return distance;
	}
	

	template<class Iterator>
	class reverse_iterator {
	private:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef Iterator iterator_type;
		typedef reverse_iterator<Iterator> self;

		reverse_iterator();
		explicit reverse_iterator(Iterator it);
		template<class U>
		reverse_iterator(const reverse_iterator<U>& other);
		template<class U>
		reverse_iterator& operator=(const reverse_iterator<U>& other);

		Iterator base() const {
			return current;
		}

		reference operator*() const {
			Iterator tmp = current;
			return *--tmp;
		}
		pointer operator->() const {
			return &(operator*());
		}

		//pre, return *this
		self& operator++() {
			--current;
			return *this;
		}
		self& operator--() {
			++current;
			return *this;
		}
		//post, return a copy
		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}
		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}

		self operator+(difference_type n) const {
			return self(current - n);
		}
		self operator-(difference_type n) const {
			return self(current + n);
		}
		self& operator+=(difference_type n) const {
			current -= n;
			return *this;
		}
		self& operator-=(difference_type n) const {
			current += n;
			return *this;
		}

	};

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator() {}

	template<class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(Iterator it) :current(it) {}

	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>::reverse_iterator(const reverse_iterator<U>& other) : current(other.base()) {}

	template<class Iterator>
	template<class U>
	reverse_iterator<Iterator>& reverse_iterator<Iterator>::operator=(const reverse_iterator<U>& other) {
		current = other.base();
	}
	
}
#endif