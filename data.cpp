#include "data.h"
#include "functions.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>

using namespace std;


void loadData(std::vector<Studentas>& studentai, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Nepavyko atidaryti failo " + filename);
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
    } catch (const std::exception& e) {
        throw e;
    }
}

void loadDataFromManualInput(std::vector<Studentas>& studentai) {
    try {
        while (true) {
            Studentas studentas;

            std::cout << "Iveskite studento varda (noredami baigti spauskite Enter): ";
            std::cin.ignore(); 
            getline(std::cin, studentas.vardas);

            if (studentas.vardas.empty()) {
                break;
            }

            std::cout << "Iveskite studento pavarde: ";
            getline(std::cin, studentas.pavarde);

            double ndBalai;
            std::cout << "Iveskite studento " << studentas.vardas << " " << studentas.pavarde << " namu darbu balus " << " " << " (Noredami baigti spauskite Enter):\n";
            while (true) {
                std::string input;
                getline(std::cin, input);

                if (input.empty()) {
                    break; 
                }

                ndBalai = std::stod(input);
                studentas.ndBalai.push_back(ndBalai);
            }

            std::cout << "Iveskite studento " << studentas.vardas << " " << studentas.pavarde << " egzamino rezultata: ";
            std::cin >> studentas.egzaminas;

            studentai.push_back(studentas);
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void generateStudentDataFile(const std::string& filename, int numRecords) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (int i = 1; i <= numRecords; ++i) {
        Studentas studentas;

        studentas.vardas = "Vardas" + std::to_string(i);
        studentas.pavarde = "Pavarde" + std::to_string(i);

        for (int j = 0; j < 15; ++j) {
            int balas = rand() % 10 + 1;
            studentas.ndBalai.push_back(static_cast<double>(balas)); 
        }
        int egzaminas = rand() % 10 + 1;
        studentas.egzaminas = static_cast<double>(egzaminas); 

        double sumHomework = 0.0;
        for (double score : studentas.ndBalai) {
            sumHomework += score;
        }

       
        float vidurkis = 0.4 * (sumHomework / 15) + 0.6 * studentas.egzaminas;
        studentas.galutBalasVid = vidurkis;

        file << studentas.vardas << " " << studentas.pavarde << " ";
        for (double score : studentas.ndBalai) {
            file << score << " ";
        }
        file << studentas.egzaminas << " " << studentas.galutBalasVid << "\n";
    }

    file.close();
}




void processStudentData(const std::string& filename) {
    std::vector<Studentas> studentai;
    loadData(studentai, filename);
    GalutinisBalas(studentai);
    displayTable(studentai);
}
