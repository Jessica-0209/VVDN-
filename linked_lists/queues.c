#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
        int data;
        struct Node* next;
} node, *np;

typedef struct Queue
{
        np front;
        np rear;
} queue;

void enqueue(queue *q, int value)
{
        np newnode = (np)malloc(sizeof(node));
        newnode->data = value;
        newnode->next= NULL; //since we are adding at the end it has to be NULL 

        if(q->rear == NULL)
        {
                q->front = q->rear = newnode;
                return;
        }

        q->rear->next = newnode; //making the current rear to point to the new node.
        q->rear = newnode; //assigning new node value to the rear.
}

void dequeue(queue *q)
{
        if(q->front == NULL)
        {
                printf("Queue empty!\n");
                return;
        }

        np temp = q->front;
        printf("Dequeued: %d\n", temp->data);
        q->front = q->front->next;

        if(q->front == NULL)
        {
                q->rear = NULL;
        }

        free(temp);
}

void display(queue *q)
{
        if(q->front == NULL)
        {
                printf("Queue is empty!\n");
                return;
        }

        np temp = q->front;
        printf("Queue: ");
        while(temp)
        {
                printf("%d -> ", temp->data);
                temp = temp->next;
        }
        printf("NULL\n");
}

int main()
{
        queue *q = (queue*)malloc(sizeof(queue));
        q->front = NULL;
        q->rear = NULL;

        int choice;
        int value;

        while(1)
        {
                printf("\nMenu\n");
                printf("1. Insert to queue\n2. Delete from queue\n3. Display queue\n4. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice)
                {
                        case 1:
                                printf("Enter value to enqueue: ");
                                scanf("%d", &value);
                                enqueue(q, value);
                                break;
                        case 2:
                                dequeue(q);
                                break;
                        case 3:
                                display(q);
                                break;
                        case 4:
                                printf("Exit!\n");
                                return 0;
                        default:
                                printf("Invalid choice!\n");
                                break;
                }
        }
        return 0;
}

