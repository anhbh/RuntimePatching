## RuntimePatcher ##

Contains several prototypes for some kind of self-patching engine, which
allows a running executable to update/modify some of it's functions/modules
during runtime.

If not otherwise mentioned all tests were performed on standard Linux Kernel
`3.2.0`.


### asm - Patching ###

#### Description ####

This prototype implements two functions `export_func` and `import_func`.
`export_func` is used to write machine code of some function of the running
executable into a file. `import_func` respectively can be used to restore
a functions exported machine code by reading the binary file contents.

Both `export_func` and `import_func` work as expected but calling an imported
function results in a segmentation violation on recent kernels (3.2.0). Though
the provided test program *did* work on standard Linux running kernel 2.6.24.

#### Usage ####

	$ cd asm_patching
	$ make
	$ ./main
	 # sample output for imp_func != some_func
	 some_func = 00000063
	 main: ofp @ 080485a4
	 main:  fp @ 0933d170
	 imp_func size = 41
	 imp_func:
		55 89 e5 83
		ec 10 c7 45
		f8 00 00 00
		00 c7 45 fc
		00 00 00 00
		eb 08 83 45
		f8 01 83 45
		fc 01 83 7d
		fc 62 76 f2
		8b 45 f8 c9
		c3 00 00 00
	 imp_func = 000000c6

#### Problems ####

- static vars in imported func (`prtinf( "Test\n" )` --> segfault)
- function calls from within imported func?
- memory protection in recent kernels forbids call to imported function --> segfault
- --> wrong approach



### Shared Library Patching ###

	ToDo


#### Description ####

	ToDo


#### Usage ####

Both C and C++ version of the sample have identical usage. Only outputs may
differ:

	$ cd cd dynlib_patching/cpp/
	$ make
	$ ./main
	 Foo::init: Hello World!
	 ...
	 <now modify code + replace .so>
	 ...
	 Foo::init: H3ll0 W0r1d!
