// with_policy.cpp
#include "with_policy.h"
#include <algorithm>

// Реалізація функції customAnyOfWithPolicy
bool customAnyOfWithPolicy(const std::vector<int>& data, std::function<bool(int)> predicate) {
    // Використання стандартної функції any_of без політики
    return std::any_of(data.begin(), data.end(), predicate);
}
