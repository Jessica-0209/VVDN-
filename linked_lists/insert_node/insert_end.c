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

void insert_end(np *head)
{
	np newnode = (np)malloc(sizeof(node));

	newnode->data = 50;
	newnode->next = NULL;

	if(*head == NULL)
	{
		*head = newnode;
		return;
	}

	np temp = *head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}


int main()
{
	np head = NULL;
	np node1 = NULL;
	np node2 = NULL;
	np node3 = NULL;

	node1 = (np)malloc(sizeof(node));
	node2 = (np)malloc(sizeof(node));
	node3 = (np)malloc(sizeof(node));

	node1->data = 10;
	node1->next = node2;
	head = node1;

	node2->data = 20;
	node2->next = node3;

	node3->data = 30;
	node3->next = NULL;
	
	printf("Linked list before insertion:\n");
	print_list(head);

	insert_end(&head);

	printf("Linked list after insertion:\n");
	print_list(head);

	free(node1);
	free(node2);
	free(node3);

	return 0;
}
