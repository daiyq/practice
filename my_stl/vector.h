#ifndef D_VECTOR_H_
#define D_VECTOR_H_

#include <cstdio>
#include <cstdlib>
#include <cstddef> //ptrdiff_t, size_t
#include <stdexcept> //throw
#include <initializer_list>
#include <type_traits>
//#include <algorithm>
#include "iterator.h"
#include <iterator> //distance()
#include "memory.h"
#include "algorithm.h"

namespace d_stl {


	template<class T, class Allocator = d_stl::allocator<T>>
	class vector {
	public:
		using value_type = T;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = value_type*;
		using const_pointer = const value_type*;
		using iterator = value_type*;
		using const_iterator = const value_type*;
		using reverse_iterator = d_stl::reverse_iterator<iterator>;
		using const_reverse_iterator = d_stl::reverse_iterator<const_iterator>;
		using data_alloc = Allocator;

	private:
		T* begin_;
		T* end_;
		T* stroage_;
	
	public:
		//Member functions
		vector();
		explicit vector(size_type count);
		vector(size_type count, const value_type& value);
		template<class InputIt>
		vector(InputIt first, InputIt last);
		vector(const vector& other);
		vector(vector&& other);
		vector(std::initializer_list<T> ilist);
		~vector();


		vector& operator=(const vector& other);
		vector& operator=(vector&& other);
		vector& operator=(std::initializer_list<T> ilist);

		void assign(size_type count, const value_type& value);
		template<class InputIt>
		void assign(InputIt first, InputIt last);
		void assign(std::initializer_list<T> ilist);

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

		//Iterators
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
		const_iterator end() const noexcept {
			return end_;
		}
		const_iterator cend() const noexcept {
			return end_;
		}

		reverse_iterator rbegin() noexcept {
			return reverse_iterator(end_);
		}
		const_reverse_iterator rbegin() const noexcept {
			return reverse_iterator(end_);
		}
		const_reverse_iterator crbegin() const noexcept {
			return const_reverse_iterator(end_);
		}
		reverse_iterator rend() noexcept {
			return reverse_iterator(begin_);
		}
		const_reverse_iterator rend() const noexcept {
			return reverse_iterator(begin_);
		}
		const_reverse_iterator crend() const noexcept {
			return const_reverse_iterator(begin_);
		}

		//Capacity
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
		void shrink_to_fit(); //removed unused capacity. useless?? where to use? and difficult to inplement

		//Modifiers
		void clear();
		iterator insert(const_iterator pos, const value_type& value); // return the first element inserted
		iterator insert(const_iterator pos, value_type&& value);
		iterator insert(const_iterator pos, size_type count, const value_type& value);
		template<class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last);
		iterator insert(const_iterator pos, std::initializer_list<T> ilist);//not finished
		iterator erase(const_iterator pos); //return the following removed element
		iterator erase(const_iterator first, const_iterator last);
		void push_back(const value_type& value);
		void push_back(value_type&& value);
		void pop_back();
		void resize(size_type count);
		void resize(size_type count, const value_type& value);
		void swap(vector& other); //exchange contents, no move, copy etc.


	private:
		//allocate memory, initialize begin_, end_ and stroage_
		T* allocate(size_type size);
		void ininitialized(size_type size);
		void deallocate(T* p, size_type n);

