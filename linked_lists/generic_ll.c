#include<stdio.h>
#include<stdlib.h>

struct Node
{
	void *data;
	struct Node *next;
};

typedef struct Node node, *np;

void insert(np *head, void *new)
{
	np new = (np)malloc(sizeof(node));

	new->data = new;
	new->next = *head;
	*head = new;
}

void print_int(void *data)
{
	printf("%d -> ", *(int*)data);
}

void print_float(void *data)
{
	printf("%.2f -> ", *(float*)data);
}

void print_list(

int main()
{

	np int_list = NULL;
	np float_list = NULL;


