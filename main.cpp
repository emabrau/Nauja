 #include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 #include <cstdlib>
 #include <ctime>
 #include <iomanip>
 #include <algorithm>
 #include "data.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> recordSizes = {1000, 10000, 100000, 1000000, 10000000};
    int repetitions = 5;  

    for (int size : recordSizes) {
        std::string filename = "studentai_" + std::to_string(size) + ".txt";

        generateAndWriteStudentRecords(filename, size);

        processStudentData(filename, size, repetitions);
    }

    return 0;
}








