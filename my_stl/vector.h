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

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);

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

		vector();
		explicit vector(size_type count);
		vector(size_type count, size_type T& value);
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
		//as below, but not initilized begin_, end_ and stroage_
		void delete_data_and_memory();
		//if the stroage  is not big enough
		void reallocated(std::size_t need_size);
		

	public:
		friend bool operator==<T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
		friend bool operator!=<T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
		friend bool operator<=<T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
		friend bool operator<<T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
		friend bool operator>=<T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
		friend bool operator><T>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs);
	};

	//错误地点，两个模板参数都要写全，即使是有默认模板参数，也要写全！！
	//construction etc.
	template<class T, class Allocator>
	vector<T, Allocator>::vector() :begin_(nullptr), end_(nullptr), stroage_(nullptr) {}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count) {
		begin_ = data_alloc::allocate(count);
		end_ = begin_ + count;
		stroage_ = begin_ + (((sizeof(T)*count + 7) / 8) * 8) / sizeof(T);
		uninitialized_fill_n(begin_, count, T());
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count, size_type T& value) {
		begin_ = data_alloc::allocate(count);
		end_ = begin_ + count;
		stroage_ = begin_ + (((sizeof(T)*count + 7) / 8) * 8) / sizeof(T);
		uninitialized_fill_n(begin_, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	vector<T, Allocator>::vector(InputIt first, InputIt last) {
		auto count = distance(first, last);
		begin_ = data_alloc::allocate(count);
		end_ = begin_ + count;
		stroage_ = begin_ + (((sizeof(T)*count + 7) / 8) * 8) / sizeof(T);
		uninitialized_copy(first, last, begin_);
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(const vector& other) {
		auto count = other.size();
		begin_ = data_alloc::allocate(count);
		end_ = begin_ + count;
		stroage_ = begin_ + (((sizeof(T)*count + 7) / 8) * 8) / sizeof(T);
		uninitialized_copy(other.begin(), other.end(), begin_);
	}
	
	template<class T, class Allocator>
	vector<T, Allocator>::vector(vector&& other) {
		begin_ = other.begin();
		end_ = other.end();
		stroage_ = begin_ + other.capacity();
		other.begin_ = other.end_ = other.stroage_ = nullptr;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(std::initializer_list<T> init) {

	}

	template<class T, class Allocator>
	vector<T, Allocator>::~vector() {
		delete_data_and_memory();
	}
	
	
	//function about value assignment
	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
		if (this != &other) {
			if (capacity() < other.size()) {
				reallocated(other.size());
			}
			uninitialized_copy(other.begin(), other.end(), begin_);
		}
		return *this;
	}

	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(vector&& other) {
		if (this != &other) {
			delete_data_and_memory();
			begin_ = other.begin();
			end_ = other.end();
			stroage_ = begin_ + other.capacity();
			other.begin_ = other.end_ = other.stroage_ = nullptr;
		}
		return *this;
	}

	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> init) {

	}

	template<class T, class Allocator>
	void vector<T, Allocator>::assign(size_type count, size_type T& value) {
		if (capacity() < count) {
			reallocated(count);
		}
		uninitialized_fill_n(begin_, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void vector<T, Allocator>::assign(InputIt first, InputIt last) {
		auto count = distance(first, last);
		if (capacity() < count) {
			reallocated(count);
		}
		uninitialized_copy(first, last, begin_);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::assign(std::initializer_list<T> init) {

	}

	//functions about size
	template<class T, class Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity())
			return;
		T* t_begin_ = data_alloc::allocate(new_cap);
		T* t_end_ = t_begin_ + new_cap;
		T* t_stroage_ = t_begin_ + (((sizeof(T)*new_cap + 7) / 8) * 8) / sizeof(T);

		uninitialized_copy(begin_, end_, t_begin_);
		delete_data_and_memory();
		begin_ = t_begin_;
		end_ = t_end_;
		stroage_ = t_stroage_;
	}
	
	template<class T, class Allocator>
	void vector<T, Allocator>::shrink_to_fit() {
		data_alloc::deallocate(end_, stroage_ - end_);
		stroage_ = end_;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::clean() {
		data_alloc::destory(begin_, end_);
	}

	//insert, push, pop
	
	//
	template<class T, class Allocator>
	void vector<T, Allocator>::delete_data_and_memory() {
		data_alloc::destory(begin_, end_);
		data_alloc::deallocate(begin_, capacity());
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::reallocated(std::size_t need_size) {
		T* t_begin_ = data_alloc::allocate(need_size);
		T* t_end_ = t_begin_ + need_size;
		T* t_stroage_ = t_begin_ + (((sizeof(T)*need_size + 7) / 8) * 8) / sizeof(T);

		delete_data_and_memory();
		begin_ = t_begin_;
		end_ = t_end_;
		stroage_ = t_stroage_;
	}
}
#endif 