		void destory(T* first, T* last);
		void delete_data_and_memory();
		//clean, reallocate memory, initialize begin_, end_ and stroage_
		//but not construct
		void reallocate_and_desert(size_type need_size);
		void reallocate_and_preserve(size_type need_size);

		
		void vector_base(size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		void vector_base(InputIt first, InputIt last, std::false_type);
		
		void assign_base(size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		void assign_base(InputIt first, InputIt last, std::false_type);
		
		iterator insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type);
		template<class InputIt>
		iterator insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type);
	};

	//错误地点，两个模板参数都要写全，即使是有默认模板参数，也要写全！！
	//construction etc.
	template<class T, class Allocator>
	vector<T, Allocator>::vector() :begin_(nullptr), end_(nullptr), stroage_(nullptr) {
		//std::printf("blank\n");
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count) {
		//std::printf("only number\n");
		ininitialized(count);
		uninitialized_fill_n(begin_, count, T());
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(size_type count, const value_type& value) {	
		vector_base(count, value, typename std::is_integral<size_type>::type());
	}
	
	template<class T, class Allocator>
	template<class InputIt>
	vector<T, Allocator>::vector(InputIt first, InputIt last) {
		vector_base(first, last, typename std::is_integral<InputIt>::type());
	}
	
	template<class T, class Allocator>
	vector<T, Allocator>::vector(const vector& other) {
		const_iterator first = other.cbegin();
		const_iterator last = other.cend();
		vector_base(first, last, typename std::is_integral<const_iterator>::type());
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(vector&& other) {
		begin_ = other.begin();
		end_ = other.end();
		stroage_ = begin_ + other.capacity();
		other.begin_ = other.end_ = other.stroage_ = nullptr;
	}

	template<class T, class Allocator>
	vector<T, Allocator>::vector(std::initializer_list<T> ilist) {
		const T* first = ilist.begin();
		const T* last = ilist.end();
		vector_base(first, last, typename std::is_integral<const T*>::type());
	}

	template<class T, class Allocator>
	vector<T, Allocator>::~vector() {
		delete_data_and_memory();
	}


	//function about value assignment
	template<class T, class Allocator>
	vector<T, Allocator>& vector<T, Allocator>::operator=(const vector& other) {
		if (this != &other) {
			delete_data_and_memory();
			const_iterator first = other.cbegin();
			const_iterator last = other.cend();
			vector_base(first, last, typename std::is_integral<const_iterator>::type());
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
	vector<T, Allocator>& vector<T, Allocator>::operator=(std::initializer_list<T> ilist) {
		delete_data_and_memory();
		const T* first = ilist.begin();
		const T* last = ilist.end();
		vector_base(first, last, typename std::is_integral<const T*>::type());
		return *this;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::assign(size_type count, const value_type& value) {
		assign_base(count, value, typename std::is_integral<size_type>::type());
	}

	template<class T, class Allocator>
	template<class InputIt>
	void vector<T, Allocator>::assign(InputIt first, InputIt last) {
		assign_base(first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::assign(std::initializer_list<T> ilist) {
		const T* first = ilist.begin();
		const T* last = ilist.end();
		assign_base(first, last, typename std::is_integral<const T*>::type());
	}

	//functions about size
	template<class T, class Allocator>
	void vector<T, Allocator>::reserve(size_type new_cap) {
		if (new_cap <= capacity())
			return;
		/*
		T* t_begin_ = allocate(new_cap);
		T* t_end_ = t_begin_ + new_cap;
		T* t_stroage_ = t_begin_ + (((sizeof(T)*new_cap + 7) / 8) * 8) / sizeof(T);

		uninitialized_copy(begin_, end_, t_begin_);
		delete_data_and_memory();
		begin_ = t_begin_;
		end_ = t_end_;
		stroage_ = t_stroage_;
		*/
		reallocate_and_preserve(new_cap);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::shrink_to_fit() {
		/*
		*/
		//to  be normailzed 
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::clear() {
		destory(begin_, end_);
		end_ = begin_;
	}

	//insert, push, pop
	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, const value_type& value) {
		return insert_base(pos, 1, value, typename std::is_integral<size_type>::type());
		/*
		size_type dis = static_cast<size_type>(distance(cbegin(), pos));
		if (end_ == stroage_) {
			size_type new_size = 2 * size();
			T* t_begin_ = allocate(new_size);
			T* t_end_ = t_begin_ + size() + 1;
			T* t_stroage_ = t_begin_ + (((sizeof(T)*new_size + 7) / 8) * 8) / sizeof(T);

			uninitialized_copy(cbegin(), pos, t_begin_);
			uninitialized_fill_n(t_begin_ + dis, 1, value);
			uninitialized_copy(pos, cend(), t_begin_ + dis + 1);

			delete_data_and_memory();
			begin_ = t_begin_;
			end_ = t_end_;
			stroage_ = t_stroage_;
			return iterator(begin_ + dis);
		}
		else {
			if (pos == cend()) {
				uninitialized_fill_n(end_, 1, value);
			}
			else {
				uninitialized_copy(end_ - 1, end_, end_ + 1);
				copy_backward(begin_ + dis, end_ - 1, end_);
				*(begin_ + dis) = value;
			}
			end_++;
			return iterator(begin_ + dis);
		}
		*/
	}

	//the using of rvalue reference
	//should not be treated as lvalue reference
	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, value_type&& value) {
		return insert_base(pos, 1, value_type(value), typename std::is_integral<size_type>::type());
		/*
		size_type dis = static_cast<size_type>(std::distance(cbegin(), pos));
		if (end_ == stroage_) {
			size_type new_size = size() == 0 ? 2 : size() * 2;
			T* t_begin_ = allocate(new_size);
			T* t_end_ = t_begin_ + size() + 1;
			T* t_stroage_ = t_begin_ + (((sizeof(T)*new_size + 7) / 8) * 8) / sizeof(T);

			uninitialized_copy(cbegin(), pos, t_begin_);
			uninitialized_fill_n(t_begin_ + dis, 1, T(value));
			uninitialized_copy(pos, cend(), t_begin_ + dis + 1);

			delete_data_and_memory();
			begin_ = t_begin_;
			end_ = t_end_;
			stroage_ = t_stroage_;
			return iterator(begin_ + dis);
		}
		else {
			if (pos == cend()) {
				uninitialized_fill_n(end_, 1, value);
			}
			else {
				uninitialized_copy(end_ - 1, end_, end_ + 1);
				copy_backward(begin_ + dis, end_ - 1, end_);
				*(begin_ + dis) = value; //move assignment
			}
			end_++;
			return iterator(begin_ + dis);
		}
		*/
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, size_type count, const value_type& value) {
		return insert_base(pos, count, value, typename std::is_integral<size_type>::type());	
	}

	template<class T, class Allocator>
	template<class InputIt>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
		return insert_base(pos, first, last, typename std::is_integral<InputIt>::type());
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
		const T* first = ilist.begin();
		const T* last = ilist.end();
		return insert_base(pos, first, last, typename std::is_integral<const T*>::type());
		/*
		size_type dis = static_cast<size_type>(distance(cbegin(), pos));
		size_type count = init.size();
		if (end_ + count > stroage_) {
			size_type new_size = size() > count ? 2 * size() : 2 * count;
			T* t_begin_ = allocate(new_size);
			T* t_end_ = t_begin_ + size() + count;
			T* t_stroage_ = t_begin_ + (((sizeof(T)*new_size + 7) / 8) * 8) / sizeof(T);

			uninitialized_copy(cbegin(), pos, t_begin_);
			uninitialized_copy(init.begin(), init.end(), t_begin_ + dis);
			uninitialized_copy(pos, cend(), t_begin_ + dis + count);

			delete_data_and_memory();
			begin_ = t_begin_;
			end_ = t_end_;
			stroage_ = t_stroage_;
			return iterator(begin_ + dis);
		}
		else {
			if ((size() - dis) > count) {
				uninitialized_copy(end_ - count, end_, end_);
				copy_backward(begin_ + dis, begin_ + dis + count, end_);
				destory(begin_ + dis, begin_ + dis + count);
			}
			else {
				uninitialized_copy(begin_ + dis, end_, begin_ + dis + count);
				destory(begin_ + dis, end_);
			}
			uninitialized_copy(init.begin(), init.end(), begin_ + dis);
			end_ += count;
			return iterator(begin_ + dis);
		}
		*/
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator pos) {
		if (pos == cend()) {
			return end();
		}
		const_iterator first = pos;
		const_iterator last = ++pos;
		return erase(first, last);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
		size_type count = static_cast<size_type>(distance(first, last));
		size_type dis = static_cast<size_type>(distance(cbegin(), first));
		if (first == last) {
			return (begin_ + dis);
		}
		else {
			copy(last, cend(), begin_ + dis);
			destory(end_ - count, end_);
			end_ = end_ - count;
			return (begin_ + dis);
		}		
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(const value_type& value) {
		size_type old_size = size();
		if (end_ == stroage_) {
			size_type dis_size = old_size == 0 ? 1 : old_size;
			size_type new_size = 2 * dis_size;
			reallocate_and_preserve(new_size);
		}
		uninitialized_fill_n(begin_ + old_size, 1, value);
		end_ = begin_ + old_size + 1;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::push_back(value_type&& value) {
		size_type old_size = size();
		if (end_ == stroage_) {
			size_type dis_size = old_size == 0 ? 1 : old_size;
			size_type new_size = 2 * dis_size;
			reallocate_and_preserve(new_size);
		}
		uninitialized_fill_n(begin_ + old_size, 1, value);
		end_ = begin_ + old_size + 1;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::pop_back() {
		if (size() == 0)
			return;
		destory(end_ - 1, end_);
		end_--;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::resize(size_type count) {
		resize(count, value_type());
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::resize(size_type count, const value_type& value) {
		if (size() > count) {
			destory(begin_ + count, end_);
			end_ = begin_ + count;
		}
		else if (size() < count) {
			if (capacity() >= count) {
				uninitialized_fill_n(end_, count - size(), value);
			}
			else {
				size_type old_size = size();
				size_type new_size = count;
				reallocate_and_preserve(new_size);
				uninitialized_fill_n(begin_ + old_size, count - old_size, value);
			}
			end_ = begin_ + count;
		}
		else
			return;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::swap(vector& other) {
		if (this != &other) {
			std::swap(begin_, other.begin_);
			std::swap(end_, other.end_);
			std::swap(stroage_, other.stroage_);
		}
	}


	//private function to be called to allocate, deallocate and reallocate
	template<class T, class Allocator>
	T* vector<T, Allocator>::allocate(size_type size) {
		T* t = data_alloc::allocate(size);	
		return t;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::ininitialized(size_type size) {
		begin_ = allocate(size);
		end_ = begin_ + size;
		stroage_ = begin_ + (((sizeof(T)*size + 7) / 8) * 8) / sizeof(T);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::deallocate(T* p, size_type n) {
		data_alloc::deallocate(p, n);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::destory(T* first, T* last) {
		data_alloc::destory(first, last);	
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::delete_data_and_memory() {
		destory(begin_, end_);
		deallocate(begin_, capacity());
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::reallocate_and_desert(size_type need_size) {
		T* t_begin_ = allocate(need_size);
		T* t_stroage_ = t_begin_ + (((sizeof(T)*need_size + 7) / 8) * 8) / sizeof(T);

		delete_data_and_memory();
		begin_ = t_begin_;
		end_ = begin_;
		stroage_ = t_stroage_;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::reallocate_and_preserve(size_type need_size) {
		size_type old_size = size();
		T* t_begin_ = allocate(need_size);
		T* t_stroage_ = t_begin_ + (((sizeof(T)*need_size + 7) / 8) * 8) / sizeof(T);

		uninitialized_copy(begin_, end_, t_begin_);
		delete_data_and_memory();
		begin_ = t_begin_;
		end_ = begin_ + old_size;
		stroage_ = t_stroage_;
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::vector_base(size_type count, const value_type& value, std::true_type) {
		//std::printf("number and value\n");
		ininitialized(count);
		uninitialized_fill_n(begin_, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void vector<T, Allocator>::vector_base(InputIt first, InputIt last, std::false_type) {
		//std::printf("Iterator\n");
		//if first and last are not initialized, will not work

		size_type count = static_cast<size_type>(std::distance(first, last));
		ininitialized(count);
		uninitialized_copy(first, last, begin_);
	}

	template<class T, class Allocator>
	void vector<T, Allocator>::assign_base(size_type count, const value_type& value, std::true_type) {
		if (capacity() < count) {
			reallocate_and_desert(count);
		}
		else {
			destory(begin_, end_);		
		}
		end_ = begin_ + count;
		uninitialized_fill_n(begin_, count, value);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void vector<T, Allocator>::assign_base(InputIt first, InputIt last, std::false_type) {
		size_type count = static_cast<size_type>(std::distance(first, last));
		if (capacity() < count) {
			reallocate_and_desert(count);
		}
		else {
			destory(begin_, end_);	
		}
		end_ = begin_ + count;
		uninitialized_copy(first, last, begin_);
	}

	template<class T, class Allocator>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert_base(const_iterator pos, size_type count, const value_type& value, std::true_type) {
		size_type dis = static_cast<size_type>(distance(cbegin(), pos));
		size_type left_size = capacity() - size();
		if (count > left_size) {
			size_type new_size = size() > count ? 2 * size() : 2 * count;
			T* t_begin_ = allocate(new_size);
			T* t_end_ = t_begin_ + size() + count;
			T* t_stroage_ = t_begin_ + (((sizeof(T)*new_size + 7) / 8) * 8) / sizeof(T);

			uninitialized_copy(cbegin(), pos, t_begin_);
			uninitialized_fill_n(t_begin_ + dis, count, value);
			uninitialized_copy(pos, cend(), t_begin_ + dis + count);

			delete_data_and_memory();
			begin_ = t_begin_;
			end_ = t_end_;
			stroage_ = t_stroage_;
			return iterator(begin_ + dis);
		}
		else {
			//different area
			if ((size() - dis) > count) {
				uninitialized_copy(end_ - count, end_, end_);
				copy_backward(begin_ + dis, end_ - count, end_);
				destory(begin_ + dis, begin_ + dis + count);
			}
			else {
				uninitialized_copy(begin_ + dis, end_, begin_ + dis + count);
				destory(begin_ + dis, end_);
			}
			uninitialized_fill_n(begin_ + dis, count, value);
			end_ += count;
			return iterator(begin_ + dis);
		}
	}

	template<class T, class Allocator>
	template<class InputIt>
	typename vector<T, Allocator>::iterator vector<T, Allocator>::insert_base(const_iterator pos, InputIt first, InputIt last, std::false_type) {
		size_type dis = static_cast<size_type>(distance(cbegin(), pos));
		size_type count = static_cast<size_type>(std::distance(first, last));
		size_type left_size = capacity() - size();
		if (count > left_size) {
			size_type new_size = size() > count ? 2 * size() : 2 * count;
			T* t_begin_ = allocate(new_size);
			T* t_end_ = t_begin_ + size() + count;
			T* t_stroage_ = t_begin_ + (((sizeof(T)*new_size + 7) / 8) * 8) / sizeof(T);

			uninitialized_copy(cbegin(), pos, t_begin_);
			uninitialized_copy(first, last, t_begin_ + dis);
			uninitialized_copy(pos, cend(), t_begin_ + dis + count);

			delete_data_and_memory();
			begin_ = t_begin_;
			end_ = t_end_;
			stroage_ = t_stroage_;
			return iterator(begin_ + dis);
		}
		else {
			if ((size() - dis) > count) {
				uninitialized_copy(end_ - count, end_, end_);
				copy_backward(begin_ + dis, end_ - count, end_);
				destory(begin_ + dis, begin_ + dis + count);
			}
			else {
				uninitialized_copy(begin_ + dis, end_, begin_ + dis + count);
				destory(begin_ + dis, end_);
			}
			uninitialized_copy(first, last, begin_ + dis);
			end_ += count;
			return iterator(begin_ + dis);
		}
	}



	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (std::size_t i = 0; i < lhs.size(); i++) {
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		return (!operator==(lhs, rhs));
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		for (std::size_t i = 0; i < size; i++) {
			if (!((lhs[i] == rhs[i]) || (lhs[i] < rhs[i])))
				return false;
		}
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		std::size_t size = lhs.size() > rhs.size() ? rhs.size() : lhs.size();
		for (std::size_t i = 0; i < size; i++) {
			if (!(lhs[i] < rhs[i]))
				return false;
		}
		return true;
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		return (!operator<(lhs, rhs));
	}

	template<class T, class Allocator = d_stl::allocator<T>>
	bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs) {
		return (!operator<=(lhs, rhs));
	}

}
#endif 
