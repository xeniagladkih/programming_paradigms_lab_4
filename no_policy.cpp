// no_policy.cpp
#include "no_policy.h"

// Реалізація функції customAnyOfNoPolicy
bool customAnyOfNoPolicy(const std::vector<int>& data, std::function<bool(int)> predicate) {
    for (int element : data) {
        if (predicate(element)) {
            return true;
        }
    }
    return false;
}
