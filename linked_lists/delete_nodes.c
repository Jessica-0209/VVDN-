#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node node, *np;

int count_node(np *head)
{
	int count = 0;
	np temp = *head;

	while(temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

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
		printf("Enter value for node %d: ", i + 1);
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

void print_list(np *head, int n)
{
	np temp = *head;
	if(*head == NULL)
	{
		printf("List is empty!\n");
		return;
	}

	printf("Linked List: ");
	while(temp->next != NULL)
	{
		printf("%d -> ", temp->data);
		temp = temp->next;
	}

	printf("%d\n", temp->data); 
	printf("Last node = %d\n", temp->data);

	printf("NULL\n");

}

void delete_front(np *head)
{
	if(*head == NULL)
	{
		printf("List is already empty!\n");
		return;
	}

	np temp = *head;
	*head = (*head)->next;
	free(temp);
}

void delete_end(np *head)
{
	if(*head == NULL)
	{
		printf("List is already empty!\n");
		return;
	}

	if((*head)->next == NULL)
	{
		free(*head);
		*head = NULL;
		return;
	}

	np temp = *head;
	while(temp->next->next != NULL)
	{
		temp = temp->next;
	}
	free(temp->next);
	temp->next = NULL;
}

void delete_at_position(np *head, int pos)
{
	if(*head == NULL)
	{
		printf("List is already empty!\n");
		return;
	}

	np temp = *head;
	if(pos == 1)
	{
		printf("Choose 2nd option from the Menu to delete first node!\n");
		return;
	}

	np prev = NULL;
	for(int i = 1; temp != NULL && i <= pos; i++)
	{
		if(prev != NULL)
		{
			printf("prev=%d\n", prev->data);
		}
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL)
	{
		printf("Invalid position!\n");
		return;
	}

	prev->next = temp->next;
	free(temp);
}

int main()
{
	np head = NULL;
	int choice;
	int n;
	int pos;

	while(1)
	{
		printf("\nMENU\n");
        	printf("1. Create List\n");
        	printf("2. Delete from beginning\n");
        	printf("3. Delete from end\n");
        	printf("4. Delete at position\n");
        	printf("5. Print list\n");
		printf("6. Total number of nodes\n");
        	printf("7. Exit\n");
        	printf("Enter your choice: ");
        	scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter number of nodes: ");
				scanf("%d", &n);
				create_list(&head, n);
				break;
			case 2:
				delete_front(&head);
				break;
			case 3:
				delete_end(&head);
				break;
			case 4:
				printf("Enter position to be deleted: ");
				scanf("%d", &pos);
				delete_at_position(&head, pos);
				break;
			case 5:
				print_list(&head, n);
				break;
			case 6:
				printf("Total number of nodes = %d\n", count_node(&head));
				break;
			case 7:
				printf("Exit!\n");
				return 0;
			default:
				printf("Invalid choice!\n");
		}
	}
}
