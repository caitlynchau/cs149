#include <stdio.h>
#include <stdlib.h>

/*
5. Write a program "q5.c" that creates an array of integers called data of size
100 using malloc; then set data[100] to zero. 

What happens when you run this program? 
> Program runs and an integer array of size 100 (400 bytes) is allocated on the heap.
> data[100] is set to 0

What happens when you run this program using valgrind? Is the program
correct?
> data is not freed so there is a memory leak.
> 	==2640== Invalid write of size 4
	==2640==    at 0x10918D: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q5)
	==2640==  Address 0x4a531d0 is 0 bytes after a block of size 400 alloc'd
	==2640==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==2640==    by 0x10917E: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q5)
	==2640== 
	==2640== Invalid read of size 4
	==2640==    at 0x10919D: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q5)
	==2640==  Address 0x4a531d0 is 0 bytes after a block of size 400 alloc'd
	==2640==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==2640==    by 0x10917E: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q5)
	==2640== 
	value at data[100] is 0
	==2640== 
	==2640== HEAP SUMMARY:
	==2640==     in use at exit: 400 bytes in 1 blocks
	==2640==   total heap usage: 2 allocs, 1 frees, 1,424 bytes allocated
	==2640== 
	==2640== 400 bytes in 1 blocks are definitely lost in loss record 1 of 1
	==2640==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	==2640==    by 0x10917E: main (in /home/caitlyn/Desktop/cs149/Worksheet 15/q5)
	==2640== 
	==2640== LEAK SUMMARY:
	==2640==    definitely lost: 400 bytes in 1 blocks
	==2640==    indirectly lost: 0 bytes in 0 blocks
	==2640==      possibly lost: 0 bytes in 0 blocks
	==2640==    still reachable: 0 bytes in 0 blocks
	==2640==         suppressed: 0 bytes in 0 blocks

*/


int main() {

	int * data;
	data = (int*)malloc(sizeof(int) * 100);
	data[100] = 0;

	printf("value at data[100] is %d\n", data[100]);


}