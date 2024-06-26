#include "Stack.h"
#include "Messages.h"
#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

Stack createStack()
{
	Stack* stack = new Stack();
	stack->top = NULL;
	return *stack;
}

void push(Stack* stack, void* data)
{
	StackNode* node = new StackNode();
	node->data = data;
	node->next = stack->top;
	stack->top = node;
}

int pop(Stack* stack)
{
	if (stack->top == NULL)
	{
		printf("%s\n", getMessage(EMPTY_STACK));
		return 0;
	}
	StackNode* node = stack->top;
	stack->top = stack->top->next;
	delete node;
	printf("Element popped\n");
	return 1;
}

int isEmpty(Stack* stack)
{
	return stack->top == NULL;
}

StackNode* top(Stack* stack)
{
	return stack->top;
}

void freeStack(Stack* stack, void (*freeEl)(void*))
{
	StackNode* node = stack->top;
	while (node != NULL)
	{
		StackNode* next = node->next;
		freeEl(node->data);
		delete node;
		node = next;
	}
	stack->top = NULL;
}

void printStack(Stack* stack, void (*print)(void*))
{
	StackNode* node = stack->top;
	if (node == NULL)
	{
		printf("%s\n", getMessage(EMPTY_STACK));
		return;
	}
	while (node != NULL)
	{
		printStackNode(node, print);
		node = node->next;
	}
}

void saveStackToFile(Stack* stack, FILE* file, void (*save)(void*, FILE*))
{
	if (file == NULL)
	{
		printf("%s\n", getMessage(FILE_NOT_FOUND));
		return;
	}
	StackNode* node = stack->top;
	if (node == NULL)
	{
		printf("%s\n", getMessage(EMPTY_STACK));
		return;
	}
	while (node != NULL)
	{
		save(node->data, file);
		node = node->next;
	}
	printf("Stack saved to file\n");
}

Stack loadStackFromFile(FILE* file, std::vector<void*>(*load)(FILE*))
{
	Stack stack = createStack();
	std::vector<void*> data = load(file);
	if (data.empty())
	{
		printf("%s\n", getMessage(FILE_NOT_FOUND));
		return stack;
	}
	for (int i = 0; i < data.size(); i++)
	{
		push(&stack, data[i]);
	}
	StackNode* node = stack.top;
	StackNode* prev = NULL;
	while (node != NULL)
	{
		StackNode* next = node->next;
		node->next = prev;
		prev = node;
		node = next;
	}
	stack.top = prev;
	printf("Stack loaded from file\n");
	return stack;
}

Stack findByUsername(Stack* stack, char* surname, int (*compare)(void*, char*))
{
	Stack result = createStack();
	StackNode* node = stack->top;
	while (node != NULL)
	{
		if (compare(node->data, surname))
		{
			push(&result, node->data);
		}
		node = node->next;
	}
	return result;
}

Stack findByYear(Stack* stack, int year, int (*compare)(void*, int))
{
	Stack result = createStack();
	StackNode* node = stack->top;
	while (node != NULL)
	{
		if (compare(node->data, year))
		{
			push(&result, node->data);
		}
		node = node->next;
	}
	return result;
}

Stack findByFieldOfStudy(Stack* stack, int year, int (*compare)(void*, int))
{
	Stack result = createStack();
	StackNode* node = stack->top;
	while (node != NULL)
	{
		if (compare(node->data, year))
		{
			push(&result, node->data);
		}
		node = node->next;
	}
	return result;
}