#include <cstdlib> //malloc, free
#include <new>
#include "alloc.h"


namespace d_stl {

	char* alloc::start_free = nullptr;
	char* alloc::end_free = nullptr;
	std::size_t alloc::heap_size = 0;
	alloc::obj* alloc::free_list[NUMBER_FREE_LIST] = { nullptr,nullptr, nullptr,nullptr, nullptr,nullptr, nullptr,nullptr,nullptr,nullptr, nullptr,nullptr, nullptr,nullptr, nullptr,nullptr };

	std::size_t alloc::round_up(std::size_t bytes) {
		return ((bytes + ALIGN - 1)&~(ALIGN - 1));
	}

	std::size_t alloc::free_list_index(std::size_t bytes) {
		return ((bytes + ALIGN - 1) / ALIGN - 1);
	}

	//bytes has been normalized
	void* alloc::refill(std::size_t bytes) {
		std::size_t nobjs = 20;
		char* chunk = chunk_alloc(bytes, nobjs);
		if (nobjs == 1)
			return chunk;

		obj** my_free_list;
		my_free_list = free_list + free_list_index(bytes);
		obj* current;
		obj* next;

		obj* result;
		result = reinterpret_cast<obj*>(chunk);
		*my_free_list = next = reinterpret_cast<obj*>(chunk + bytes);
		
		std::size_t i = 1;
		for (;;) {
			current = next;
			next = reinterpret_cast<obj*>(reinterpret_cast<char*>(next) + bytes);
			if (i == nobjs - 1) {
				current->next = nullptr;
				break;
			}
			current->next=next;
			i++;
		}
		return result;
	}
	
	//bytes has been normalized
	char* alloc::chunk_alloc(std::size_t bytes, std::size_t& nobjs) {
		char* result;
		std::size_t left = end_free - start_free;
		if (left >= (bytes*nobjs)) {
			result = start_free;
			start_free += bytes*nobjs;
			return start_free;
		}
		else if (left >= bytes) {
			result = start_free;
			nobjs = left / bytes;
			start_free += bytes*nobjs;
			return result;
		}
		else {
			std::size_t bytes_to_get = 2 * bytes*nobjs + round_up(heap_size >> 4);

			if (left > 0) {
				obj** my_free_list;
				obj* tmp = reinterpret_cast<obj*>(start_free);
				my_free_list = free_list + free_list_index(left);
				tmp->next = *my_free_list;
				*my_free_list = tmp;
			}

			start_free = static_cast<char*>(std::malloc(bytes_to_get));
			if (start_free == nullptr) {
				std::size_t i = bytes;
				obj** my_free_list;
				obj* tmp;
				for (; i <= MAX_BYTES; i += ALIGN) {
					my_free_list = free_list + free_list_index(i);
					tmp = *my_free_list;
					if (tmp != nullptr) {
						*my_free_list = tmp->next;
						start_free = reinterpret_cast<char*>(tmp);
						end_free = start_free + i;
						return chunk_alloc(bytes, nobjs);
					}
				}
				end_free = nullptr;
				start_free = static_cast<char*>(first_allocate(bytes_to_get));
			}

			end_free = start_free + bytes_to_get;
			heap_size += bytes_to_get;

			return chunk_alloc(bytes, nobjs);
		}

	}

	void* alloc::first_allocate(std::size_t n) {
		void* result;
		result = std::malloc(n);
		if (result == nullptr)
			throw std::bad_alloc();  //out of memory
		return result;
	}
	void alloc::first_deallocate(void* p, std::size_t n) {
		std::free(p);
	}

	void* alloc::second_allocate(std::size_t n) {
		obj** my_free_list;
		obj* result;
		my_free_list = free_list + free_list_index(n);
		result = *my_free_list;
		if (result == nullptr) {
			void* r = refill(round_up(n));
			return r;
		}
		*my_free_list = result->next; //adjust the pointer, use of equal pointer
		return result;
	}
	void alloc::second_deallocate(void* p, std::size_t n) {
		obj** my_free_list;
		obj* tmp = static_cast<obj*>(p);
		//difference between allocate and deallocate
		//for example: 12 bytes for allocate, it should in (12+8-1)/8=2, the second node,
		//so it should allocate from the second node(16 bytes)
		//12 bytes for deallocate, it should in 12/8=1, the first node,
		//so it should deallocate into the fist node(8 bytes)
		//of course, we may suppose n is multples of 8
		if (n < 8)
			std::free(p);
		my_free_list = free_list + (n / 8 - 1); 
		tmp->next = *my_free_list;
		*my_free_list = tmp;
	}

	void* alloc::allocate(std::size_t n) {
		void* result;
		if (n > 128) {
			result = first_allocate(n);
		}
		else {
			result = second_allocate(n);
		}

		return result;
	}

	void alloc::deallocate(void* p, std::size_t n) {
		if (n > 128) {
			first_deallocate(p, n);
		}
		else {
			second_deallocate(p, n);
		}
	}

}
