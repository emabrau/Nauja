#include <iostream>
#include <string>
#include <vector>
#include <numeric> 

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<double> ndBalai;
    double egzaminas;
    double galutBalas;
};

int main() {
    int n; 
    cout << "Iveskite atliktu namu darbu skaiciu: ";
    cin >> n;

    vector<Studentas> studentai;
    
    int numStudentai;
    cout << "Iveskite studentu skaiciu: ";
    cin >> numStudentai;

    for (int i = 0; i < numStudentai; ++i) {
        Studentas student;

        cout << "Iveskite studento varda " << i + 1 << ": ";
        cin >> student.vardas;
        cout << "Iveskite studento pavarde " << i + 1 << ": ";
        cin >> student.pavarde;

        cout << "Iveskite studento namu darbu ivertinimus " << student.vardas << " " << student.pavarde << ":" << endl;
        for (int j = 0; j < n; ++j) {
            double balas;
            cout << "ND " << j + 1 << ": ";
            cin >> balas;
            student.ndBalai.push_back(balas);
        }

        cout << "Iveskite studento egzamino bala " << student.vardas << " " << student.pavarde << ": ";
        cin >> student.egzaminas;

        
        student.galutBalas = 0.4 * (accumulate(student.ndBalai.begin(), student.ndBalai.end(), 0.0) / n) + 0.6 * student.egzaminas;

        studentai.push_back(student);
    }

    
    cout << "\nGalutinis balas:\n";
    for (const Studentas& student : studentai) {
        cout << student.vardas << " " << student.pavarde << ": " << student.galutBalas << endl;
    }

    return 0;
}
