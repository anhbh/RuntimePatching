#include <iostream>
#include <dlfcn.h>
#include <unistd.h>
#include "foo_if.hpp"

using namespace std;

int main( void )
{
	void *hndl = NULL;

	typedef FooIf *create_t( );
	typedef void destroy_t( FooIf * );

	while(1)
	{
		if( ( hndl = dlopen( "./libfoo.so", RTLD_NOW ) ) == NULL )
		{
			cout << "Error: " << dlerror() << endl;
			return -1;
		}

		create_t *creat = ( create_t * ) dlsym( hndl, "create" );
		destroy_t *destr = ( destroy_t * ) dlsym( hndl, "destroy" );

		if( !creat || !destr )
		{
			cout << "Error: " << dlerror() << endl;
			dlclose( hndl );
			return -1;
		}

		FooIf *my_foo = creat();
		my_foo->init();
		destr( my_foo );

		dlclose( hndl );

		// buy some time to replace the .so files
		sleep( 10 );
	}

	return 0;
}
