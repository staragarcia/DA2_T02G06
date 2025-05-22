#include <iostream>
#include <vector>
#include "../utils/structs.h"

using namespace std;

/**
 * @brief Function to compute the remaining profits from each index to the end of the pallets vector.
 * 
 * @param pallets pallets vector
 * @return vector<int> for each index i, the sum of profits from pallets[i] to pallets[n-1]
 */
vector<int> computeRemainingProfits(const vector<Pallet> &pallets) {
    int n = pallets.size();
    vector<int> remainingProfitFrom(n + 1, 0); // remainingProfitFrom[n] = 0

    for (int i = n - 1; i >= 0; --i) {
        remainingProfitFrom[i] = remainingProfitFrom[i + 1] + pallets[i].profit;
    }
    return remainingProfitFrom;
}

/**
 * @brief Actual recursive backtracking function for the knapsack problem.
 * 
 * @param dataset pallets and truck capacity
 * @param remainingProfitFrom vector of remaining profits from index i to end
 * @param index index of the current pallet being considered
 * @param currentWeight current total weight of selected pallets
 * @param currentProfit current total profit of selected pallets
 * @param maxProfit current maximum profit found
 * @param bestWeight current best weight found
 * @param currentSubset current subset of selected pallets
 * @param bestSubset best subset of selected pallets found
 */
void knapsackBacktrack(const Dataset &dataset, const vector<int> &remainingProfitFrom,
                       int index, int currentWeight, int currentProfit,
                       int &maxProfit, int &bestWeight,
                       vector<int> &currentSubset, vector<int> &bestSubset) {
    if (index == dataset.pallets.size()) {
        if (currentWeight <= dataset.truckCapacity && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestWeight = currentWeight;
            bestSubset = currentSubset;
        }
        return;
    }

    // Prune if even with all remaining profit, this path can't beat maxProfit
    if (currentProfit + remainingProfitFrom[index] <= maxProfit) {
        return;
    }

    // Try skipping the item
    knapsackBacktrack(dataset, remainingProfitFrom, index + 1, currentWeight, currentProfit,
                      maxProfit, bestWeight, currentSubset, bestSubset);

    // Try including the item if it fits
    const Pallet &pallet = dataset.pallets[index];
    if (currentWeight + pallet.weight <= dataset.truckCapacity) {
        currentSubset.push_back(index);
        knapsackBacktrack(dataset, remainingProfitFrom, index + 1,
                          currentWeight + pallet.weight,
                          currentProfit + pallet.profit,
                          maxProfit, bestWeight, currentSubset, bestSubset);
        currentSubset.pop_back(); // backtrack
    }
}

/**
 * @brief Solves the 0/1 Knapsack problem using backtracking.
 * 
 * @details The asymptotic complexity of this algorithm is O(2^n) in the worst case, where n is the number of pallets. However,
 * the actual performance depends on the specific dataset and can be significantly improved with pruning techniques.
 * 
 * @param dataset pallets and truck capacity
 * @param totalWeight used to return the total weight of the selected pallets
 * @param totalProfit used to return the total profit of the selected pallets
 * @return vector<Pallet> selected pallets
 */
vector<Pallet> backtrackingKnapsack(Dataset &dataset, int &totalWeight, int &totalProfit) {
    int maxProfit = 0;
    int bestWeight = 0;
    vector<int> currentSubset;
    vector<int> bestSubset;

    vector<int> remainingProfitFrom = computeRemainingProfits(dataset.pallets);

    knapsackBacktrack(dataset, remainingProfitFrom, 0, 0, 0, maxProfit, bestWeight, currentSubset, bestSubset);

    vector<Pallet> selectedPallets;
    for (int index : bestSubset) {
        selectedPallets.push_back(dataset.pallets[index]);
    }

    totalProfit = maxProfit;
    totalWeight = bestWeight;
    return selectedPallets;
}
