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

     for (int size : recordSizes) {
         std::string filename = "students_" + std::to_string(size) + ".txt";

         
         generateAndWriteStudentRecords(filename, size);

         
         processStudentData(filename);
     }

     return 0;
 }











