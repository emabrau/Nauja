#include "data.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip> 

void loadData(std::vector<Studentas>& studentai, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Nepavyko atidaryti failo " << filename << std::endl;
        return;
    }

    studentai.clear(); 
    std::string header;
    std::getline(file, header);

    std::string line;
    while (std::getline(file, line)) {
        Studentas studentas;
      
        std::istringstream iss(line);
        iss >> std::setw(15) >> studentas.vardas >> std::setw(15) >> studentas.pavarde;
        for (int i = 0; i < 15; ++i) {
            double balas;
            iss >> std::setw(8) >> balas; 
            studentas.ndBalai.push_back(balas);
        }
        iss >> studentas.egzaminas;

        studentai.push_back(studentas);
    }

    file.close();
}

