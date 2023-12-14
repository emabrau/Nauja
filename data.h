#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>


class Human {
public:
    virtual ~Human() = default;
    virtual void introduce() const = 0;
 


    std::string vardas;
    std::string pavarde;
};


class Studentas : public Human {
public:
    Studentas();
    ~Studentas() override;
    Studentas(const Studentas& other);
    Studentas& operator=(const Studentas& other);

     void introduce() const override;
  
    friend std::istream& operator>>(std::istream& is, Studentas& student);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& student);

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







