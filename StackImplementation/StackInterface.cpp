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
	printf("8. Find students by surname\n");
	printf("9. Find students by birth year\n");
	printf("10. Find students by field of study\n");
	printf("11. Free memory and exit\n");
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
	{
		char surname[20];
		printf("Enter surname: ");
		scanf_s("%s", surname, 20);
		Stack foundStudents = findByUsername(&stack, surname, compareStudentsBySurname);
		printSearchResult(foundStudents);
		freeStack(&foundStudents, freeStudent);
		break;
	}
	case 9:
	{
		int birthYear;
		printf("Enter birth year: ");
		scanf_s("%d", &birthYear);
		Stack foundStudents = findByYear(&stack, birthYear, compareStudentsByBirthYear);
		printSearchResult(foundStudents);
		freeStack(&foundStudents, freeStudent);
		break;
	}
	case 10:
	{
		int fieldOfStudy;
		printf("Enter field of study[0-7]:\n");
		for (int i = 0; i < 8; i++)
		{
			printf("%d. %s\n", i, FIELD_OF_STUDY_STRINGS[i]);
		}
		scanf_s("%d", &fieldOfStudy);
		Stack foundStudents = findByFieldOfStudy(&stack, fieldOfStudy, compareStudentsByFieldOfStudy);
		printSearchResult(foundStudents);
		freeStack(&foundStudents, freeStudent);
		break;
	}
	case 11:
		freeStack(&stack, freeStudent);
		printf("Stack freed\n");
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

void printSearchResult(Stack stack)
{
	if (stack.top != NULL)
	{
		printf("\nFound following students:\n");
		printStack(&stack, printStudent);
	}
	else
	{
		printf("No students found\n");
	}
}