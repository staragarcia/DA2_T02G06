#include <iostream>
#include <vector>
#include <algorithm>
#include "../utils/structs.h"
using namespace std;


/**
 * @brief Sorts pallets by descending order.
 * TieBreakers are lower weight and then lower id.
 * 
 * @param a First pallet to compare
 * @param b Second pallet to compare
 * @return true if a should come before b, false otherwise
 */
bool sortByDescRatio(const Pallet& a, const Pallet& b) {
    if (a.ratio != b.ratio)
        return a.ratio > b.ratio;
    if (a.weight != b.weight)
        return a.weight > b.weight; 
    return a.id < b.id;
}

/**
 * @brief Greedy Knapsack Algorithm implementation.
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