#ifndef D_VECTOR_H_
#define D_VECTOR_H_

typedef std::ptrdiff_t difference_type;
#include <cstddef> //ptrdiff_t, size_t
#include <stdexcept> //throw
#include <initializer_list>
#include "iterator.h"
#include "memory.h"

namespace d_stl {
	template<class T, class Allocator = d_stl::allocator<T>>
	class vector;

	template<class T>
	bool operator==(const vector<T>& lhs, const vector<T>& rhs);
	template<class T>
	bool operator!=(const vector<T>& lhs, const vector<T>& rhs);
	template<class T>
	bool operator<=(const vector<T>& lhs, const vector<T>& rhs);
	template<class T>
	bool operator<(const vector<T>& lhs, const vector<T>& rhs);
	template<class T>
	bool operator>=(const vector<T>& lhs, const vector<T>& rhs);
	template<class T>
	bool operator>(const vector<T>& lhs, const vector<T>& rhs);

	template<class T, class Allocator = d_stl::allocator<T>>
	class vector {
	private:
		T* begin_;
		T* end_;
		T* stroage_;
		typedef Allocator data_alloc;

	public:
		typedef T value_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T* iterator;
		typedef const T* const_iterator;
		typedef d_stl::reverse_iterator<iterator> reverse_iterator;
		typedef d_stl::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit vector(size_type count);
		explicit vector(size_type count, size_type T& value);
		template<class InputIt>
		vector(InputIt first, InputIt last);
		vector(const vector& other);
		vector(vector&& other);
		vector(std::initializer_list<T> init);
		~vector();

		vector& operator=(const vector& other);
		vector& operator=(vector&& other);
		vector& operator=(std::initializer_list<T> init);

		void assign(size_type count, size_type T& value);
		template<class InputIt>
		void assign(InputIt first, InputIt last);
		void assign(std::initializer_list<T> init);

		//bound checking
		reference at(size_type pos) {
			if (size() <= pos)
				throw std::out_of_range("out_of_range");
			return *(begin_ + pos);
		}
		const_reference at(size_type pos) const {
			if (size() <= pos)
				throw std::out_of_range("out_of_range");
			return *(begin_ + pos);
		}
		//no bound checking
		reference operator[](size_type pos) {
			return *(begin_ + pos);
		}
		const_reference operator[](size_type pos) const {
			return *(begin_ + pos);
		}
		//empty UB
		reference front() {
			return *begin_;
		}
		const_reference front() const {
			return *begin_;
		}
		reference back() {
			return *(end_ - 1);
		}
		const_reference back() const {
			return *(end_ - 1);
		}

		T* data() noexcept {
			return begin_;
		}
		const T* data() const noexcept {
			return begin_;
		}

		iterator begin() noexcept {
			return begin_;
		}
		const_iterator begin() const noexcept {
			return begin_;
		}
		const_iterator cbegin() const noexcept {
			return begin_;
		}
		iterator end() noexcept {
			return end_;
		}
		iterator end() const noexcept {
			return end_;
		}
		const_iterator cend() const noexcept {
			return end_;
		}

		reverse_iterator rbegin() noexcept {
			return reverse_iterator(end_ - 1);
		}
		const_reverse_iterator rbegin() const noexcept {
			return reverse_iterator(end_ - 1);
		}
		const_reverse_iterator crbegin() const noexcept {
			return const_reverse_iterator(end_ - 1);
		}
		reverse_iterator rend() noexcept {
			return reverse_iterator(begin_ - 1);
		}
		const_reverse_iterator rend() const noexcept {
			return reverse_iterator(begin_ - 1);
		}		
		const_reverse_iterator crend() const noexcept {
			return const_reverse_iterator(begin_ - 1);
		}

		bool empty() const noexcept {
			return begin_ == end_;
		}
		size_type size() const noexcept {
			return end_ - begin_;
		}

		void reserve(size_type new_cap); //reserve stroage
		size_type capacity() const noexcept {
			return stroage_ - begin_;
		}
		void shrink_to_fit(); //removed unused capacity 

		void clean() noexcept;
		iterator insert(const_iterator pos, const T& value); // return the first element inserted
		iterator insert(const_iterator pos, T&& value);
		iterator insert(const_iterator pos, size_type count, const T& value);
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> init);
		iterator erase(const_iterator pos); //return the following removed element
		iterator erase(const_iterator first, const_iterator last);
		void push_back(const T& value);
		void push_back(T&& value);
		void pop_back();
		void resize(size_type count);
		void resize(size_type count, const value_type& value);
		void swap(vector& other) noexcept; //exchange contents, no move, copy etc.
		
	private:
		

	public:
		friend bool operator==<T>(const vector<T>& lhs, const vector<T>& rhs);
		friend bool operator!=<T>(const vector<T>& lhs, const vector<T>& rhs);
		friend bool operator<=<T>(const vector<T>& lhs, const vector<T>& rhs);
		friend bool operator<<T>(const Vector<T>& lhs, const Vector<T>& rhs);
		friend bool operator>=<T>(const vector<T>& lhs, const vector<T>& rhs);
		friend bool operator><T>(const vector<T>& lhs, const vector<T>& rhs);
	};


}
#endif 
