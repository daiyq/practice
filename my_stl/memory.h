#ifndef D_MEMORY_
#define D_MEMORY_
//that includes smart pointer, allocator
#include <cstddef> //size_t
#include <utility> //std::forward
#include <new>
#include <exception>
#include "alloc.h"

namespace d_stl {

	//the definition of allocator<T>, used as a interface
	//memory processing agent functions
	template<class T>
	class allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

	public:
		static T* allocate(std::size_t n);
		static void deallocate(T* p, std::size_t n);
		template<typename...Args>
		static void construct(T* p, Args&&...args);
		static void destory(T* p);

	};

	template<class T>
	T* allocator<T>::allocate(std::size_t n) {
		if (n == 0)return nullptr;
		return static_cast<T*>(alloc::allocate(sizeof(T)*n));
	}

	template<class T>
	void allocator<T>::deallocate(T* p, std::size_t n) {
		if (n == 0)return;
		alloc::deallocate(static_cast<void*>(p), sizeof(T)*n);
	}

	template<class T>
	template<typename...Args>
	void allocator<T>::construct(T* p, Args&&...args) {
		//placement new
		//place!!
		//non_allocating placement allocation function
		//below are placement new too
		::new ((void*)p)T(std::forward<Args>(args)...);
	}

	template<class T>
	void allocator<T>::destory(T* p) {
		p->~T();
	}

	//companion algorithm
	//not make use of POD
	template<class InputIt, class ForwardIt>
	ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first) {
		typedef typename d_stl::iterator_traits<ForwardIt>::value_type Value;
		ForwardIt current = d_first;
		try {
			for (; first != last; ++first, ++current) {
				//placement new
				::new (static_cast<void*>(&(*current))) Value(*first);
			}
			return current;
		}
		catch (std::exception& e) {
			for (; d_first != current; ++d_first) {
				d_first->~Value();
			}
			throw;
		}
	}

	template<class InputIt, class Size, class ForwardIt>
	ForwardIt uninitialized_copy_n(InputIt first, Size count, ForwardIt d_first) {
		typedef typename d_stl::iterator_traits<ForwardIt>::value_type Value;
		ForwardIt current = d_first;
		try {
			for (; count > 0; ++first, ++current, --count) {
				::new (static_cast<void*>(&(*current))) Value(*first);
			}	
		}
		catch (std::exception& e) {
			for (; d_first != current; ++d_first) {
				d_first->~Value();
			}
			throw;
		}
		return current;
	}

	template<class ForwardIt, class T>
	void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value) {
		typedef typename d_stl::iterator_traits<ForwardIt>::value_type Value;
		ForwardIt current = first;
		try {
			for (; current != last; ++current) {
				::new (static_cast<void*>(&(*current))) Value(value);
			}
		}
		catch (std::exception& e) {
			for (; first != current; ++first) {
				first->~Value();
			}
			throw;
		}
	}

	template<class ForwardIt, class Size, class T>
	ForwardIt uninitialized_fill_n(ForwardIt first, Size count, const T& value) {
		typedef typename d_stl::iterator_traits<ForwardIt>::value_type Value;
		ForwardIt current = first;
		try {
			for (; count > 0; ++current, --count) {
				//placement new
				::new (static_cast<void*>(&(*current))) Value(value);
			}
			return current;
		}
		catch (std::exception& e) {
			for (; first != current; ++first) {
				d_first->~Value();
			}
			throw;
		}
	}

	//smart_pointers

}
#endif 

