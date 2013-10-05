#include <stdio.h>
#include <stdlib.h>

unsigned int some_func( void )
{
	unsigned int a=0;
	unsigned int i;
	for( i=0; i<99; i++ )
	{
		a=a+1;
	}

	return a;
}

int export_func( void (*fp)(), const char *filename )
{
	unsigned char dw[2] = { 0x00, 0x00 };
	unsigned int i=0;

	FILE *of = fopen( filename, "wb" );

	if( of == NULL )
	{
		printf( "export_func failed: Can't open file for writing!\n" );
		return -1;
	}

	do
	{
		dw[ 1 ] = dw[ 0 ];
		dw[ 0 ] = *((unsigned char *)(fp+i));
		i++;
		fwrite( (void *) dw, 1, 1, of );
	} while( dw[0] != 0xC3 && dw[1] != 0xC9 );

	fclose( of );

	return i;
}

void (*import_func( const char *filename, unsigned char **code_buffer, unsigned int *size ))( void )
{
	FILE *fi = fopen( filename, "rb" );

	if( fi == NULL )
	{
		printf( "import_func failed: Can't open file for reading!\n" );
		return NULL;
	}

	fseek( fi, 0L, SEEK_END );
	(*size) = ftell( fi );
	fseek( fi, 0L, SEEK_SET );

	(*code_buffer) = ( unsigned char * ) malloc( sizeof( char )*(*size) );

	if( (*code_buffer) == NULL )
	{
		printf( "import_func failed: Memory error!\n" );
		return NULL;
	}

	if( fread( (*code_buffer), sizeof( char ), (*size), fi ) != (*size) )
	{
		printf( "import_func: Read error!\n" );
		free( *code_buffer );
		return NULL;
	}

	fclose( fi );

	return (void (*)()) (*code_buffer);
}

int main( void )
{
	unsigned int (*orig_fp)();
	orig_fp = some_func;

	// call some_func
	printf( "some_func = %08x\n", orig_fp() );

	// export some_func to file, comment as needed
	export_func( (void (*)()) orig_fp, "some_func.bin" );

	unsigned int (*fp)();
	unsigned char *cb = NULL;
	int cb_sz = 0;

	// import imp_func from file, comment as needed
	fp = (unsigned int (*)()) import_func( "some_func.bin", &cb, &cb_sz );

	// DEBUG: print addresses
	printf( "main: ofp @ %08x\n", ( unsigned int ) ((unsigned int *)orig_fp) );
	printf( "main:  fp @ %08x\n", ( unsigned int ) ((unsigned int *)fp) );

	// DEBUG: print imp_func size + contents
	int i=0;
	printf( "imp_func size = %d\nimp_func:\n", cb_sz );

	for( i=0; i<cb_sz; i+=4 )
		printf( " %02x %02x %02x %02x\n", (unsigned int) cb[i], (unsigned int) cb[i+1], (unsigned int) cb[i+2], (unsigned int) cb[i+3] );

	// call imp_func
	// 	<- runs on older kernels <= 2.6.x
	// 	<- fails on more recent kernels (>= 3.x)
	printf( "imp_func = %d\n", fp() );

	free( cb );

	return 0;
}

