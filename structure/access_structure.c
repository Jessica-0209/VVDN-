#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Laptop
{
	float price;
	int pID;
	char name[30];
} Laptop1, *Laptop2;

int main()
{
	printf("Access members using variable:\n\n");
	Laptop1.price = 20899.21;
	Laptop1.pID = 234;
	strcpy(Laptop1.name, "Lenovo");

	printf("Laptop price: %.2f\n", Laptop1.price);
	printf("Laptop product ID: %d\n", Laptop1.pID);
	printf("Laptop name: %s\n", Laptop1.name);

	printf("\n\nAccess members using pointer:\n\n");

	Laptop2 = malloc(sizeof(struct Laptop));
	if(Laptop2 == NULL)
	{
		printf("Failed to allocate memory!");
		return -1;
	}

	Laptop2->price = 18999.00;
	Laptop2->pID = 231;
	strcpy(Laptop2->name, "Dell");

	printf("Laptop price: %.2f\n", Laptop2->price);
	printf("Laptop product ID: %d\n", Laptop2->pID);
	printf("Laptop name: %s\n", Laptop2->name);

	free(Laptop2);
	
	Laptop2 = NULL;

	return 0;
}
