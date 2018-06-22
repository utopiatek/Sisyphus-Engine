
#include "../Inc/Core.h"


SE_API int Square(int x)
{
	static int g = 0; g++;

	return x * x * g;
}
