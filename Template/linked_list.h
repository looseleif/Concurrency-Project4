#ifndef __LINKED_LIST_H
#define __LINKED_LIST_H

#define LINE_SIZE 256

typedef struct linked_node {
	int seq_no;
	int line_no;
	char *content;
	struct linked_node *next;	
} node;

//Initialize page table
char* read_line(char *, int); 
void traversal(node *);
void insert(node **, node *);
node* create_node(int, char *);

node *head;// to be used for linked list
#endif
