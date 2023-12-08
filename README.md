v1.2 release

Tai yra programa, skirta apdoroti studentų namų darbų bei egzamino rezultatų duomenis. Vartotojui siūlomi keli studentų duomenų įvedimo būdai: rankinis įvedimas, skaitymas iš failo arba automatinis duomenų failų generavimas.

Rankinis duomenų įvedimas (R): vartotojai gali rankiniu būdu įvesti studento vardą, pavardę, namų darbų įverčius ir egzamino balą. Programa apskaičiuoja kiekvieno studento galutinį balą pagal vidurkį ir pagal medianą ir išveda rezultatą lentelėje.

Duomenų nuskaitymas iš failo (F): vartotojai gali nuskaityti studentų duomenis iš anksčiau sugeneruoto failo. Programa apskaičiuoja kiekvieno studento galutinį balą pagal vidurkį ir pagal medianą ir išveda rezultatą lentelėje.

Automatinis duomenų failų generavimas (G): vartotojui pasirinkus automatinį duomenų failų generavimą, leidžiama rinktis, ar duomenis saugoti vektoriuje, ar sąraše (liste). Programa sugeneruoja 5 duomenų failus: ,,studentai_1000.txt", ,,studentai_10000.txt", ,,studentai_100000.txt", ,,studentai_1000000.txt" ir ,,studentai_10000000.txt", kuriuose yra pateikiami studentų vardas, pavardė, galutinis balas pagal vidurkį. Tuomet programa nuskaito studentų duomenis iš sugeneruotų failų ir apdoroja juos rūšiuodama pagal studentų vardus. Taip pat studentai skirstomi į dvi grupes: „kietiakai“ (aukštesnius pažymius turintys studentai) ir „nuskriaustukai“ (žemesnius pažymius turintys studentai). Po apdorojimo duomenys įrašomi į naujus failus, "nuskriaustukai_n.txt" ir "kietiakai_n.txt", čia n - skaičius, atitinkantis išrūšiuoto failo ,,studentai_n.txt" n skaičių. Programa taip pat matuoja failų generavimo, nuskaitymo, rūšiavimo ir išvedimo trukmę sekundėmis. Siekiant užtikrinti tikslų laiko matavimą, programa pakartoja kiekvieno studentų duomenų failo apdorojimą kelis kartus. Apskaičiuojamas vidutinis kiekvieno failo duomenų skaitymo, rūšiavimo ir rašymo laikas.

Nuo v1.1 skiriasi tuo, jog realizuoti visi reikiami "Rule of three" (destruktorius, kopijavimo konstruktorius ir kopijavimo priskyrimo operatorius) ir įvesties/išvesties operatoriai Studentas klasei.

1pav. Konsolės vaizdas, pasirinkus rankinį duomenų įvedimo būdą.
![image](https://github.com/emabrau/Nauja/assets/144418033/7b9f7a92-0e56-420a-92de-24af7f882892)

2pav. Konsolės vaizdas, pasirinkus duomenų nuskaitymą iš failo.
![image](https://github.com/emabrau/Nauja/assets/144418033/6722c031-d6de-4287-86ef-40bebe274edb)

3pav. Konsolės vaizdas, pasirinkus automatinį duomenų generavimą ir vektoriaus struktūrą. 

![image](https://github.com/emabrau/Nauja/assets/144418033/d59c57d6-0903-4071-8346-9e944bfd2f96)

4pav. Konsolės vaizdas, pasirinkus automatinį duomenų generavimą ir sąrašo struktūrą.
![image](https://github.com/emabrau/Nauja/assets/144418033/0ae2eca5-bfed-49ba-a47e-c0b544690029)








