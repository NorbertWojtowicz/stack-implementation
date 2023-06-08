#pragma once
static const char* MESSAGES_STRINGS[] = { "Cannot open the file...", "Stack is empty...", "No data found in file..."};
enum MESSAGES { FILE_NOT_FOUND, EMPTY_STACK, EMPTY_FILE };

char* getMessage(MESSAGES message);