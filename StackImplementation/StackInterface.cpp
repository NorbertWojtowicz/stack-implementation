#include "StackInterface.h"
#include <cstdlib>
#include "Student.h"
#include <iostream>
#include "Stack.h"

void printInterfaceMenu()
{
	printf("1. Push\n");
	printf("2. Pop\n");
	printf("3. Top\n");
	printf("4. Is empty\n");
	printf("5. Print\n");
	printf("6. Save to file\n");
	printf("7. Load from file\n");
	printf("8. Exit\n");
}

void handleUserInput(Stack &stack)
{
	int choice;
	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		push(&stack, createStudent());
		break;
	case 2:
		pop(&stack);
		break;
	case 3:
		printStackNode(top(&stack), printStudent);
		break;
	case 4:
		printf("%d\n", isEmpty(&stack));
		break;
	case 5:
		printStack(&stack, printStudent);
		break;
	case 6:
	{
		FILE* file;
		fopen_s(&file, "students.bin", "wb");
		saveStackToFile(&stack, file, saveStudentToFile);
		fclose(file);
		break;
	}
	case 7:
	{
		FILE* file;
		fopen_s(&file, "students.bin", "rb");
		stack = loadStackFromFile(file, loadStudentsFromFile);
		fclose(file);
		break;
	}
	case 8:
		freeStack(&stack);
		exit(0);
		break;
	default:
		break;
	}
}

void runInterface()
{
	Stack stack = createStack();
	std::cout << "Empty stack initialized\n";
	std::cout << "Please, enter your first choice:\n";
	while (1)
	{
		printInterfaceMenu();
		handleUserInput(stack);
	}
}