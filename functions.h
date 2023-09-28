#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <vector>
#include <string>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<double> ndBalai;
    double egzaminas;
    double galutinisBalas;
};

double Mediana(std::vector<double>& vec);
double generateRandomScore(double min, double max);
void inputStudentData(std::vector<Studentas>& studentai, char skaicMetodas);
void printStudentData(const std::vector<Studentas>& studentai);

#endif 
