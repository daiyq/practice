#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "test_vector.h"

int main()
{
	d_stl::test_vector();


	_CrtDumpMemoryLeaks();
	return 0;
}

