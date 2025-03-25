#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node node;

void print_list(struct Node* pnode)
{
	int count = 0;
	while(pnode != NULL)
	{
		printf("Value of %d node = %d\n", ++count, pnode->data);
		pnode = pnode->next;
	}
}

int main()
{
	struct Node* head = NULL;
	struct Node* node1 = NULL;
	struct Node* node2 = NULL;
	struct Node* node3 = NULL;

	node1 = malloc(sizeof(node));
	node2 = malloc(sizeof(node));
	node3 = malloc(sizeof(node));

	node1->data = 32;
	node1->next = node2;
	head = node1;

	node2->data = 37;
	node2->next = node3;

	node3->data = 43;
	node3->next = NULL;

	struct Node* newnode = malloc(sizeof(node));
	newnode->data = 78;
	newnode->next = head;
	head = newnode;

	print_list(head);

	free(node1);
	free(node2);
	free(node3);
	free(newnode);

	return 0;
}
