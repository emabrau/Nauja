#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

class Studentas {
public:
    Studentas();
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
    void generateAndWriteStudentRecordsV(const std::string &filename, int size);
    void generateAndWriteStudentRecordsL(const std::string &filename, int size);

    void processStudentDataV(const std::string &filename, int size, int repetitions);
    void processStudentDataL(const std::string &filename, int size, int repetitions);

    void loadDataFromManualInput(std::vector<Studentas>& studentai);
    void loadData(std::vector<Studentas>& studentai, const std::string& filename);
    void chooseDataInputMethod(std::vector<Studentas>& studentai);
    void generateRandomData(std::vector<Studentas>& studentai, int count);
};

#endif


