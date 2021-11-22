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

	char* lineOfInterest; // to hold line from file

	int local_lc = 0; // used to maintain local manipulation and minimize critical sections

	while (1) {

		if (pthread_mutex_lock(&line_lock) != 0) {

			perror("process_file");
			exit(-1);

		}

		local_lc = line_ctr; // locked manipulation of line_ctr

		line_ctr = line_ctr + 1;

		if (pthread_mutex_unlock(&line_lock) != 0) {

			perror("process_file");
			exit(-1);

		}

		char* filename = (char*)param;

		lineOfInterest = read_line(filename, local_lc);

		if (lineOfInterest == (char*)5) {

			return 0;

		}

		
		if (pthread_mutex_lock(&list_lock) != 0) {

			perror("process_file");
			exit(-1);

		}

		node* threadNode = create_node(local_lc, lineOfInterest); // read only access of data

		insert(&head, threadNode);

		
		if (pthread_mutex_unlock(&list_lock) != 0) {

			perror("process_file");
			exit(-1);

		}

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

	traversal(head); // only print resultant linked list contents at the end

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
