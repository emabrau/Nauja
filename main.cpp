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

    try {
        chooseDataInputMethod(studentai); 
        
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












