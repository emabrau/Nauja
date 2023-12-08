#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include "data.h"
#include "functions.h"

StudentFunctions::StudentFunctions() {}

StudentFunctions::~StudentFunctions() {}

const int StudentFunctions::numNamuDarbu = 10;

Studentas StudentFunctions::generateRandomStudent(int studentoNumeris) {
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

bool StudentFunctions::compareStudents(const Studentas &a, const Studentas &b) {
    int studentoNumerisA = std::stoi(a.vardas.substr(6));
    int studentoNumerisB = std::stoi(b.vardas.substr(6));

    return studentoNumerisA > studentoNumerisB;
}

double StudentFunctions::Mediana(std::vector<double>& vec) {
    size_t size = vec.size();
    if (size == 0) {
        return 0.0;
    }
    std::sort(vec.begin(), vec.end());
    if (size % 2 == 0) {
        return (vec[size / 2 - 1] + vec[size / 2]) / 2.0;
    } else {
        return vec[size / 2];
    }
}

void StudentFunctions::GalutinisBalas(std::vector<Studentas>& studentai) {
    for (Studentas& studentas : studentai) {
        double vidurkis = 0.4 * (std::accumulate(studentas.ndBalai.begin(), studentas.ndBalai.end(), 0.0) / studentas.ndBalai.size()) + 0.6 * studentas.egzaminas;
        double mediana = 0.4 * Mediana(studentas.ndBalai) + 0.6 * studentas.egzaminas;
        studentas.galutBalasVid = vidurkis;
        studentas.galutBalasMed = mediana;
    }
}

void StudentFunctions::displayTable(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis (Vid)" << std::setw(20) << "Galutinis (Med)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const auto& student : studentai) {
        std::cout << student << std::endl;
    }
}
