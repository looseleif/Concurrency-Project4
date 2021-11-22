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
	FILE * fp = fopen(fname, "r");
	if (fp == NULL)
	{
		perror("fopen");
		free(fname);
		fclose(fp);
		exit(EXIT_FAILURE);
	}

	fseek(fp, 0, SEEK_END);
	long int endpos = ftell(fp);;
	long int currentpos;
	rewind(fp);

	char * buf = (char*) malloc(256);
	int i;
	size_t length = 0;
	//read every line BEFORE the line we want
	for(i = 0; i <= line_no; i++)
	{
		currentpos = ftell(fp);
		if(currentpos == endpos) //EOF
		{
			free(buf);
			return ((char*)5);
		}
		if((fgets(buf, LINE_SIZE, fp)) == NULL) //ERROR CHECKING
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

//traverse the linked list
void traversal(node *head)
{
	node * temp = head;
	while(temp != NULL)
	{
		printf("%i, %i, %s", temp->seq_no, temp->line_no, temp->content);
		temp = temp->next;
	}

}

// insert the node into the linked list
void insert(node **phead, node *newnode)
{
	//first node inserted
	if(*phead == NULL)
	{
		*phead = newnode;
	}
	else if ((*phead)->line_no > newnode->line_no) {

		newnode->next = (*phead);
		
		(*phead) = newnode;

	}
	else
	{
		node * search = *phead;

		while(search->next != NULL)
		{

			if ((search->line_no < newnode->line_no) && (search->next->line_no > newnode->line_no)) {

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
