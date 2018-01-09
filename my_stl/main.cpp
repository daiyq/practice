#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "test.h"

int main()
{
	d_stl::test();


	_CrtDumpMemoryLeaks();
	return 0;
}

