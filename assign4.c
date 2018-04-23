//Gabriel Weigel, Mark Morrissey, assign4.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Dispatch table entry
typedef struct {
	char * name;
	void(*function)();
} dispatch_entry;

//convert each entry in $args to an int, then move it into $output
void numeric_convert(int size, char** args, int* output)
{
	for (int i = 0; i < (size-1); i++)
	{
		output[i] = strtol(args[i+1], NULL, 10);
		if (output[i] == 0)
		{
			output[i] = strtol(args[i+1], NULL, 16);
			if (output[i] == 0)
			{
				printf("\tBAD INPUT\n");
				exit(0);
			}
		}
	}
}

//passes off $args to be parsed than adds all elements
void addition(int size, char ** args) 
{
	int arr[size-1];
	int sum = 0;
	numeric_convert(size, args, arr);
	
	for (int i = 0; i < (size-1); i++)
	{
		sum += arr[i];
	}

	printf("Sum of addition: %d\n", sum);
}

//passes off $args to be parsed then subtracts all elements
void subtraction(int size, char ** args)
{
	int arr[size-1];
	numeric_convert(size, args, arr);
	int sum = arr[0];

	for (int i = 1; i < (size-1); i++)
	{
		sum -= arr[i];
	}

	printf("Product of subtraction: %d\n", sum);
}

//passes off $args to be parsed then multiplies all elements
void multiplication(int size, char ** args)
{
	int arr[size-1];
	int sum = 1;
	numeric_convert(size, args, arr);
	for (int i = 0; i < (size-1); i++)
	{
		sum *= arr[i];
	}

	printf("Product of multiplication: %d\n", sum);
}

//passes off $args to be parsed then divides all elements
void division(int size, char ** args)
{
	int arr[size-1];
	float sum;
	numeric_convert(size, args, arr);

	sum = (float) arr[0] / arr[1];
	printf("Product of division is: %f\n", sum);
}

//passes off $args to be parsed than modulo divides all elements
void modulo(int size, char ** args)
{
	int arr[size-1];
	int sum;
	numeric_convert(size, args, arr);

	sum = arr[0] % arr[1];
	printf("Product of modulo division is: %d\n", sum);
}

//reverses the order of of all the arguments in $args and prints them
void reverse(int size, char ** args)
{
	int length;
	for (int i = (size-1); i >= 1; i--)
	{
		length = strlen(args[i]);

		for (int j = length; j >= 0; j--)
		{
			printf("%c", *(args[i]+j));
		}
		printf(" ");
	}
	printf("\n");
}

//print the menu
void print_menu(int size, dispatch_entry * table)
{
	printf("\tChoices:\n");
	for (int i = 0; i < size; i++)
	{
		printf("\t%d: %s\n", i, table[i].name);
	}
}

int main (int argc, char ** argv)
{
	//ensure at least one but no more than 15 args
	if (argc < 2)
	{
		printf("Usage: assign4 [arg] ... [arg] (1 to 15 args accepted)\n");
		exit(0);
	}
	if (argc > 16)
	{
		printf("\tTOO MANY ARGS\n");
		exit(0);
	}

	//function dispatch table
	dispatch_entry d_table[] = {
		{"Exit", NULL},
		{"Addition", addition},
		{"Subtraction", subtraction},
		{"Multiplication", multiplication},
		{"Division", division},
		{"Modulo", modulo},
		{"Reverse Input", reverse}
	};
	int choice, size;
	//get the size of d_table
	size = sizeof(d_table)/(sizeof(d_table[0]));

	print_menu(size, d_table);

	//take in the users choice
	printf("\t%s", "$ ");
	if (scanf("%d", &choice) != 1)
	{
		printf("\t%s\n", "CHOICE INVALID");
		exit(0);
	}

	//call the function chosen via fdt, exit on 0 or out-of-bounds
	if (choice != 0 && choice < size)
	{
		//pass command line input to the function chosen
		d_table[choice].function(argc, argv);
	}

	exit(0);
}





