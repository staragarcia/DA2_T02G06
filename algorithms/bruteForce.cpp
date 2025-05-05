#include <iostream>
#include <vector>
#include <cmath>
#include "../utils/structs.h"

using namespace std;

int bruteForceKnapsack(const Dataset &dataset) {
    int maxProfit = 0;
    int n = dataset.pallets.size();
    int capacity = dataset.truckCapacity;

    for (int subset = 0; subset < (1 << n); subset++) {   // 1<<n pq temos 2^n subsets
        int totalWeight = 0;
        int totalProfit = 0;

        for (int i = 0; i < n; i++) {
            if (subset & (1 << i)) {                      // & com bitmask e somar se o bit for 1
                totalWeight += dataset.pallets[i].weight;
                totalProfit += dataset.pallets[i].profit;
            }
        }

        if (totalWeight <= capacity) {
            maxProfit = max(maxProfit, totalProfit);
        }
    }

    return maxProfit;
}