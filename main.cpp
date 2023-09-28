#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "functions.h" 

using namespace std;

int main() {
    vector<Studentas> studentai;
    char skaicMetodas;

    cout << "Pasirinkite skaiciavimo metoda (V - vidurkis, M - mediana): ";
    cin >> skaicMetodas;

    inputStudentData(studentai, skaicMetodas); 
  

    printStudentData(studentai); 

    return 0;
}

