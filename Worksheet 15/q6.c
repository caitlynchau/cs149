#include <stdio.h>
#include <stdlib.h>

/*
6. Create a program "q6.c" that allocates an array of integers (as above), frees
them, and then tries to print the value of one of the elements of the array. 

Does the program run? 
> Yes, the program still runs after data is freed and outputs:
> value at data[0] is 0

What happens when you use valgrind on it?
> A memory error is detected

	==2694== Invalid read of size 4
	==2694==    at 0x1091D9: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q6)
	==2694==  Address 0x4a53040 is 0 bytes inside a block of size 400 free'd
	==2694==    at 0x483CA3F: free (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==2694==    by 0x1091D4: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q6)
	==2694==  Block was alloc'd at
	==2694==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==2694==    by 0x10919E: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q6)

*/


int main() {

	int * data;
	data = (int*)malloc(sizeof(int) * 100);
	

	data[0] = 1;
	data[1] = 2;
	data[2] = 3;


	free(data);

	printf("value at data[0] is %d\n", data[0]);


}