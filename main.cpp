#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "functions.h"
#include "data.h"

using namespace std;

int main() {
    try {
        generateStudentDataFile("student_data_1000.txt", 1000);
        generateStudentDataFile("student_data_10000.txt", 10000);
        generateStudentDataFile("student_data_100000.txt", 100000);
        generateStudentDataFile("student_data_1000000.txt", 1000000);
        generateStudentDataFile("student_data_10000000.txt", 10000000);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}











