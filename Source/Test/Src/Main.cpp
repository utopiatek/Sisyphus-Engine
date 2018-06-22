
#include <iostream>
using namespace std;

#include "Core/Inc/Core.h"
#include "Math/Inc/Math.h"

int main()
{
	int a = Square(2);
	int b = Square2(2);
	int c = Square(2);

	cout << "Hello World!" << a << ", " << b << ", " << c << endl;

	getchar();
	return 0;
}
//http://10.0.0.19/wasm/Out.html