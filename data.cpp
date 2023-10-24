#include "data.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>


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

void chooseDataInputMethod(std::vector<Studentas>& studentai) {
    try {
        char dataChoice;
        std::cout << "Norite duomenis ivesti ranka (R), nuskaityti is failo (F), ar sugeneruoti atsitiktinius duomenis (G)? ";
        std::cin >> dataChoice;

        if (dataChoice == 'R' || dataChoice == 'r') {
            loadDataFromManualInput(studentai);
        } else if (dataChoice == 'F' || dataChoice == 'f') {
            std::string filename;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> filename;
            try {
                loadData(studentai, filename);
            } catch (const std::ifstream::failure& e) {
                std::cerr << "Error: Nepavyko atidaryti failo." << std::endl;
                throw;
            }
        } else if (dataChoice == 'G' || dataChoice == 'g') {
            int count;
            std::cout << "Iveskite norimu sugeneruoti studentu skaiciu: ";
            std::cin >> count;
            generateRandomData(studentai, count);
        } else {
            throw std::invalid_argument("Netinkamas pasirinkimas.");
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void generateRandomData(std::vector<Studentas>& studentai, int count) {
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        Studentas studentas;
        studentas.vardas = "Vardas" + std::to_string(i);
        studentas.pavarde = "Pavarde" + std::to_string(i);
        for (int j = 0; j < 5; ++j) {
            studentas.ndBalai.push_back((rand() % 10) + 1);
        }
        studentas.egzaminas = rand() % 10 + 1;
        studentai.push_back(studentas);
    }
}

