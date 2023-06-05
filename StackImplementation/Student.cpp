#include "Student.h"
#include <iostream>
#include <cstring>

Student* createStudent()
{
	Student* student = new Student();
	std::cout << "Enter birth year: ";
	std::cin >> student->birthYear;
	std::cout << "Enter field of study:\n";
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
	std::cout << "Surname: " << s->surname << std::endl;
}

void saveStudentToFile(void* student, FILE* file)
{
	Student* s = (Student*)student;
	fwrite(&s->birthYear, sizeof(int), 1, file);
	fwrite(&s->fieldOfStudy, sizeof(FIELD_OF_STUDY), 1, file);
	size_t surnameLength = strlen(s->surname);
	fwrite(&surnameLength, sizeof(size_t), 1, file);
	fwrite(s->surname, sizeof(char), surnameLength, file);
}

std::vector<void*> loadStudentsFromFile(FILE* file)
{
	std::vector<void*> students;
	while (!feof(file))
	{
		Student* s = new Student();
		fread(&s->birthYear, sizeof(int), 1, file);
		fread(&s->fieldOfStudy, sizeof(FIELD_OF_STUDY), 1, file);
		size_t surnameLength;
		fread(&surnameLength, sizeof(size_t), 1, file);
		s->surname = new char[surnameLength + 1];
		fread(s->surname, sizeof(char), surnameLength, file);
		s->surname[surnameLength] = '\0';
		students.push_back(s);
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
