#include <stdio.h>
#include <stdlib.h>

/*
4. Write a simple program "q4.c" that allocates memory using malloc() but forgets
to free it before exiting. 

What happens when this program runs? Can you use gdb to find any problems with it? 
How about valgrind (with the --leak-check=yes flag)?

Program runs and the output is: value in pointer is 3

	ptr is never freed, so there will be a memory leak.
	valgrind summary:
	==2421== LEAK SUMMARY:
	==2421==    definitely lost: 4 bytes in 1 blocks
	==2421==    indirectly lost: 0 bytes in 0 blocks
	==2421==      possibly lost: 0 bytes in 0 blocks
	==2421==    still reachable: 0 bytes in 0 blocks
	==2421==         suppressed: 0 bytes in 0 blocks

*/


int main() {

	int * ptr;
	ptr = (int*)malloc(sizeof(int));
	*ptr = 3;

	printf("value in pointer is %d\n", *ptr);

	


}