#ifndef D_ALLOC_H_
#define D_ALLOC_H_
#include <cstddef> //size_t

namespace d_stl {

	//memory processing functions
	class alloc {
	private:
		enum { ALIGN = 8 };
		enum { MAX_BYTES = 128 };
		enum { NUMBER_FREE_LIST = MAX_BYTES / ALIGN }; //NUMBER OF FREE LISTS
		enum { NOBJS = 20 }; //get a few pieces memory

	private:
		//memory pool
		static char* start_free;
		static char* end_free;
		static std::size_t heap_size;

	private:
		//list's node means memory of exact size
		union obj {
			union obj* next;
			char index[1];
		};

		static obj* free_list[NUMBER_FREE_LIST];

	private:
		static std::size_t round_up(std::size_t bytes);
		static std::size_t free_list_index(std::size_t bytes);

		//allocate momory for size = bytes 
		static void* refill(std::size_t bytes);
		//get memory for function above
		static char* chunk_alloc(std::size_t bytes, std::size_t& nobjs);

	private:
		static void* first_allocate(std::size_t n);
		static void first_deallocate(void* p, std::size_t n);

		static void* second_allocate(std::size_t n);
		static void second_deallocate(void* p, std::size_t n);

	public:
		static void* allocate(std::size_t n);
		static void deallocate(void* p, std::size_t n);
	};

}
#endif 
