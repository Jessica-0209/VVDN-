#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node node, *np;

void create_list(np *head, int n)
{
	if(*head != NULL)
	{
		printf("List exists!\n");
		return;
	}

	np temp;
	np newnode;

	for(int i = 0; i < n; i++)
	{
		newnode = (np)malloc(sizeof(node));

		printf("Enter value of node %d: ", i+1);
		scanf("%d", &newnode->data);
		newnode->next = NULL;

		if(*head == NULL)
		{
			*head = newnode;
			temp = newnode;
		}
		else
		{
			temp->next = newnode;
			temp = newnode;
		}
	}
}

void print_list(np *head)
{
	if(*head == NULL)
	{
		printf("List empty!\n");
		return;
	}

	np temp = *head;

	printf("Linked List: ");
	while(temp != NULL)
	{
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

void insert_node(np *head)
{
	np newnode = (np)malloc(sizeof(node));
	
	printf("Enter value to be inserted: ");
	scanf("%d", &newnode->data);

	newnode->next = *head;
	*head = newnode;
}

void delete_node(np *head)
{
	if(*head == NULL)
	{
		printf("List is empty!\n");
		return;
	}

	np temp = *head;
	*head = (*head)->next;
	free(temp);
}

void delete_without_head(np Node)
{
	np temp = Node->next;
	Node->data = temp->data;
	Node->next = temp->next;
	free(temp);
}

int main()
{
	int n = 0;

	np head = NULL;

	printf("Enter number of nodes: ");
	scanf("%d", &n);
	
	create_list(&head, n);
	np temp;

	if(temp == NULL)
	{
		printf("List is empty!\n");
		return 0;
	}

	printf("Linked list: ");
	print_list(head);

	delete_without_head(head);
	printf("List after deleting without head pointer: ");
	print_list(head);

	return 0;
}
