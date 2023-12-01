//compiler - clang

// main.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <functional>
#include <future>
#include "no_policy.h"
#include "with_policy.h"
#include "custom_algorithm.h"

int main() {
    // Створення вектору з тестовими даними
    std::vector<int> data = {1, 3, 5, 7, 2, 9, 1, 3, 5, 7, 2, 9, 1, 3, 5, 7, 2, 9, 1, 3, 5, 7, 2, 9, 1, 3, 5, 7, 2, 9, 1, 3, 5, 7};

    // Предикат для пошуку парних елементів
    std::function<bool(int)> isEven = [](int x) { return x % 2 == 0; };

    // Відкриваємо файл для запису результатів
    std::ofstream outputFile("results.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the results file." << std::endl;
        return 1;
    }

    // Тестування функції без політики
    auto start_time = std::chrono::high_resolution_clock::now();
    bool result_no_policy = customAnyOfNoPolicy(data, isEven);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time_no_policy = end_time - start_time;

    // Виведення інформації про дані та предикат
    outputFile << "Данi : { ";
    for (const auto& num : data) {
        outputFile << num << ", ";
    }
    outputFile << "}\nПредикат : x % 2 == 0\n\n";
    
    // Запис результатів у файл
    outputFile << "Час роботи бiблiотечного алгоритму без полiтики " << elapsed_time_no_policy.count() * 1e6 << " мкс\n";

    // Тестування функції з політикою seq
    start_time = std::chrono::high_resolution_clock::now();
    bool result_with_seq_policy = customAnyOfWithPolicy(data, isEven, std::launch::deferred | std::launch::async);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time_with_seq_policy = end_time - start_time;

    // Запис результатів у файл
    outputFile << "Час роботи бiблiотечного алгоритму з полiтикою seq " << elapsed_time_with_seq_policy.count() * 1e6 << " мкс\n";

    // Тестування функції з політикою par
    start_time = std::chrono::high_resolution_clock::now();
    bool result_with_par_policy = customAnyOfWithPolicy(data, isEven, std::launch::deferred | std::launch::async);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time_with_par_policy = end_time - start_time;

    // Запис результатів у файл
    outputFile << "Час роботи бiблiотечного алгоритму з полiтикою par " << elapsed_time_with_par_policy.count() * 1e6 << " мкс\n\n";

    // Тестування власного паралельного алгоритму
    runExperiments(data, isEven, outputFile);

    // Закриваємо файл
    outputFile.close();

    return 0;
}
