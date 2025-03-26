#include<stdio.h>
#include<stdlib.h>

struct Node
{
        int data;
        struct Node* next;
};

typedef struct Node node, *np;

void push(np *top, int value)
{
        np newnode = (np)malloc(sizeof(node));
        if(!newnode)
        {
                printf("Stack Overflow!\n");
                return;
        }

        newnode->data = value;
        newnode->next = *top;
        *top = newnode;

        printf("Pushed: %d\n", value);
}

int pop(np *top)
{
        if(*top == NULL)
        {
                printf("Stack Underflow!\n");
                return -1;
        }

        np temp = *top;

        int popped = temp->data;
        *top = temp->next;

        free(temp);
        return popped;
}

int peek(np top)
{
        if(top == NULL)
        {
                printf("Stack is empty!\n");
                return -1;
        }
        return top->data;
}

void display(np top)
{
        if(top == NULL)
        {
                printf("Stack is empty!\n");
                return;
        }

        printf("Stack elements: ");
        while(top != NULL)
        {
                printf("%d -> ", top->data);
                top = top->next;
        }
        printf("NULL\n");
}

int main()
{
        np top = NULL;
        int choice;
	int value;

        while(1)
        {
                printf("\nMenu\n");
                printf("1. Push\n2. Pop\n3. Peek\n4. Display\n5. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice)
                {
                        case 1:
                                printf("Enter value to push: ");
                                scanf("%d", &value);
                                push(&top, value);
                                break;
                        case 2:
                               // if(value != -1)
                                //{
                                printf("Popped: %d\n", pop(&top));
                               // }
                                break;
			case 3:
				printf("Top element: %d\n", peek(top));
				break;
                        case 4:
                                display(top);
                                break;
                        case 5:
                                printf("Exit!\n");
                                return;
                        default:
                                printf("Invalid choice!\n");
                }
        }
        return 0;
}

