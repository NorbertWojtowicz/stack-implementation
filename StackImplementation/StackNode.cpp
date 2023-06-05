#include "StackNode.h"

void printStackNode(StackNode* node, void (*print)(void*))
{
	print(node->data);
}
