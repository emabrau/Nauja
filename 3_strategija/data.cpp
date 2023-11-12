void processStudentDataList(const std::string &filename, int size, int repetitions) {
    std::vector<double> readTimes;
    std::vector<double> sortTimes;
    std::vector<double> writeTimes;

    for (int rep = 0; rep < repetitions; ++rep) {
        // Generate data
        auto startTimeGeneration = std::chrono::high_resolution_clock::now();
        std::list<Studentas> students;
        for (int i = size; i >= 1; --i) {
            Studentas student = generateRandomStudent(i);
            students.push_back(student);
        }
        auto endTimeGeneration = std::chrono::high_resolution_clock::now();
        auto durationGeneration = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeGeneration - startTimeGeneration);
        readTimes.push_back(durationGeneration.count());

        auto startTimeSorting = std::chrono::high_resolution_clock::now();
        students.sort(compareStudents);
        auto endTimeSorting = std::chrono::high_resolution_clock::now();
        auto durationSorting = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeSorting - startTimeSorting);
        sortTimes.push_back(durationSorting.count());

        // Use std::partition to separate students based on the condition
        auto partitionPoint = std::partition(students.begin(), students.end(), [](const Studentas &student) {
            return student.galutBalas < 5.0;
        });

        // Write students with a grade less than 5.0 to one file
        std::string nuskriaustukaiFileName = "nuskriaustukai_" + std::to_string(size) + ".txt";
        std::ofstream outFileNuskriaustukai(nuskriaustukaiFileName);
        if (!outFileNuskriaustukai.is_open()) {
            std::cerr << "Nepavyko sukurti failo: " << nuskriaustukaiFileName << std::endl;
            return;
        }
        for (auto it = students.begin(); it != partitionPoint; ++it) {
            outFileNuskriaustukai << it->vardas << " " << it->pavarde;
            for (double score : it->ndBalai) {
                outFileNuskriaustukai << " " << score;
            }
            outFileNuskriaustukai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
        }
        outFileNuskriaustukai.close();

        // Write students with a grade of 5.0 or higher to another file
        std::string kietiakaiFileName = "kietiakai_" + std::to_string(size) + ".txt";
        std::ofstream outFileKietiakai(kietiakaiFileName);
        if (!outFileKietiakai.is_open()) {
            std::cerr << "Nepavyko sukurti failo: " << kietiakaiFileName << std::endl;
            return;
        }

        for (auto it = partitionPoint; it != students.end(); ++it) {
            outFileKietiakai << it->vardas << " " << it->pavarde;
            for (double score : it->ndBalai) {
                outFileKietiakai << " " << score;
            }
            outFileKietiakai << " " << it->egzaminas << " " << it->galutBalas << std::endl;
        }
        outFileKietiakai.close();

        auto endTimeWrite = std::chrono::high_resolution_clock::now();
        auto durationWrite = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeWrite - endTimeSorting);
        writeTimes.push_back(durationWrite.count());
    }

    double averageReadTime = std::accumulate(readTimes.begin(), readTimes.end(), 0.0) / repetitions;
    double averageSortTime = std::accumulate(sortTimes.begin(), sortTimes.end(), 0.0) / repetitions;
    double averageWriteTime = std::accumulate(writeTimes.begin(), writeTimes.end(), 0.0) / repetitions;

    std::cout << "Vidutinis nuskaitymo laikas: " << averageReadTime / 1000 << " s" << std::endl;
    std::cout << "Vidutinis rusiavimo laikas: " << averageSortTime / 1000 << " s" << std::endl;
    std::cout << "Vidutinis perrasymo laikas: " << averageWriteTime / 1000 << " s" << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
}
