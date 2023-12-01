// custom_algorithm.cpp
#include "custom_algorithm.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <future>

// Реалізація функції customParallelAlgorithm
bool customParallelAlgorithm(const std::vector<int>& data, std::function<bool(int)> predicate, int numThreads) {
    // Розбивка даних для кожного потоку
    std::vector<std::vector<int>> threadData(numThreads);

    for (int i = 0; i < data.size(); ++i) {
        threadData[i % numThreads].push_back(data[i]);
    }

    // Запуск потоків
    std::vector<std::future<bool>> futures;
    for (int i = 0; i < numThreads; ++i) {
        futures.push_back(std::async(std::launch::async, [predicate](const std::vector<int>& threadVec) {
            return std::any_of(threadVec.begin(), threadVec.end(), predicate);
        }, threadData[i]));
    }

    // Збір результатів
    bool result = false;
    for (auto& future : futures) {
        result |= future.get();
    }

    return result;
}

// Реалізація функції runExperiments
void runExperiments(const std::vector<int>& data, std::function<bool(int)> predicate, std::ofstream& outputFile) {

    // Виведення результатів для різної кількості потоків
    for (int numThreads = 1; numThreads <= std::thread::hardware_concurrency(); ++numThreads) {
        auto start_time = std::chrono::high_resolution_clock::now();
        bool result = customParallelAlgorithm(data, predicate, numThreads);
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;

        // Запис результатів у файл
        outputFile << "Час роботи власного паралельного алгоритму з " << numThreads << " потокiв: " << elapsed_time.count() * 1e6 << " мкс\n";
    }

    outputFile << "\n";
}
