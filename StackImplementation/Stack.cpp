#include "Stack.h"
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
		return 0;
	}
	StackNode* node = stack->top;
	stack->top = stack->top->next;
	delete node;
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

void freeStack(Stack* stack)
{
	while (stack->top != NULL)
	{
		pop(stack);
	}
	delete stack;
}

void printStack(Stack* stack, void (*print)(void*))
{
	StackNode* node = stack->top;
	while (node != NULL)
	{
		printStackNode(node, print);
		node = node->next;
	}
}

void saveStackToFile(Stack* stack, FILE* file, void (*save)(void*, FILE*))
{
	StackNode* node = stack->top;
	while (node != NULL)
	{
		save(node->data, file);
		node = node->next;
	}
}

Stack loadStackFromFile(FILE* file, std::vector<void*>(*load)(FILE*))
{
	Stack stack = createStack();
	std::vector<void*> data = load(file);
	for (int i = 0; i < data.size(); i++)
	{
		push(&stack, data[i]);
	}
	return stack;
}
