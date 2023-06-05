#pragma once

struct StackNode
{
	void* data;
	StackNode* next;
};

void printStackNode(StackNode* node, void (*print)(void*));
