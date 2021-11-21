#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
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

	pthread_mutex_lock(&seq_lock);

	char * filename = (char *) param;

	char* lineOfInterest = read_line(filename, line_ctr);

	if()

	node* threadNode = create_node(line_ctr, lineOfInterest);
		
	line_ctr++;

	if (line_ctr == 0) {

		insert(NULL, threadNode);

	}
	else {

		insert(&head, threadNode);

	}

	pthread_mutex_unlock(&seq_lock);

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
	filename = (char *) malloc(sizeof(argv[1]));
	strcpy(filename, argv[1]);

	int i;
	pthread_t threadArray[threads];
	for(i = 0; i < threads; i++)
	{
		pthread_create(&threadArray[i], NULL, process_file, (void*) filename);
	}

	for(i = 0; i < threads; i++)
	{
		pthread_join(threadArray[i], NULL);
	}

	traversal(head);

	free(filename);
	return 0;
}
