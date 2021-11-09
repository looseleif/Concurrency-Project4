#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

//global line-number counter to be sync'ed.
int line_ctr = 0;

//initialization of mutex locks
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seq_lock = PTHREAD_MUTEX_INITIALIZER;
//at least two mutex locks should be used

//start of the threads
void* process_file(void *param)
{
	// TODO
}

int main(int argc, char* argv[])
{
	FILE* in_ptr;
	int threads;
	char *filename = NULL;

	if (argc != 3) {
		printf("Incorrect arg count. Enter file name and thread count\n");
		exit(EXIT_FAILURE);
	}

	threads = atoi(argv[2]);
	if (threads < 1 || threads > 16) {
		printf("Incorrect number of threads. Enter between 1 and 16\n");
		exit(EXIT_FAILURE);
	}

	// TODO: create threads and join them
	
	return 0;
}
