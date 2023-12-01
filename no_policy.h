// no_policy.h
#pragma once
#include <vector>
#include <functional>

// Функція customAnyOfNoPolicy шукає елемент у векторі data
// без використання політик для паралелізації.
bool customAnyOfNoPolicy(const std::vector<int>& data, std::function<bool(int)> predicate);
