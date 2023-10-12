#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "data.h"


Studentas generateRandomStudent(int studentoNumeris);


bool compareStudents(const Studentas &a, const Studentas &b);


void generateAndWriteStudentRecords(const std::string &filename, int size);



#endif
