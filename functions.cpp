#include "functions.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> 
#include <random>
#include <string>    

double Mediana(std::vector<double>& vec) {
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

double generateRandomScore(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

void inputStudentData(std::vector<Studentas>& studentai, char skaicMetodas) {
    while (true) {
        Studentas studentas;

        std::cout << "Iveskite studento varda (Noredami baigti spauskite Enter): ";
        std::cin.ignore();
        std::getline(std::cin, studentas.vardas);

        if (studentas.vardas.empty()) {
            break;
        }

        std::cout << "Iveskite studento pavarde: ";
        std::getline(std::cin, studentas.pavarde);

        char generuoti;
        std::cout << "Ar norite, kad studento balai butu generuojami atsitiktinai? " << studentas.vardas << " " << studentas.pavarde << "? (T/N): ";
        std::cin >> generuoti;

        if (generuoti == 'T' || generuoti == 't') {
            int numND;
            std::cout << "Iveskite namu darbu skaiciu: ";
            std::cin >> numND;

            std::cout << "Atsitiktinai sugeneruoti studento namu darbu balai:  " << studentas.vardas << " " << studentas.pavarde << ":\n";
            for (int j = 0; j < numND; ++j) {
                double randomScore = generateRandomScore(0.0, 10.0);
                studentas.ndBalai.push_back(randomScore);

                std::cout << "ND " << j + 1 << ": " << std::fixed << std::setprecision(2) << randomScore << std::endl;
            }

            studentas.egzaminas = generateRandomScore(0.0, 10.0);

            std::cout << "Atsitiktinai sugeneruotas studento egzamino balas " << studentas.vardas << " " << studentas.pavarde << ": " << std::fixed << std::setprecision(2) << studentas.egzaminas << std::endl;
        } else {
            std::cout << "Iveskite studento namu darbu ivertinimus  " << studentas.vardas << " " << studentas.pavarde << " (Noredami baigti spauskite Enter):\n";
            while (true) {
                double ndBalas;
                std::cin >> ndBalas;
                if (ndBalas < 0.0 || ndBalas > 10.0) {
                    std::cout << "Namu darbu ivertinimas turi buti tarp 0 ir 10. Iveskite vel: ";
                    continue;
                }
                studentas.ndBalai.push_back(ndBalas);

                char nextChar = std::cin.get();
                if (nextChar == '\n') {
                    break;
                }
            }

           
            std::cout << "Iveskite studento egzamino bala  " << studentas.vardas << " " << studentas.pavarde << ": ";
            std::cin >> studentas.egzaminas;
        }

        if (skaicMetodas == 'V' || skaicMetodas == 'v') {
            studentas.galutinisBalas = 0.4 * (std::accumulate(studentas.ndBalai.begin(), studentas.ndBalai.end(), 0.0) / studentas.ndBalai.size()) + 0.6 * studentas.egzaminas;
        } else if (skaicMetodas == 'M' || skaicMetodas == 'm') {
            studentas.galutinisBalas = 0.4 * (Mediana(studentas.ndBalai)) + 0.6 * studentas.egzaminas;
        } else {
            std::cout << "Neteisingas skaiciavimo metodas. Pasirinkite V arba M." << std::endl;
            return;
        }

        studentai.push_back(studentas);
    }
}

void printStudentData(const std::vector<Studentas>& studentai) {
    std::cout << std::left << std::setw(15) << "Vardas" << std::setw(15) << "Pavarde" << std::setw(15) << "Galutinis balas" << std::endl;
    std::cout << std::string(45, '-') << std::endl;

    for (const Studentas& studentas : studentai) {
        std::cout << std::left << std::setw(15) << studentas.vardas << std::setw(15) << studentas.pavarde << std::setw(15) << std::fixed << std::setprecision(2) << studentas.galutinisBalas << std::endl;
    }
}
