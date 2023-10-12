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



void generateAndWriteStudentRecords(const std::string &filename, int size) {
   auto startTime = std::chrono::high_resolution_clock::now();
    std::ofstream outFile(filename);
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
  
  auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
  
  std::cout << "Laikas, per kuri sugeneravo " << filename << ": " << duration.count() << " sekundes" << std::endl;
}


void processStudentData(const std::string &filename) {
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
  
  auto durationReading = std::chrono::duration_cast<std::chrono::seconds>(endTimeReading - startTimeReading);
  
  std::cout << "Laikas, per kuri nuskaite " << filename << ": " << durationReading.count() << " sekundes" << std::endl;

  
  
    std::sort(students.begin(), students.end(), compareStudents);

   auto startTimeSorting = std::chrono::high_resolution_clock::now();

    std::ofstream outFileSorted(filename);
    for (const Studentas &sortedStudent : students) {
        outFileSorted << sortedStudent.vardas << " " << sortedStudent.pavarde;
        for (double score : sortedStudent.ndBalai) {
            outFileSorted << " " << score;
        }
        outFileSorted << " " << sortedStudent.egzaminas << " " << sortedStudent.galutBalas << std::endl;
    }
    outFileSorted.close();

  auto endTimeSorting = std::chrono::high_resolution_clock::now();

  auto durationSorting = std::chrono::duration_cast<std::chrono::seconds>(endTimeSorting - startTimeSorting);
  std::cout << "Laikas, per kuri isrusiavo: " <<  filename << ": " << durationSorting.count() << " sekundes" << std::endl;

   auto startTimeOutput = std::chrono::high_resolution_clock::now();
  
    std::ifstream inFileSorted(filename);
    std::ofstream outFileNuskriaustukai("nuskriaustukai_" + filename);
    std::ofstream outFileKietiakai("kietiakai_" + filename);

    while (inFileSorted >> student.vardas >> student.pavarde) {
        student.ndBalai.clear();
        for (int i = 0; i < 10; ++i) {
            double score;
            inFileSorted >> score;
            student.ndBalai.push_back(score);
        }
        inFileSorted >> student.egzaminas >> student.galutBalas;

        if (student.galutBalas < 5.0) {
            outFileNuskriaustukai << student.vardas << " " << student.pavarde;
            for (double score : student.ndBalai) {
                outFileNuskriaustukai << " " << score;
            }
            outFileNuskriaustukai << " " << student.egzaminas << " " << student.galutBalas << std::endl;
        } else {
            outFileKietiakai << student.vardas << " " << student.pavarde;
            for (double score : student.ndBalai) {
                outFileKietiakai << " " << score;
            }
            outFileKietiakai << " " << student.egzaminas << " " << student.galutBalas << std::endl;
        }
    }

    inFileSorted.close();
    outFileNuskriaustukai.close();
    outFileKietiakai.close();
   auto endTimeOutput = std::chrono::high_resolution_clock::now();
  auto durationOutput = std::chrono::duration_cast<std::chrono::seconds>(endTimeOutput - startTimeOutput);
  std::cout << "Laikas, per kuri isvede isrusiuotus " << filename <<  "duomenis: " << durationOutput.count() << " sekundes" << std::endl;
}

