#include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <iomanip>
 #include <algorithm>
 #include "data.h"
#include <list>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::string choice;
    std::cout << "Pasirinkinte duomenu struktura (v - vektorius, l - listas): ";
    std::cin >> choice;

    if (choice == "v") {
        std::vector<int> recordSizes = {1000, 10000, 100000, 1000000, 10000000};
        int repetitions = 5;

        for (int size : recordSizes) {
            std::string filename = "studentai_" + std::to_string(size) + ".txt";

            generateAndWriteStudentRecordsV(filename, size);
            processStudentDataV(filename, size, repetitions);
        }
    } else if (choice == "l") {
         std::list<int> recordSizes = {1000, 10000, 100000, 1000000, 10000000};
        int repetitions = 5;

        for (int size : recordSizes) {
            std::string filename = "studentai_" + std::to_string(size) + ".txt";

            generateAndWriteStudentRecordsL(filename, size);
            processStudentDataL(filename, size, repetitions);
        }
    } else {
        std::cout << "Netinkamas pasirinkimas. Prasau pasirinkti 'v' arba 'l'." << std::endl;
    }

    return 0;
}








