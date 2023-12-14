#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <vector>
#include "data.h"

class StudentFunctions {
public:
    StudentFunctions();
    ~StudentFunctions();
    static Studentas generateRandomStudent(int studentoNumeris);
    static bool compareStudents(const Studentas &a, const Studentas &b);
    static void generateAndWriteStudentRecords(const std::string &filename, int size);
    static double Mediana(std::vector<double>& vec);
    static void GalutinisBalas(std::vector<Studentas>& studentai);
    static void displayTable(const std::vector<Studentas>& studentai);
    static const int numNamuDarbu; 
};

#endif

