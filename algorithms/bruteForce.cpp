#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include "../utils/structs.h"

using namespace std;

int bruteForceKnapsack(const Dataset &dataset) {
    auto start = chrono::high_resolution_clock::now();

    int maxProfit = 0;
    int n = dataset.pallets.size();
    int capacity = dataset.truckCapacity;
    vector<int> bestSubset; 
    int bestWeight = 0; 

    for (int subset = 0; subset < (1 << n); subset++) {   // 1<<n pq temos 2^n subsets
        int totalWeight = 0;
        int totalProfit = 0;
        vector<int> currentSubset;

        for (int i = 0; i < n; i++) {
            if (subset & (1 << i)) {                      // & com bitmask e somar se o bit for 1
                totalWeight += dataset.pallets[i].weight;
                totalProfit += dataset.pallets[i].profit;
                currentSubset.push_back(i);
            }
        }

        if (totalWeight <= capacity && totalProfit > maxProfit) {
            maxProfit = totalProfit;
            bestSubset = currentSubset; 
            bestWeight = totalWeight;   
        }
    }

    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double> elapsed = end - start; 

    cout << "Maximum Profit using bruteforce: " << maxProfit << endl;
    cout << "Total Weight: " << bestWeight << endl;
    cout << "Execution Time: " << elapsed.count() << " seconds" << endl;
    cout << "---- Included Pallets: ----" << endl;
    for (int index : bestSubset) {
        cout << "Pallet " << index + 1 << ": Weight = " << dataset.pallets[index].weight
             << ", Profit = " << dataset.pallets[index].profit << endl;
    }

    return maxProfit;
}