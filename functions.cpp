#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include "functions.h"

double Mediana(std::vector<double>& vec) {
    size_t size = vec.size();
    if (size == 0) {
        return 0.0;
    }
    sort(vec.begin(), vec.end());
    if (size % 2 == 0) {
       
        return (vec[size / 2 - 1] + vec[size / 2]) / 2.0;
    } else {
        
        return vec[size / 2];
    }
}

void GalutinisBalas(std::vector<Studentas>& studentai) {
    for (Studentas& studentas : studentai) {
        double vidurkis = 0.4 * (std::accumulate(studentas.ndBalai.begin(), studentas.ndBalai.end(), 0.0) / studentas.ndBalai.size()) + 0.6 * studentas.egzaminas;
        double mediana = 0.4 * Mediana(studentas.ndBalai) + 0.6 * studentas.egzaminas;
        studentas.galutBalasVid = vidurkis;
        studentas.galutBalasMed = mediana;
    }
}

void displayTable(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(20) << "Galutinis (Vid)" << std::setw(20) << "Galutinis (Med)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const Studentas& studentas : studentai) {
        std::cout << std::left << std::setw(15) << studentas.vardas << std::setw(15) << studentas.pavarde
                  << std::fixed << std::setprecision(2) << std::setw(20) << studentas.galutBalasVid << std::setw(20) << studentas.galutBalasMed << std::endl;
    }
}


void loadDataFromManualInput(std::vector<Studentas>& studentai) {
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
        std::cout << "Iveskite studento namu darbu balus " << studentas.vardas << " " << studentas.pavarde << " (Noredami baigti spauskite Enter):\n";
        while (true) {
            std::string input;
            getline(std::cin, input);

            if (input.empty()) {
                break; 
            }

            ndBalai = std::stod(input);
            studentas.ndBalai.push_back(ndBalai);
        }

        std::cout << "Iveskite studento egzamino rezultata " << studentas.vardas << " " << studentas.pavarde << ": ";
        std::cin >> studentas.egzaminas;

        studentai.push_back(studentas);
    }
}
