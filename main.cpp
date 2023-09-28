#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<double> ndBalai;
    double egzaminas;
    double galutinisBalas;
};

double Mediana(vector<double>& vec) {
    size_t size = vec.size();
    if (size == 0) {
        return 0.0;
    }
    sort(vec.begin(), vec.end());
    if (size % 2 == 0) {
        return (vec[size / 2 - 1] + vec[size / 2]) / 2.0;
    } else {
        return vec[size / 2];
    }
}

int main() {
    int n; 
    cout << "Iveskite atliktu namu darbu skaiciu: ";
    cin >> n;

    vector<Studentas> studentai;

    int numStudentai;
    cout << "Iveskite studentu skaiciu: ";
    cin >> numStudentai;

    char skaicMetodas;
    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> skaicMetodas;

    for (int i = 0; i < numStudentai; ++i) {
        Studentas student;

        cout << "Iveskite studento varda " << i + 1 << ": ";
        cin >> student.vardas;
        cout << "Iveskite studento pavarde " << i + 1 << ": ";
        cin >> student.pavarde;

        cout << "Iveskite studento namu darbu ivertinimus " << student.vardas << " " << student.pavarde << ":" << endl;
        for (int j = 0; j < n; ++j) {
            double score;
            cout << "ND " << j + 1 << ": ";
            cin >> score;
            student.ndBalai.push_back(score);
        }

        cout << "Iveskite studento egzamino bala " << student.vardas << " " << student.pavarde << ": ";
        cin >> student.egzaminas;

        
        if (skaicMetodas == 'V' || skaicMetodas == 'v') {
            
            student.galutinisBalas = 0.4 * (accumulate(student.ndBalai.begin(), student.ndBalai.end(), 0.0) / n) + 0.6 * student.egzaminas;
        } else if (skaicMetodas == 'M' || skaicMetodas == 'm') {
            
            student.galutinisBalas = 0.4 * Mediana(student.ndBalai) + 0.6 * student.egzaminas;
        } else {
            cout << "Neteisingas skaiciavimo metodas. Pasirinkite V arba M." << endl;
            return 1;
        }

        studentai.push_back(student);
    }


    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas" << endl;
    cout << string(45, '-') << endl;

    
    for (const Studentas& studentas : studentai) {
        cout << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << fixed << setprecision(2) << studentas.galutinisBalas << endl;
    }

    return 0;
}
