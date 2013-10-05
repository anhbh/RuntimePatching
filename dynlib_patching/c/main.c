#include <stdio.h>
#include <dlfcn.h>
#include "unistd.h"

int main( void )
{
	printf( "main calling shared library func\n" );

	void *hndl = NULL;
	void (*foo)() = NULL;

	while(1)
	{
		if( ( hndl = dlopen( "./libfoo.so", RTLD_LAZY ) ) == NULL )
		{
			printf( "%s\n", dlerror() );
			return -1;
		}

		if( ( foo = dlsym( hndl, "foo" ) ) == NULL )
		{
			printf( "%s\n", dlerror() );
			dlclose( hndl );
			return -1;
		}

		foo();

		dlclose( hndl );

		// buy some time to modify .so file
		sleep( 10 );
	}
	return 0;
}
