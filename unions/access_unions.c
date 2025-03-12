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
	printf("Book name: %s\n", book1.name);

	strcpy(book1.author, "Danielle Steel");
	printf("Author name: %s\n", book1.author);

	book1.price = 499;
	printf("Price of book: %.2f\n", book1.price);

	printf("\n\nAccess pointer:\n\n");

	book2 = 
