#pragma once
#include "StackNode.h"
#include <iostream>
#include <vector>

struct Stack {
	StackNode* top;
};

Stack createStack();
void push(Stack* stack, void* data);
int pop(Stack* stack);
int isEmpty(Stack* stack);
StackNode* top(Stack* stack);
void freeStack(Stack* stack);
void printStack(Stack* stack, void (*print)(void*));
void saveStackToFile(Stack* stack, FILE* file, void (*save)(void*, FILE*));
Stack loadStackFromFile(FILE* file, std::vector<void*>(*load)(FILE*));
