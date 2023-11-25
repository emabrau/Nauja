#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include "data.h"
#include "functions.h"
#include <chrono>
#include <numeric>
#include <sstream>

#include "data.h"
#include "functions.h"

void DataManager::loadDataFromManualInput(std::vector<Studentas>& studentai) {
    try {
        while (true) {
            Studentas studentas;

            std::cout << "Iveskite studento varda (noredami baigti spauskite Enter): ";
            std::cin.ignore(); 
            getline(std::cin, studentas.vardas);

            if (studentas.vardas.empty()) {
                break;
            }

            std::cout << "Iveskite studento pavarde: ";
            getline(std::cin, studentas.pavarde);

            double ndBalai;
            std::cout << "Iveskite studento " << studentas.vardas << " " << studentas.pavarde << " namu darbu balus " << " " << " (Noredami baigti spauskite Enter):\n";
            while (true) {
                std::string input;
                getline(std::cin, input);

                if (input.empty()) {
                    break; 
                }

                ndBalai = std::stod(input);
                studentas.ndBalai.push_back(ndBalai);
            }

            std::cout << "Iveskite studento " << studentas.vardas << " " << studentas.pavarde << " egzamino rezultata: ";
            std::cin >> studentas.egzaminas;

            studentai.push_back(studentas);
        }
    } catch (const std::exception& e) {
        throw e;
    }
}

void DataManager::loadData(std::vector<Studentas>& studentai, const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Nepavyko atidaryti failo " + filename);
        }

        studentai.clear(); 
        std::string header;
        std::getline(file, header);

        std::string line;
        while (std::getline(file, line)) {
            Studentas studentas;

            std::istringstream iss(line);
            iss >> std::setw(15) >> studentas.vardas >> std::setw(15) >> studentas.pavarde;
            for (int i = 0; i < 15; ++i) {
                double balas;
                iss >> std::setw(8) >> balas; 
                studentas.ndBalai.push_back(balas);
            }
            iss >> studentas.egzaminas;

            studentai.push_back(studentas);
        }

        file.close();
    } catch (const std::exception& e) {
        throw e;
    }
}

void DataManager::generateRandomData(std::vector<Studentas>& studentai, int count) {
    srand(time(0));
    for (int i = 0; i < count; ++i) {
        Studentas studentas;
        studentas.vardas = "Vardas" + std::to_string(i);
        studentas.pavarde = "Pavarde" + std::to_string(i);
        for (int j = 0; j < 5; ++j) {
            studentas.ndBalai.push_back((rand() % 10) + 1);
        }
        studentas.egzaminas = rand() % 10 + 1;
        studentai.push_back(studentas);
    }
}

void DataManager::generateAndWriteStudentRecordsV(const std::string &filename, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ofstream outFile(filename);

    std::vector<Studentas> students;
    students.reserve(size);

    for (int i = size; i >= 1; --i) {
        Studentas student = StudentFunctions::generateRandomStudent(i);
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

void DataManager::generateAndWriteStudentRecordsL(const std::string &filename, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ofstream outFile(filename);

    std::list<Studentas> students; 

    for (int i = size; i >= 1; --i) {
        Studentas student = StudentFunctions::generateRandomStudent(i);
        outFile << student.vardas << " " << student.pavarde;
        for (double score : student.ndBalai) {
            outFile << " " << score;
        }
        outFile << " " << student.egzaminas << " " << student.galutBalas << std::endl;
    }
    outFile.close();

    auto endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << "Laikas, per kuri sugeneravo " << filename << ": " << duration.count() / 1000 << " s" << std::endl;
}

void DataManager::processStudentDataV(const std::string &filename, int size, int repetitions) {
  std::vector<double> readTimes;
  std::vector<double> sortTimes;
  std::vector<double> writeTimes;

  for (int rep = 0; rep < repetitions; ++rep) {

      auto startTimeGeneration = std::chrono::high_resolution_clock::now();
      std::vector<Studentas> students;
      students.reserve(size);
      for (int i = size; i >= 1; --i) {
          Studentas student = StudentFunctions::generateRandomStudent(i);
          students.push_back(student);
      }
      auto endTimeGeneration = std::chrono::high_resolution_clock::now();
      auto durationGeneration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeGeneration - startTimeGeneration);
      readTimes.push_back(durationGeneration.count());

      auto startTimeSorting = std::chrono::high_resolution_clock::now();
      std::sort(students.begin(), students.end(), StudentFunctions::compareStudents);
      auto endTimeSorting = std::chrono::high_resolution_clock::now();
      auto durationSorting = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeSorting - startTimeSorting);
      sortTimes.push_back(durationSorting.count());


      auto partitionPoint = std::partition(students.begin(), students.end(), [](const Studentas &student) {
          return student.galutBalas < 5.0;
      });


      std::string nuskriaustukaiFileName = "nuskriaustukai_" + std::to_string(size) + ".txt";
      std::ofstream outFileNuskriaustukai(nuskriaustukaiFileName);
      if (!outFileNuskriaustukai.is_open()) {
          std::cerr << "Nepavyko sukurti failo: " << nuskriaustukaiFileName << std::endl;
          return;
      }
      for (auto it = students.begin(); it != partitionPoint; ++it) {
          outFileNuskriaustukai << it->vardas << " " << it->pavarde;
          for (double score : it->ndBalai) {
              outFileNuskriaustukai << " " << score;
          }
          outFileNuskriaustukai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
      }
      outFileNuskriaustukai.close();


      std::string kietiakaiFileName = "kietiakai_" + std::to_string(size) + ".txt";
      std::ofstream outFileKietiakai(kietiakaiFileName);
      if (!outFileKietiakai.is_open()) {
          std::cerr << "Nepavyko sukurti failo: " << kietiakaiFileName << std::endl;
          return;
      }

      for (auto it = partitionPoint; it != students.end(); ++it) {
          outFileKietiakai << it->vardas << " " << it->pavarde;
          for (double score : it->ndBalai) {
              outFileKietiakai << " " << score;
          }
          outFileKietiakai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
      }
      outFileKietiakai.close();

      auto endTimeWrite = std::chrono::high_resolution_clock::now();
      auto durationWrite = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeWrite - endTimeSorting);
      writeTimes.push_back(durationWrite.count());
  }

  double averageReadTime = std::accumulate(readTimes.begin(), readTimes.end(), 0.0) / repetitions;
  double averageSortTime = std::accumulate(sortTimes.begin(), sortTimes.end(), 0.0) / repetitions;
  double averageWriteTime = std::accumulate(writeTimes.begin(), writeTimes.end(), 0.0) / repetitions;

  std::cout << "Vidutinis nuskaitymo laikas: " << averageReadTime / 1000 << " s" << std::endl;
  std::cout << "Vidutinis rusiavimo laikas: " << averageSortTime / 1000 << " s" << std::endl;
  std::cout << "Vidutinis perrasymo laikas: " << averageWriteTime / 1000 << " s" << std::endl;
  std::cout << "--------------------------------------------------------------" << std::endl;
}

