#include <iostream>
#include <vector>
#include <algorithm>
#include "../utils/structs.h"
using namespace std;

bool sortByDescRatio(const Pallet& a, const Pallet& b) {
    return a.ratio > b.ratio;
}

/**
 * @brief 
 * @details Final Time Complexity: O(n log n)
 * 
 * @param dataset 
 * @param totalWeight 
 * @param totalProfit 
 * @return vector<Pallet> 
 */
vector<Pallet> greedyKnapsack (Dataset& dataset, int &totalWeight, int &totalProfit) { // O(n)
    for (Pallet &p : dataset.pallets) {
        p.ratio = static_cast<double>(p.profit) / p.weight;
    }

    sort(dataset.pallets.begin(), dataset.pallets.end(), sortByDescRatio); // O(n log n)

    vector<Pallet> selectedPallets;
    int remainingCapacity = dataset.truckCapacity;
    totalProfit = 0;

    for (Pallet& p : dataset.pallets) { // O(n)
        if (p.weight <= remainingCapacity) {
            selectedPallets.push_back(p);
            remainingCapacity -= p.weight;
            totalProfit += p.profit;
        }
    }
    
    totalWeight = dataset.truckCapacity - remainingCapacity;

    return selectedPallets;
}