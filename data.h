#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<double> ndBalai;
    double egzaminas;
    double galutBalas;
};


void generateAndWriteStudentRecords(const std::string &filename, int size);

void processStudentData(const std::string &filename, int size, int repetitions);

#endif
