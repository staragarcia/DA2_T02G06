#pragma once

#include <vector>

/**
 * @brief Compares two integer vectors lexicographically.
 *
 * Iterates through both vectors and compares their elements one by one.
 * Returns true if the first vector is lexicographically less than the second.
 * If all elements are equal, returns false.
 * @details asymptotic complexity: O(n), where n is the size of the vectors.
 *
 * @param a The first vector to compare.
 * @param b The second vector to compare.
 * @return true if vector a is lexicographically less than vector b, false otherwise.
 */
bool lexCompare(const vector<int> &a, const vector<int> &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return a[i] < b[i]; // lexicographical comparison
        }
    }
    return false; // they are equal
}

/**
 * @brief Determines if the current solution is better than the best found so far.
 *
 * Compares solutions based on weight, profit, subset size, and lexicographical order.
 * - Returns false if the current weight exceeds the truck capacity.
 * - Prefers higher profit.
 * - If profits are equal, prefers smaller subsets.
 * - If subset sizes are equal, prefers lexicographically smaller subsets.
 * @details asymptotic complexity: O(n), where n is the size of the subsets.
 *
 * @param currentWeight The total weight of the current subset.
 * @param currentProfit The total profit of the current subset.
 * @param maxProfit The maximum profit found so far.
 * @param currentSubset The current subset of items.
 * @param bestSubset The best subset found so far.
 * @param truckCapacity The maximum allowed weight.
 * @return true if the current solution is better, false otherwise.
 */
bool better(int currentWeight, int currentProfit, int maxProfit,
        const vector<int> &currentSubset, const vector<int> &bestSubset, int truckCapacity) {
    if (currentWeight > truckCapacity) {
        return false; // current weight exceeds truck capacity
    }
    if (currentProfit != maxProfit) {
        return currentProfit > maxProfit; // current profit is better
    }
    if (currentSubset.size() != bestSubset.size()) {
        return currentSubset.size() < bestSubset.size(); // smaller subset is better
    }
    return lexCompare(currentSubset, bestSubset); // lexicographical comparison
}