void DataManager::processStudentDataL(const std::string &filename, int size, int repetitions) {
   std::vector<double> readTimes;
   std::vector<double> sortTimes;
   std::vector<double> writeTimes;

   for (int rep = 0; rep < repetitions; ++rep) {

       auto startTimeGeneration = std::chrono::high_resolution_clock::now();
       std::list<Studentas> students;
       for (int i = size; i >= 1; --i) {
           Studentas student = StudentFunctions::generateRandomStudent(i);
           students.push_back(student);
       }
       auto endTimeGeneration = std::chrono::high_resolution_clock::now();
       auto durationGeneration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeGeneration - startTimeGeneration);
       readTimes.push_back(durationGeneration.count());

       auto startTimeSorting = std::chrono::high_resolution_clock::now();
       students.sort(StudentFunctions::compareStudents);
       auto endTimeSorting = std::chrono::high_resolution_clock::now();
       auto durationSorting = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeSorting - startTimeSorting);
       sortTimes.push_back(durationSorting.count());


       auto partitionPoint = std::partition(students.begin(), students.end(), [](const Studentas &student) {
           return student.galutBalas < 5.0;
       });


       std::string nuskriaustukaiFileName = "nuskriaustukai_" + std::to_string(size) + ".txt";
       std::ofstream outFileNuskriaustukai(nuskriaustukaiFileName);
       if (!outFileNuskriaustukai.is_open()) {
           std::cerr << "Nepavyko sukurti failo: " << nuskriaustukaiFileName << std::endl;
           return;
       }
       for (auto it = students.begin(); it != partitionPoint; ++it) {
           outFileNuskriaustukai << it->vardas << " " << it->pavarde;
           for (double score : it->ndBalai) {
               outFileNuskriaustukai << " " << score;
           }
           outFileNuskriaustukai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
       }
       outFileNuskriaustukai.close();


       std::string kietiakaiFileName = "kietiakai_" + std::to_string(size) + ".txt";
       std::ofstream outFileKietiakai(kietiakaiFileName);
       if (!outFileKietiakai.is_open()) {
           std::cerr << "Nepavyko sukurti failo: " << kietiakaiFileName << std::endl;
           return;
       }

       for (auto it = partitionPoint; it != students.end(); ++it) {
           outFileKietiakai << it->vardas << " " << it->pavarde;
           for (double score : it->ndBalai) {
               outFileKietiakai << " " << score;
           }
           outFileKietiakai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
       }
       outFileKietiakai.close();

       auto endTimeWrite = std::chrono::high_resolution_clock::now();
       auto durationWrite = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeWrite - endTimeSorting);
       writeTimes.push_back(durationWrite.count());
   }

   double averageReadTime = std::accumulate(readTimes.begin(), readTimes.end(), 0.0) / repetitions;
   double averageSortTime = std::accumulate(sortTimes.begin(), sortTimes.end(), 0.0) / repetitions;
   double averageWriteTime = std::accumulate(writeTimes.begin(), writeTimes.end(), 0.0) / repetitions;

   std::cout << "Vidutinis nuskaitymo laikas: " << averageReadTime / 1000 << " s" << std::endl;
   std::cout << "Vidutinis rusiavimo laikas: " << averageSortTime / 1000 << " s" << std::endl;
   std::cout << "Vidutinis perrasymo laikas: " << averageWriteTime / 1000 << " s" << std::endl;
   std::cout << "--------------------------------------------------------------" << std::endl;
}
