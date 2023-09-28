#include <iostream>
#include "functions.h"
#include "data.h"

int main() {
    std::vector<Studentas> studentai; 
    char skaicMetodas;
    std::string filename;

    std::cout << "Pasirinkite skaiciavimo metoda (V - Vidurkis, M - Mediana): ";
    std::cin >> skaicMetodas;

    std::cout << "Norite duomenis ivesti ranka (R) ar nuskaityti is failo (F)? ";
    char dataChoice;
    std::cin >> dataChoice;

    if (dataChoice == 'R' || dataChoice == 'r') {
        loadDataFromManualInput(studentai); 
    } else if (dataChoice == 'F' || dataChoice == 'f') {
        std::cout << "Iveskite failo pavadinima: ";
        std::cin >> filename;
        loadData(studentai, filename); 
    } else {
        std::cerr << "Netinkamas pasirinkimas. Programa baigia darba." << std::endl;
        return 1;
    }

    GalutinisBalas(studentai, skaicMetodas); 
    displayTable(studentai); 

    return 0;
}

