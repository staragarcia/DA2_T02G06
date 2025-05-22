#include <iostream>
#include <vector>
#include <cmath>
#include "../utils/structs.h"

using namespace std;

/**
 * @brief Brute force solution for the 0/1 knapsack problem. Selects the best subset of pallets
 * by checking all possible combinations.
 * 
 * @details The asymptotic complexity of this algorithm is Θ(2^n), where n is the number of pallets.
 * 
 * @param dataset pallets and truck capacity
 * @param totalWeight total weight of selected pallets
 * @param totalProfit total profit of selected pallets
 * @return vector<Pallet> selected pallets
 */
vector<Pallet> bruteForceKnapsack(Dataset &dataset, int &totalWeight, int &totalProfit) {

    int maxProfit = 0;
    int n = dataset.pallets.size();
    int capacity = dataset.truckCapacity;
    vector<int> bestSubset; 
    int bestWeight = 0; 

    for (int subset = 0; subset < (1 << n); subset++) {   // 1<<n pq temos 2^n subsets
        int currentWeight = 0;
        int currentProfit = 0;
        vector<int> currentSubset;

        for (int i = 0; i < n; i++) {
            if (subset & (1 << i)) {                      // & com bitmask e somar se o bit for 1
                currentWeight += dataset.pallets[i].weight;
                currentProfit += dataset.pallets[i].profit;
                currentSubset.push_back(i);
            }
        }

        if (currentWeight <= capacity && currentProfit > maxProfit) {
            maxProfit = currentProfit;
            bestSubset = currentSubset; 
            bestWeight = currentWeight;   
        }
    }

    vector<Pallet> selectedPallets;
    for (int index : bestSubset) selectedPallets.push_back(dataset.pallets[index]);
    
    // Update totalWeight and totalProfit
    totalWeight = bestWeight;
    totalProfit = maxProfit;

    return selectedPallets;
}