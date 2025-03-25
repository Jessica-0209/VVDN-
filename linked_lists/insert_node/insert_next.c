#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node node, *np;

void print_list(struct Node* pnode)
{
	int count = 0;
	while(pnode != NULL)
	{
		printf("Value of %d node = %d\n", ++count, pnode->data);
		pnode = pnode->next;
	}
}

void insert_after_node(np prev_node)
{
	if(prev_node == NULL)
	{
		printf("Previous node cannot be NULL!\n");
		return;
	}

	np newnode = malloc(sizeof(node));
	
	newnode->data = 12;
	newnode->next = prev_node->next;
	prev_node->next = newnode;
}

int main()
{
	np head = NULL;
	np node1 = NULL;
	np node2 = NULL;
	np node3 = NULL;

	node1 = malloc(sizeof(node));
	node2 = malloc(sizeof(node));
	node3 = malloc(sizeof(node));

	node1->data = 20;
	node1->next = node2;
	head = node1;

	node2->data = 32;
	node2->next = node3;

	node3->data = 43;
	node3->next = NULL;
	
	printf("Linked List before insertion of new node:\n");	
	print_list(head);

	insert_after_node(node1);

	printf("\nLinked List after inserting new node:\n");
	print_list(head);

	free(node1);
	free(node2);
	free(node3);

	return 0;
}
