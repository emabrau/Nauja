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


void loadDataFromManualInput(std::vector<Studentas>& studentai) {
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

void loadData(std::vector<Studentas>& studentai, const std::string& filename) {
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



void generateRandomData(std::vector<Studentas>& studentai, int count) {
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


void generateAndWriteStudentRecordsV(const std::string &filename, int size) {
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

void generateAndWriteStudentRecordsL(const std::string &filename, int size) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ofstream outFile(filename);

    std::list<Studentas> students; 

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

    std::cout << "Laikas, per kuri sugeneravo " << filename << ": " << duration.count() / 1000 << " s" << std::endl;
}



void processStudentDataV(const std::string &filename, int size, int repetitions) {
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


void processStudentDataL(const std::string &filename, int size, int repetitions) {
    std::list<double> readTimes;
    std::list<double> sortTimes;
    std::list<double> writeTimes;

    for (int rep = 0; rep < repetitions; ++rep) {
        auto startTimeReading = std::chrono::high_resolution_clock::now();

        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Nepavyko atidaryti failo: " << filename << std::endl;
            return;
        }

        std::list<Studentas> students;  

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
        students.sort(compareStudents); 
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

    std::cout << "Vidutinis nuskaitymo laikas: " << averageReadTime / 1000 << " s" << std::endl;
    std::cout << "Vidutinis rusiavimo laikas: " << averageSortTime / 1000 << " s" << std::endl;

    std::cout << "Vidutinis perrasymo laikas: " << averageWriteTime / 1000 << " s" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
}

