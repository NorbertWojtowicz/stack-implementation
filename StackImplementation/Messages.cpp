#include "Messages.h"

char* getMessage(MESSAGES message)
{
	return (char*)MESSAGES_STRINGS[message];
}