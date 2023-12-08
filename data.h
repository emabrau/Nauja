#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

class Studentas {
public:
    Studentas();
    ~Studentas();
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

    friend std::istream& operator>>(std::istream& is, Studentas& student);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& student);
    std::string vardas;
    std::string pavarde;
    std::vector<double> ndBalai;
    double egzaminas;
    double galutBalas;
    double galutBalasMed;
    double galutBalasVid;
};

class DataManager {
public:
    DataManager() noexcept;
    ~DataManager();
    void generateAndWriteStudentRecordsV(const std::string &filename, int size);
    void generateAndWriteStudentRecordsL(const std::string &filename, int size);

    void processStudentDataV(int size, int repetitions);
    void processStudentDataL(int size, int repetitions);

    void loadDataFromManualInput(std::vector<Studentas>& studentai);
    void loadData(std::vector<Studentas>& studentai, const std::string& filename);
    void chooseDataInputMethod(std::vector<Studentas>& studentai);
    void generateRandomData(std::vector<Studentas>& studentai, int count);
};

#endif




