#include "StackInterface.h"
#include "Messages.h"
#include <cstdlib>
#include "Student.h"
#include <iostream>
#include "Stack.h"

void printInterfaceMenu()
{
	printf("1. Add new student\n");
	printf("2. Delete top student (pop())\n");
	printf("3. Get student from the top (top())\n");
	printf("4. Check if stack is empty\n");
	printf("5. Print whole stack\n");
	printf("6. Save Stack to the file\n");
	printf("7. Load stack from the file\n");
	printf("8. Free memory and exit\n");
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
	{
		StackNode* student = top(&stack);
		if (student == NULL)
		{
			printf("%s\n", getMessage(EMPTY_STACK));
			break;
		}
		printStackNode(student, printStudent);
		break;
	}
	case 4:
		printf("%s\n", isEmpty(&stack) == 1 ? "Stack is empty" : "Stack is not empty");
		break;
	case 5:
		printStack(&stack, printStudent);
		break;
	case 6:
	{
		FILE* file;
		if (stack.top == NULL) {
			printf("%s\n", getMessage(EMPTY_STACK));
			break;
		}
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
		if (file != NULL)
		{
			fclose(file);
		}
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