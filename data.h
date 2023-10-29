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


void generateAndWriteStudentRecordsV(const std::string &filename, int size);
void generateAndWriteStudentRecordsL(const std::string &filename, int size);

void processStudentDataV(const std::string &filename, int size, int repetitions);
void processStudentDataL(const std::string &filename, int size, int repetitions);

#endif
