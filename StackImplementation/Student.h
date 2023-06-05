#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

static const char* FIELD_OF_STUDY_STRINGS[] = { "IT", "MECHANICS", "MEDICINE", "ARCHITECTURE", "ART", "PSYCHOLOGY", "ENGINEERING", "OTHER" };
enum FIELD_OF_STUDY { IT, MECHANICS, MEDICINE, ARCHITECTURE, ART, PSYCHOLOGY, ENGINEERING, OTHER };

struct Student
{
	int birthYear;
	FIELD_OF_STUDY fieldOfStudy;
	char* surname;
};

Student* createStudent();
void printStudent(void* student);
void saveStudentToFile(void* student, FILE* file);
std::vector<void*> loadStudentsFromFile(FILE* file);
void freeStudent(void* student);