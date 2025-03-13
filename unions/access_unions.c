#include<stdio.h>
#include<string.h>
#include<stdlib.h>

union Book
{
	char name[30];
	char author[30];
	float price;
} book1, *book2;

int main()
{
	printf("Access variable:\n\n");
	
	strcpy(book1.name, "Southern Lights");
	//printf("Book name: %s\n", book1.name);

	strcpy(book1.author, "Danielle Steel");
	//printf("Author name: %s\n", book1.author);

	book1.price = 499;

	printf("Book name: %s\n", book1.name);
	printf("Author name: %s\n", book1.author);
	printf("Price of book: %.2f\n", book1.price);

	printf("THIS IS WHY WE DONT USE UNIONS FOR SUCH CASES. USE THEM ONLY IF YOU NEED TO STORE VALUES SEPARATELY AS EACH VARIABLE USE THE SAME MEMORY SPACE!!!");

	printf("\n\nAccess pointer:\n\n");

	book2 = malloc(sizeof(union Book));
	if(book2 == NULL)
	{
		printf("Failed to allocate memory");
		return -1;
	}

	strcpy(book2->name, "Kill the Father");
        printf("Book name: %s\n", book2->name);

        strcpy(book2->author, "Sandori Dazienori");
        printf("Author name: %s\n", book2->author);

        book2->price = 799;
        printf("Price of book: %.2f\n", book2->price);

	free(book2);
	book2 = NULL;

	return 0;
}
