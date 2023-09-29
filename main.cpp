#include <iostream>
#include <algorithm>
#include "functions.h"
#include "data.h"

int main() {
    std::vector<Studentas> studentai; 
    std::string filename;

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
        std::cerr << "Netinkamas pasirinkimas. Programa baigia darba." << 
    std::endl;
        return 1;
    }

    GalutinisBalas(studentai); 

    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, 
    const Studentas& b) {
        return a.vardas < b.vardas;
    });
  
    displayTable(studentai); 

    return 0;
}
