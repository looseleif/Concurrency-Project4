#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "linked_list.h"

//global line-number counter to be sync'ed.
int line_ctr = 0;

int checkEnd = 0;

//initialization of mutex locks
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seq_lock = PTHREAD_MUTEX_INITIALIZER;
//at least two mutex locks should be used

//start of the threads
void* process_file(void *param)
{

	char* lineOfInterest;

	int local_lc = 0;

	while (1) {

		pthread_mutex_lock(&line_lock);

		local_lc = line_ctr;

		line_ctr = line_ctr + 1;

		pthread_mutex_unlock(&line_lock);

		char* filename = (char*)param;

		lineOfInterest = read_line(filename, local_lc);

		if (lineOfInterest == (char*)5) {

			free(lineOfInterest);

			return 0;

		}

		pthread_mutex_lock(&list_lock);

		node* threadNode = create_node(local_lc, lineOfInterest);

		insert(&head, threadNode);

		pthread_mutex_unlock(&list_lock);

	}

	return 0;

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

	if (head != NULL) {

		node* clearNode;

		while (head != NULL) {

			clearNode = head;
			head = head->next;
			free(clearNode->content);
			free(clearNode);

		}

	}

	printf("\n");

	free(filename);
	return 0;
}
