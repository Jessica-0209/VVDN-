#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Book
{
	char Bname[30];
	char Aname[30];
	float price;
} Book1, *Book2;

int main()
{
	printf("Access using variable:\n\n");

	strcpy(Book1.Bname, "Kill The Father");
	strcpy(Book1.Aname, "Sandrone Dazieri");
	Book1.price = 799.0;

	printf("Book Name: %s\n", Book1.Bname);
	printf("Author Name: %s\n", Book1.Aname);
	printf("Price of Book: %.2f\n", Book1.price);

	Book2 = malloc(sizeof(struct Book));
	if(Book2 == NULL)
	{
		printf("Failed to allocate memory!\n");
		return -1;
	}

	printf("\nAccess using pointer:\n\n");

	strcpy(Book2->Bname, "Silent Patient");
	strcpy(Book2->Aname, "Alex Michaelides");
	Book2->price = 699.0;

	printf("Book Name: %s\n", Book2->Bname);
	printf("Author Name: %s\n", Book2->Aname);
	printf("Price of Book: %.2f\n", Book2->price);

	free(Book2);

	Book2 = NULL;

	return 0;
}
