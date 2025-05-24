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
 * @brief 
 * @details  Time Complexity: O(i × j)
 * 
 * @param dataset 
 * @param totalWeight 
 * @param totalProfit 
 * @return vector<Pallet> 
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