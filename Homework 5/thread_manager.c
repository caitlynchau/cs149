#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


#include "Node.h"


/* function prototypes */
void * thread_runner(void*);
void printLog(int logid, pthread_t threadid, pid_t pid, time_t now, char msg[50]);
int getLogid();
// void updateReadFlag();


/* locks */
pthread_mutex_t tlockLogIndex = PTHREAD_MUTEX_INITIALIZER; // log index
pthread_mutex_t tlockAllocateThread = PTHREAD_MUTEX_INITIALIZER; // allocating THREADDATA
pthread_mutex_t tlockDeallocateThread = PTHREAD_MUTEX_INITIALIZER; // deallocate THREADDATA
pthread_mutex_t tlockLinkedList = PTHREAD_MUTEX_INITIALIZER; // modifying linked list
pthread_mutex_t tlockReadFlag = PTHREAD_MUTEX_INITIALIZER; // read flag

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

/* THREADDATA declaration */
struct THREADDATA_STRUCT
{
	pthread_t creator;
};
typedef struct THREADDATA_STRUCT THREADDATA;


/* thread variables */
pthread_t tid1, tid2;
THREADDATA* p = NULL;


//variable for indexing of messages by the logging function
int logindex = 0;

//A flag to indicate if the reading of input is complete, 
//so the other thread knows when to stop
bool is_reading_complete = false;

// flag indicates if linked list head was updated
bool is_head_updated = false;


/* input variables */
char buf[21];

/* linkedlist variables */
Node * head = NULL;
Node * current = NULL;



/*********************************************************
main function
*********************************************************/
int main()
{

	printf("create first thread\n");
	pthread_create(&tid1, NULL, thread_runner, NULL);

	printf("create second thread\n");
	pthread_create(&tid2, NULL, thread_runner, NULL);

	printf("wait for first thread to exit\n");
	pthread_join(tid1, NULL);
	printf("first thread exited\n");

	printf("wait for second thread to exit\n");
	pthread_join(tid2, NULL);
	printf("second thread exited\n");

	exit(0);

}//end main


/**********************************************************************
// function thread_runner runs inside each thread -------------------------------------------------- 
**********************************************************************/
void * thread_runner(void* x)
{
	time_t now;
	pthread_t me;
	me = pthread_self();
	
	time(&now);
	printLog(getLogid(), me, getpid(), now, "entered thread_runner");

	/* Critical section: allocate p */
	pthread_mutex_lock(&tlockAllocateThread);
	if (p == NULL) {
		p = (THREADDATA*) malloc(sizeof(THREADDATA));
		p->creator = me;
		time(&now);
		printLog(getLogid(), me, getpid(), now, "allocated THREADDATA");
	}
	pthread_mutex_unlock(&tlockAllocateThread);  
	// Critical section ends

	/* Thread 1 */
	if (p != NULL && p->creator == me) {

		while (fgets(buf, 21, stdin) != NULL) {

			/* break when new line is encountered */
			if (buf[0] == '\n') break;

			// otherwise set newline character to null
			buf[strlen(buf) - 1] = '\0'; 

			/* Critical section: add node linked list */
			pthread_mutex_lock(&tlockLinkedList);

			current = (Node*)malloc(sizeof(Node));
			CreateNewNode(current, buf, head);
			head = current; // head updated
			is_head_updated = true;

			time(&now);
			printLog(getLogid(), me, getpid(), now, "created and inserted node");
			
			pthread_mutex_unlock(&tlockLinkedList);
			pthread_cond_signal(&condition);
			/* end critical section */
			
		} // end while	

		/* Critical section: update is_reading_complete and is_head_updated flags */
		pthread_mutex_lock(&tlockReadFlag);
		is_reading_complete = true;
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&tlockReadFlag);



		// pthread_mutex_lock(&tlockListHeadFlag);
		// is_head_updated = true;
		// pthread_mutex_unlock(&tlockListHeadFlag);
		/* end critical section */

	// end if

	/* Thread 2 */
	} else { 
	
		while (is_reading_complete == 0) { 

			/* Critical section: wait for linked list to update */
			pthread_mutex_lock(&tlockLinkedList);

			// waiting for user input and make sure last input
			// and make sure last thing inputted is not a newline
			// signaling read is complete
			while (!is_head_updated && !is_reading_complete) {
				pthread_cond_wait(&condition, &tlockLinkedList);
			}

			is_head_updated = false;
			pthread_mutex_unlock(&tlockLinkedList);

			if (!is_reading_complete) {
				char outputMsg[50];
				sprintf(outputMsg, "head of linked list contains line: %s", head->input);
				time(&now);
				printLog(getLogid(), me, getpid(), now, outputMsg);
			}
		} // end while

		/* Reading complete */

		/* Critical section: deallocate linked list */
		pthread_mutex_lock(&tlockLinkedList);

		FreeNodes(head);
		head = NULL;
		time(&now);
		printLog(getLogid(), me, getpid(), now, "deallocated linked list");

		pthread_mutex_unlock(&tlockLinkedList);
		/* end critical section */


		/* Critical section: deallocate thread */
		pthread_mutex_lock(&tlockDeallocateThread);
		if (p != NULL && p->creator != me) {

			free(p);
			p = NULL;
			time(&now);
			printLog(getLogid(), me, getpid(), now, "deallocated THREADDATA");

		}

		pthread_mutex_unlock(&tlockDeallocateThread);
		/* end critical section */
	} // end else



	

	

	time(&now);
	printLog(getLogid(), me, getpid(), now, "exiting thread_runner()");
	
	pthread_exit(NULL);
	return NULL;

}//end thread_runner

void printLog(int logid, pthread_t threadid, pid_t pid, time_t now, char msg[50]) {
	/* convert time */
	int hours, minutes, seconds, day, month , year;
	struct tm * local = localtime(&now);
	hours = local->tm_hour;
	minutes = local->tm_min;
	seconds = local->tm_sec;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;
	if (hours < 12) {
		hours = hours - 12;
		printf("Logindex %d, thread %lu, PID %d, %02d/%02d/%02d %02d:%02d:%02d AM : %s\n", 
		logid, threadid, pid, day, month, year, hours, minutes, seconds, msg);
	} else {
		printf("Logindex %d, thread %lu, PID %d, %02d/%02d/%02d %02d:%02d:%02d PM : %s\n", 
		logid, threadid, pid, day, month, year, hours, minutes, seconds, msg);
	}
}

int getLogid() {
	/* Critical section: read/update log message index */
	pthread_mutex_lock(&tlockLogIndex);

	logindex++;
	
	pthread_mutex_unlock(&tlockLogIndex);
	/* end critical section */

	return logindex;
}

// void updateReadFlag() {
// 	/* Critical section: update read flag */
// 	pthread_mutex_lock(&tlockReadFlag);

// 	if (is_reading_complete) is_reading_complete = false;
// 	else is_reading_complete = true;

// 	pthread_mutex_unlock(&tlockReadFlag);
// 	/* end critical section */
// }