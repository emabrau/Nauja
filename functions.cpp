#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "data.h"

const int numNamuDarbu = 10; 
Studentas generateRandomStudent(int studentoNumeris) {
    Studentas student;
    student.vardas = "Vardas" + std::to_string(studentoNumeris);
    student.pavarde = "Pavarde" + std::to_string(studentoNumeris);

    double totalNamuDarbu = 0.0;
    for (int i = 0; i < numNamuDarbu; ++i) {
        double ndbalas = static_cast<double>(rand() % 11);  
        student.ndBalai.push_back(ndbalas);
        totalNamuDarbu += ndbalas;
    }

    student.egzaminas = rand() % 11;  
    student.galutBalas = (totalNamuDarbu / numNamuDarbu) * 0.4 + student.egzaminas * 0.6;

    return student;
}


bool compareStudents(const Studentas &a, const Studentas &b) {
    
    int studentoNumerisA = std::stoi(a.vardas.substr(6)); 
    int studentoNumerisB= std::stoi(b.vardas.substr(6));

    
    return studentoNumerisA > studentoNumerisB;
}



