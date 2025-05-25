#include <iostream>
#include <vector>
#include "../utils/structs.h"

using namespace std;


struct State { 
    int profit = 0;
    vector<int> palletIndices = {};
};


/**
 * @brief Helper function to compare two states based on profit and pallet indices.
 * 
 * @param State 
 * @param State 
 * @return bool (true if a is better than b, false otherwise)
 */
bool isBetter(const State& a, const State& b) {
    if (a.profit != b.profit) return a.profit > b.profit;
    if (a.palletIndices.size() != b.palletIndices.size()) return a.palletIndices.size() < b.palletIndices.size();
    return a.palletIndices < b.palletIndices;
}

/**
 * @brief Finds the optimal subset of pallets to maximize profit without exceeding the truck's capacity using dynamic programming.
 * 
 * This function constructs a DP table to evaluate all possible combinations of pallets and capacities,
 * making sure the selected set has the highest possible profit while staying within the weight limit.
 * 
 * @details  Time Complexity: O(i × j)
 * 
 * @param dataset pallets and truck capacity
 * @param totalWeight total weight of selected pallets
 * @param totalProfit total profit of selected pallets
 * @return vector<Pallet> selected pallets
 */
vector<Pallet> dynamicKnapsack(Dataset& dataset, int &totalWeight, int &totalProfit) {
    int i = dataset.pallets.size();
    int j = dataset.truckCapacity;

    vector<vector<State>> dpTable(i + 1, vector<State>(j + 1));

    for (int k = 1; k <= i; k++) { 
        Pallet currentPallet = dataset.pallets[k - 1];
        for (int l = 0; l <= j; l++) {

            dpTable[k][l] = dpTable[k - 1][l];      // Case 1: cannot include this pallet

            if (currentPallet.weight <= l) { 
                State includePallet = dpTable[k - 1][l - currentPallet.weight]; 
                includePallet.profit += currentPallet.profit;
                includePallet.palletIndices.push_back(k - 1);
                if (isBetter(includePallet, dpTable[k][l])) {
                    dpTable[k][l] = includePallet;      // Case 2: include this pallet
                }
            }
        }
    }

    State best = dpTable[i][j];
    totalProfit = best.profit;
    totalWeight = 0;
    vector<Pallet> selectedPallets;
    
    for (int index : best.palletIndices) {
        selectedPallets.push_back(dataset.pallets[index]);
        totalWeight += dataset.pallets[index].weight;
    }

    return selectedPallets;
}