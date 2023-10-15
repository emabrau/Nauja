#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include "data.h"
#include "functions.h"
#include <chrono>
#include <numeric>



void generateAndWriteStudentRecords(const std::string &filename, int size) {
   auto startTime = std::chrono::high_resolution_clock::now();
    std::ofstream outFile(filename);

  std::vector<Studentas> students;
  students.reserve(size);
  
    for (int i = size; i >= 1; --i) {
        Studentas student = generateRandomStudent(i);
        outFile << student.vardas << " " << student.pavarde;
        for (double score : student.ndBalai) {
            outFile << " " << score;
        }
        outFile << " " << student.egzaminas << " " << student.galutBalas << std::endl;
    }
    outFile.close();

   auto endTime = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
  
  std::cout << "Laikas, per kuri sugeneravo " << filename << ": " << duration.count() /1000 << " s" << std::endl;
}


void processStudentData(const std::string &filename, int size, int repetitions) {
    std::vector<double> readTimes;
    std::vector<double> sortTimes;
    std::vector<double> writeTimes;

    for (int rep = 0; rep < repetitions; ++rep) {
        auto startTimeReading = std::chrono::high_resolution_clock::now();

        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Nepavyko atidaryti failo: " << filename << std::endl;
            return;
        }

        std::vector<Studentas> students;

        Studentas student;
        while (inFile >> student.vardas >> student.pavarde) {
            student.ndBalai.clear();
            for (int i = 0; i < 10; ++i) {
                double score;
                inFile >> score;
                student.ndBalai.push_back(score);
            }
            inFile >> student.egzaminas >> student.galutBalas;
            students.push_back(student);
        }
        inFile.close();

        auto endTimeReading = std::chrono::high_resolution_clock::now();

        auto durationReading = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeReading - startTimeReading);

        readTimes.push_back(durationReading.count());

        auto startTimeSorting = std::chrono::high_resolution_clock::now();
        std::sort(students.begin(), students.end(), compareStudents);
        auto endTimeSorting = std::chrono::high_resolution_clock::now();

        auto durationSorting = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeSorting - startTimeSorting);
        sortTimes.push_back(durationSorting.count());

        std::ofstream outFileSorted(filename);
        for (const Studentas &sortedStudent : students) {
            outFileSorted << sortedStudent.vardas << " " << sortedStudent.pavarde;
            for (double score : sortedStudent.ndBalai) {
                outFileSorted << " " << score;
            }
            outFileSorted << " " << sortedStudent.egzaminas << " " << sortedStudent.galutBalas << std::endl;
        }
        outFileSorted.close();

       auto startTimeWrite = std::chrono::high_resolution_clock::now();
      std::string nuskriaustukaiFilename = "nuskriaustukai" + std::to_string(size) + ".txt";
      std::string kietiakaiFilename = "kietiakai" + std::to_string(size) + ".txt";
      
        std::ofstream outFileNuskriaustukai(nuskriaustukaiFilename);
        std::ofstream outFileKietiakai(kietiakaiFilename);

        for (const Studentas &sortedStudent : students) {
            if (sortedStudent.galutBalas < 5.0) {
                outFileNuskriaustukai << sortedStudent.vardas << " " << sortedStudent.pavarde;
                for (double score : sortedStudent.ndBalai) {
                    outFileNuskriaustukai << " " << score;
                }
                outFileNuskriaustukai << " " << sortedStudent.egzaminas << " " << sortedStudent.galutBalas << std::endl;
            } else {
                outFileKietiakai << sortedStudent.vardas << " " << sortedStudent.pavarde;
                for (double score : sortedStudent.ndBalai) {
                    outFileKietiakai << " " << score;
                }
                outFileKietiakai << " " << sortedStudent.egzaminas << " " << sortedStudent.galutBalas << std::endl;
            }
        }
        outFileNuskriaustukai.close();
        outFileKietiakai.close();
      auto endTimeWrite = std::chrono::high_resolution_clock::now();

      auto durationWrite = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeWrite - startTimeWrite);
      writeTimes.push_back(durationWrite.count());
    }

    double averageReadTime = std::accumulate(readTimes.begin(), readTimes.end(), 0.0) / repetitions;
    double averageSortTime = std::accumulate(sortTimes.begin(), sortTimes.end(), 0.0) / repetitions;
  double averageWriteTime = std::accumulate(writeTimes.begin(), writeTimes.end(), 0.0) / repetitions;

    std::cout << "Vidutinis nuskaitymo laikas: " << averageReadTime/1000 << " s" << std::endl;
    std::cout << "Vidutinis rusiavimo laikas: " << averageSortTime/1000 << " s" << std::endl;

  std::cout << "Vidutinis perrasymo laikas: " << averageWriteTime/1000 << " s" << std::endl;
  std::cout << "--------------------------------------------------------------" << std::endl;

  return;
}
