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
    double galutBalasMed;
    double galutBalasVid;
};

void loadData(std::vector<Studentas>& studentai, const std::string& filename);
void loadDataFromManualInput(std::vector<Studentas>& studentai);
void chooseDataInputMethod(std::vector<Studentas>& studentai);
void generateRandomData(std::vector<Studentas>& studentai, int count);
#endif
