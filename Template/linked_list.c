#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "linked_list.h"

// sequence counter
int seq_ctr = 0;

//Read the file on a line by line basis
char* read_line(char* fname, int line_no) 
{
	FILE * fp = fopen(fname, "r"); // open the file eith error checking
	if (fp == NULL)
	{
		perror("fopen");
		free(fname);
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	if (fseek(fp, 0, SEEK_END) != 0) { // have fp cursor go to end of file with error check

		perror("read_line");
		free(fname);
		fclose(fp);
		exit(-1);

	}

	long int endpos = ftell(fp); // retrieve end of file position
	long int currentpos;
	rewind(fp); // reset fp cursor

	char * buf = (char*) malloc(256); // maximum line count
	int i;
	size_t length = 0;

	// read every line BEFORE the line we want

	for(i = 0; i <= line_no; i++)
	{
		currentpos = ftell(fp); // get current fp cursor position with error check

		if (currentpos == -1) {

			perror("read_line");
			free(buf);
			free(fname);
			fclose(fp);
			exit(-1);

		}

		if(currentpos == endpos) //EOF detected
		{

			fclose(fp);
			free(buf);
			return ((char*)5);

		}

		if((fgets(buf, LINE_SIZE, fp)) == NULL) // error checking
		{
			
			perror("read_line");
			free(buf);
			free(fname);
			fclose(fp);
			exit(EXIT_FAILURE);

		}
	}

	fclose(fp);
	return buf;

} 

// traverse the linked list

void traversal(node *head)
{
	node * temp = head;
	while(temp != NULL)
	{
		printf("%i, %i, %s", temp->seq_no, temp->line_no, temp->content); // proper formatting
		temp = temp->next;
	}

}

// insert the node into the linked list

void insert(node **phead, node *newnode)
{
	// first node inserted

	if(*phead == NULL)
	{
		*phead = newnode; // given first entry into linked list
	}

	else if ((*phead)->line_no > newnode->line_no) { // there is atleast 1 node in the list before entry

		newnode->next = (*phead); // given the object will fall at begining of linked list
		
		(*phead) = newnode;

	}

	else 
	{
		node * search = *phead;

		while(search->next != NULL) // traverse through linked list
		{

			if ((search->line_no < newnode->line_no) && (search->next->line_no > newnode->line_no)) { // sorted insertion into linked list

				node* temp = search->next;
				search->next = newnode;
				newnode->next = temp;

				return;

			}

			search = search->next;

		}

		search->next = newnode;

		return;

	}
}

//create a new node structure
node* create_node(int line_no, char *line)
{ 

	node * newnode = (node *) malloc(sizeof(node));
	newnode->seq_no = seq_ctr++;
	newnode->line_no = line_no;
	newnode->content = line;
	newnode->next = NULL;
	return newnode;

}
