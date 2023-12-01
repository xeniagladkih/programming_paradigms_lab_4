// with_policy.h
#ifndef WITH_POLICY_H
#define WITH_POLICY_H

#include <vector>
#include <functional>
#include <future>
#include <algorithm>

inline bool customAnyOfWithPolicy(const std::vector<int>& data, std::function<bool(int)> predicate, std::launch policy) {
    // Using std::async with the provided launch policy for asynchronous execution
    std::future<bool> result = std::async(policy, [&data, &predicate]() {
        return std::any_of(data.begin(), data.end(), predicate);
    });

    return result.get();
}

#endif // WITH_POLICY_H
