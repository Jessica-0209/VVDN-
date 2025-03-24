#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node Ntype, *Npointer;

void print_list(struct Node *pNode)
{
	int count = 0;
	while (pNode != NULL)
	{
     		printf("\nValue of %d Node = %d\n", ++count , pNode->data);
     		pNode = pNode->next;
  	}
}

int main()
{
	Npointer head = NULL;
	Npointer node1 = NULL;
	Npointer node2 = NULL;
	Npointer node3 = NULL;
	Npointer node4 = NULL;

	node1 = malloc(sizeof(Ntype));
	node2 = malloc(sizeof(Ntype));
	node3 = malloc(sizeof(Ntype));
	node4 = malloc(sizeof(Ntype));

	node1->data = 3;
	node1->next = node2;
	head = node1;

	node2->data = 12;
	node2->next = node3;

	node3->data = 23;
	node3->next = node4;

	node4->data = 32;
	node4->next = NULL;

	print_list(head);

	free(node1);
	node1 = NULL;

	free(node2);
	node2 = NULL;

	free(node3);
	node3 = NULL;

	free(node4);
	node4 = NULL;

	head = NULL;

	return 0;
}
