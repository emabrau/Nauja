v0.1 release

Tai yra programa, kuri apskaičiuoja studento galutinį balą pagal formulę 0.4ndVidurkis(arba mediana) + 0.6egzaminas. Programoje pateikiami du skirtingi galutinių pažymių skaičiavimo metodai: vidurkis ir mediana. Vartotojas gali įvesti studento duomenis rankiniu būdu arba įkelti juos iš tekstinio failo. Įvedant duomenis rankiniu būdu, žingsnis po žingsnio yra įvedami studento vardas, pavardė, namų darbų balai ir egzamino rezultatas. Programa tikrina, ar nėra neteisingų įvesties ar tuščių laukų problemų. Rezultatas yra pateikiamas lentelės pavidalu, automatiškai rūšiuojant pagal studentų vardus.

v0.2 release

Tai yra programa, generuojanti studentų namų darbų ir egzamino įverčius, pagal kuriuos apskaičiuojamas kiekvieno studento galutinis balas, naudojant formulę: 0.4ndVidurkis + 0.6egzaminas. Programa nuskaito studentų duomenis iš failų ir apdoroja juos rūšiuodama pagal studentų vardus. Taip pat studentai skirstomi į dvi grupes: „kietiakai“ (aukštesnius pažymius turintys studentai) ir „nuskriaustukai“ (žemesnius pažymius turintys studentai). Po apdorojimo duomenys įrašomi į naujus failus, "nuskriaustukai_n.txt" ir "kietiakai_n.txt", čia n - skaičius, atitinkantis išrūšiuoto failo ,,studentai_n.txt" n skaičių. Programa taip pat matuoja failų generavimo, nuskaitymo, rūšiavimo ir išvedimo trukmę sekundėmis. Siekiant užtikrinti tikslų laiko matavimą, programa pakartoja kiekvieno studentų duomenų failo apdorojimą kelis kartus. Apskaičiuojamas vidutinis kiekvieno failo duomenų skaitymo, rūšiavimo ir rašymo laikas.

v0.3 release

Tai yra programa, skirta apdoroti studentų nanmų darbų bei egzamino rezultatų duomenis. Vartotojui siūlomi keli studentų duomenų įvedimo būdai: rankinis įvedimas, skaitymas iš failo arba automatinis duomenų failų generavimas.

Rankinis duomenų įvedimas (R): vartotojai gali rankiniu būdu įvesti studento vardą, pavardę, namų darbų įverčius ir egzamino balą. Programa apskaičiuoja kiekvieno studento galutinį balą pagal vidurkį ir pagal medianą ir išvedą rezultatą lentelėje.
Duomenų nuskaitymas iš failo (F): vartotojai gali nuskaityti studentų duomenis iš anksčiau sugeneruoto failo. Programa apskaičiuoja kiekvieno studento galutinį balą pagal vidurkį ir pagal medianą ir išveda rezultatą lentelėje.
Automatinis duomenų failų generavimas (G): vartotojui pasirinkus automatinį duomenų failų generavimą, leidžiama rinktis, ar duomenis saugoti vektoriuje, ar sąraše (liste). Programa sugeneruoja 5 duomenų failus: ,,studentai_1000", ,,studentai_10000", ,,studentai_100000", ,,studentai_1000000" ir ,,studentai_10000000", kuriuose yra pateikiami studentų vardas, pavardė, galutinis balas pagal vidurkį ir pagal medianą. Tuomet programa nuskaito studentų duomenis iš sugeneruotų failų ir apdoroja juos rūšiuodama pagal studentų vardus. Taip pat studentai skirstomi į dvi grupes: „kietiakai“ (aukštesnius pažymius turintys studentai) ir „nuskriaustukai“ (žemesnius pažymius turintys studentai). Po apdorojimo duomenys įrašomi į naujus failus, "nuskriaustukai_n.txt" ir "kietiakai_n.txt", čia n - skaičius, atitinkantis išrūšiuoto failo ,,studentai_n.txt" n skaičių. Programa taip pat matuoja failų generavimo, nuskaitymo, rūšiavimo ir išvedimo trukmę sekundėmis. Siekiant užtikrinti tikslų laiko matavimą, programa pakartoja kiekvieno studentų duomenų failo apdorojimą kelis kartus. Apskaičiuojamas vidutinis kiekvieno failo duomenų skaitymo, rūšiavimo ir rašymo laikas.
Testavimo sistemos parametrai: Procesorius: 4CPUs, 3.30GHz, Atmintis: 16.0GB RAM (15.7GB naudojama), SSD


v1.0 release

Rankinis duomenų įvedimas ir duomenų nuskaitymas iš failo lieka tokie patys kaip ir v0.3. 
Pasirinkus automatinį duomenų failų generavimą galimos trys strategijos: 1 strategija - bendro studentai konteinerio (vector ir list tipų) skaidymas į du naujus to paties tipo konteinerius: "nuskriaustukų" ir "kietiakų". Tokiu būdu tas pats studentas yra dvejuose konteineriuose: bendrame studentai ir viename iš suskaidytų. 2 strategija - bendro studentų konteinerio (vector ir list) skaidymas panaudojant tik vieną naują konteinerį: "nuskriaustukai". Tokiu būdu, jei studentas yra nuskriaustukas, jį turime įkelti į naująjį "nuskriaustukų" konteinerį ir ištrinti iš bendro studentai konteinerio. Po šio žingsnio studentai konteineryje liks vien tik kietiakai. 3 strategija - bendro studentų konteinerio (vector ir list) skaidymas panaudojant 2 strategiją ir std::partition algoritmą.

1pav. v0.3. Automatinis duomenų failų generavimas naudojant vector konteinerį.
![Screenshot 2023-11-12 214230](https://github.com/emabrau/EB1/assets/144418033/172499e6-8c5b-4a9a-80db-96f44ca39f22)
2pav. v0.3. Automatinis duomenų failų generavimas naudojant list konteinerį.
![Screenshot 2023-11-12 215828](https://github.com/emabrau/EB1/assets/144418033/4178d7fa-b30f-4649-a98d-50d776591fd8)
3pav. v1.0. Automatinis duomenų failų generavimas naudojant vector konteinerį.
![Screenshot 2023-11-12 221742](https://github.com/emabrau/EB1/assets/144418033/0d446c6a-11e9-4799-8a67-8491cde60b9c)
4pav. v1.0. Automatinis duomenų failų generavimas naudojant list konteinerį.
![image](https://github.com/emabrau/EB1/assets/144418033/78f77008-309b-459a-920f-362b8cc4f7f4)




