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
    vector<Studentas> studentai;
    char skaicMetodas;

    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> skaicMetodas;

    while (true) {
        Studentas studentas;

        cout << "Iveskite studento varda (spauskite Enter noredami baigti): ";
        cin.ignore(); 
        getline(cin, studentas.vardas);

        if (studentas.vardas.empty()) {
            break; 
        }

        cout << "Iveskite studento pavarde: ";
        getline(cin, studentas.pavarde);

        double ndBalas;
        cout << "Iveskite studento namu darbu ivertinimus " << studentas.vardas << " " << studentas.pavarde << " (Spasukite Enter noredami baigti):\n";
        while (true) {
            string input;
            getline(cin, input);

            if (input.empty()) {
                break; 
            }

            ndBalas = stod(input);
            studentas.ndBalai.push_back(ndBalas);
        }

        cout << "Iveskite studento egzamino bala " << studentas.vardas << " " << studentas.pavarde << ": ";
        cin >> studentas.egzaminas;

        
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

