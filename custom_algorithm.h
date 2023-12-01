// custom_algorithm.h
#pragma once
#include <vector>
#include <functional>
#include <fstream>

// Функція customParallelAlgorithm є власною паралельною реалізацією
// алгоритму для пошуку елемента у векторі за допомогою заданої кількості потоків.
bool customParallelAlgorithm(const std::vector<int>& data, std::function<bool(int)> predicate, int numThreads);

// Функція runExperiments виконує експерименти з різною кількістю потоків і записує результати у файл.
void runExperiments(const std::vector<int>& data, std::function<bool(int)> predicate, std::ofstream& outputFile);

