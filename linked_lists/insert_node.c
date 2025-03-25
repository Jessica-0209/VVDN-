#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int data;
	struct Node* next;
};

typedef struct Node node, *np;

int count_nodes(np *head) 
{
    int count = 0;
    np temp = *head;
    while (temp != NULL) 
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

	np temp, newnode;
	for(int i = 0; i < n; i++)
	{
		newnode = (np)malloc(sizeof(node));
		printf("Enter value for node %d: ", i+1);
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

void insert_front(np *head)
{
	np newnode = (np)malloc(sizeof(node));
	printf("Enter value to insert: ");
	scanf("%d", &newnode->data);
	newnode->next = *head;
	*head = newnode;
}

void insert_end(np *head)
{
        np newnode = (np)malloc(sizeof(node));
	printf("Enter value to insert: ");
	scanf("%d", &newnode->data);
	newnode->next = NULL;


	np temp = *head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}

void insert_at_position(np *head, int pos)
{
	np newnode = (np)malloc(sizeof(node));
	printf("Enter value to insert at position %d: ", pos);
	scanf("%d", &newnode->data);

	if(pos == 1)
	{
		newnode->next = *head;
		*head = newnode;
		return;
	}

	np temp = *head;
	for(int i = 1; temp != NULL && i < pos - 1; i++)
	{
		temp = temp->next;
	}

	if(temp == NULL)
	{
		printf("Invalid position!\n");
		free(newnode);
		return;
	}
	newnode->next = temp->next;
	temp->next = newnode;
}

void print_list(np head)
{
	if(head == NULL)
	{
		printf("List is empty!\n");
		return;
	}

	np temp = head;
	printf("Linked list: ");
	while(temp != NULL)
	{
		printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

int main()
{
	np head = NULL;
	int choice, n, pos;

	while(1)
	{
		printf("\nMenu:\n\n");
		printf("1. Create List\n"); 
		printf("2. Insert node at beginning\n"); 
		printf("3. Insert node at the end\n");
		printf("4. Insert node at a position\n"); 
		printf("5. Display List\n");
		printf("6. Total number of nodes\n");
		printf("7. Exit\n");
		printf("Enter choice: ");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("Enter number of nodes:");
				scanf("%d", &n);
				create_list(&head, n);
				break;
			case 2:
				insert_front(&head);
				break;
			case 3:
				insert_end(&head);
				break;
			case 4:
				printf("Enter positon to insert: ");
				scanf("%d", &pos);
				insert_at_position(&head, pos);
				break;
			case 5:
                		print_list(head);
               			break;
			case 6:
				printf("Total number of nodes = %d\n",count_nodes(&head));
				break;
			case 7:
				printf("Exit!\n");
				return 0;
			default:
				printf("Invalid choice!\n");
		}
	}
}
