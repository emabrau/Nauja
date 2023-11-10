#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "data.h"


Studentas generateRandomStudent(int studentoNumeris);


bool compareStudents(const Studentas &a, const Studentas &b);


void generateAndWriteStudentRecords(const std::string &filename, int size);

double Mediana(std::vector<double>& vec);
void GalutinisBalas(std::vector<Studentas>& studentai);
void displayTable(const std::vector<Studentas>& studentai);

#endif
