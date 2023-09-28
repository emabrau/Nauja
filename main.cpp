#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <random>

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

double generateRandomScore(double min, double max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<double> dis(min, max);
    return dis(gen);
}

int main() {
    vector<Studentas> studentai;
    char skaicMetodas;

    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> skaicMetodas;

    while (true) {
        Studentas studentas;

        cout << "Iveskite studento varda (Noredami baigti spauskite Enter): ";
        cin.ignore(); 
        getline(cin, studentas.vardas);

        if (studentas.vardas.empty()) {
            break; 
        }

        cout << "Iveskite studento pavarde: ";
        getline(cin, studentas.pavarde);

        char generuoti;
        cout << "Ar norite, kad studento balai butu generuojami atsitiktinai? " << studentas.vardas << " " << studentas.pavarde << "? (T/N): ";
        cin >> generuoti;

        if (generuoti == 'T' || generuoti == 't') {
            int numND;
            cout << "Iveskite namu darbu skaiciu: ";
            cin >> numND;

            cout << "Atsitiktinai sugeneruoti studento namu darbu balai:  " << studentas.vardas << " " << studentas.pavarde << ":\n";
            for (int j = 0; j < numND; ++j) {
                double randomScore = generateRandomScore(0.0, 10.0); 
                studentas.ndBalai.push_back(randomScore);

               
                cout << "ND " << j + 1 << ": " << fixed << setprecision(2) << randomScore << endl;
            }
      
            studentas.egzaminas = generateRandomScore(0.0, 10.0);
           
            cout << "Atsitiktinai sugeneruotas studento egzamino balas " << studentas.vardas << " " << studentas.pavarde << ": " << fixed << setprecision(2) << studentas.egzaminas << endl;
        } else {
            cout << "Iveskite studento namu darbu ivertinimus  " << studentas.vardas << " " << studentas.pavarde << " (Noredami baigti spauskite Enter):\n";
            while (true) {
                double ndBalas;
                cin >> ndBalas;
                if (ndBalas < 0.0 || ndBalas > 10.0) {
                    cout << "Namu darbu ivertinimas turi buti tarp 0 ir 10. Iveskite vel: ";
                    continue;
                }
                studentas.ndBalai.push_back(ndBalas);

                char nextChar = cin.get(); 
                if (nextChar == '\n') {
                    break; 
                }
            }

            // Input the exam score
            cout << "Iveskite studento egzamino bala  " << studentas.vardas << " " << studentas.pavarde << ": ";
            cin >> studentas.egzaminas;
        }

        if (skaicMetodas == 'V' || skaicMetodas == 'v') {
            studentas.galutinisBalas = 0.4 * (accumulate(studentas.ndBalai.begin(), studentas.ndBalai.end(), 0.0) / studentas.ndBalai.size()) + 0.6 * studentas.egzaminas;
        } else if (skaicMetodas == 'M' || skaicMetodas == 'm') {
            studentas.galutinisBalas = 0.4 * (Mediana(studentas.ndBalai)) + 0.6 * studentas.egzaminas;
        } else {
            cout << "Neteisingas skaiciavimo metodas. Pasirinkite V arba M." << endl;
            return 1;
        }

        studentai.push_back(studentas);
    }

    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis balas" << endl;
    cout << string(45, '-') << endl;

    for (const Studentas& studentas : studentai) {
        cout << left << setw(15) << studentas.vardas << setw(15) << studentas.pavarde << setw(15) << fixed << setprecision(2) << studentas.galutinisBalas << endl;
    }

    return 0;
}
