#include <iostream>
#include "foo_if.hpp"
#include "foo_lib.hpp"

using namespace std;

void Foo::init()
{
	cout << "Foo::init: Hello World!" << endl;
}

extern "C" Foo *create()
{
	return new Foo;
}

extern "C" void destroy( Foo *f )
{
	delete f;
}
