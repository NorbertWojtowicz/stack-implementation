#include "Student.h"
#include <iostream>
#include <cstring>
#include <vector>

Student* createStudent()
{
	Student* student = new Student();
	std::cout << "Enter birth year: ";
	std::cin >> student->birthYear;
	std::cout << "Enter field of study[0-7]:\n";
	for (int i = 0; i <= OTHER; i++)
	{
		std::cout << i << " - " << FIELD_OF_STUDY_STRINGS[i] << std::endl;
	}
	int fieldOfStudy;
	std::cin >> fieldOfStudy;
	student->fieldOfStudy = (FIELD_OF_STUDY)fieldOfStudy;
	std::cout << "Enter surname: ";
	char surname[100];
	std::cin >> surname;
	size_t surnameLength = strlen(surname);
	student->surname = new char[surnameLength + 1];
	strcpy_s(student->surname, surnameLength + 1, surname);
	return student;
}

void printStudent(void* student)
{
	Student* s = (Student*)student;
	std::cout << "Birth year: " << s->birthYear << std::endl;
	std::cout << "Field of study: " << FIELD_OF_STUDY_STRINGS[s->fieldOfStudy] << std::endl;
	std::cout << "Surname: " << s->surname << std::endl << std::endl;
}

void saveStudentToFile(void* student, FILE* file)
{
	Student* s = (Student*)student;
	if (student == NULL || file == NULL)
	{
		return;
	}
	fwrite(&s->birthYear, sizeof(int), 1, file);
	fwrite(&s->fieldOfStudy, sizeof(FIELD_OF_STUDY), 1, file);
	size_t surnameLength = strlen(s->surname);
	fwrite(&surnameLength, sizeof(size_t), 1, file);
	fwrite(s->surname, sizeof(char), surnameLength, file);
}

std::vector<void*> loadStudentsFromFile(FILE* file)
{
	std::vector<void*> students;
	if (file == NULL)
	{
		return students;
	}
	while (!feof(file))
	{
		Student* student = new Student();
		fread(&student->birthYear, sizeof(int), 1, file);
		fread(&student->fieldOfStudy, sizeof(FIELD_OF_STUDY), 1, file);
		size_t surnameLength;
		fread(&surnameLength, sizeof(size_t), 1, file);
		student->surname = new char[surnameLength + 1];
		fread(student->surname, sizeof(char), surnameLength, file);
		student->surname[surnameLength] = '\0';
		students.push_back(student);
	}
	students.pop_back();
	return students;
}

void freeStudent(void* student)
{
	Student* s = (Student*)student;
	delete[] s->surname;
	delete s;
}

int compareStudentsBySurname(void* student1, char* student2Surname)
{
	Student* s1 = (Student*)student1;
	return strcmp(s1->surname, student2Surname) == 0;
}

int compareStudentsByBirthYear(void* student1, int student2BirthYear)
{
	Student* s1 = (Student*)student1;
	return s1->birthYear == student2BirthYear;
}

int compareStudentsByFieldOfStudy(void* student1, int student2FieldOfStudy)
{
	Student* s1 = (Student*)student1;
	return s1->fieldOfStudy == student2FieldOfStudy;
}
