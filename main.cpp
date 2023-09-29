#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "functions.h"
#include "data.h"
#include <stdexcept>

using namespace std;

int main() {
    std::vector<Studentas> studentai; 
    std::string filename;

    try {
        std::cout << "Norite duomenis ivesti ranka (R) ar nuskaityti is failo (F)? ";
        char dataChoice;
        std::cin >> dataChoice;

        if (dataChoice == 'R' || dataChoice == 'r') {
            loadDataFromManualInput(studentai); 
        } else if (dataChoice == 'F' || dataChoice == 'f') {
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> filename; 
          try {
                loadData(studentai, filename);
            } catch (const std::ifstream::failure& e) {
                std::cerr << "Error: Nepavyko atidaryti failo." << std::endl;
                throw;  
            }
        } else {
            throw std::invalid_argument("Netinkamas pasirinkimas.");
        }
            
        GalutinisBalas(studentai); 

        std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
        });
      
        displayTable(studentai); 
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}






