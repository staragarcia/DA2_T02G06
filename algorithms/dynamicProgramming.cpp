#include <iostream>
#include <vector>
#include "../utils/structs.h"

using namespace std;

vector<Pallet> dynamicKnapsack (Dataset& dataset, int &totalWeight, int &totalProfit) {
    int i = dataset.pallets.size();
    int j = dataset.truckCapacity;

    vector<vector<int>> table(i + 1, vector<int>(j + 1, 0));

    for (int k = 0; k <= i; k++) {
        for (int l = 0; l <= j; l++) {
            if (k == 0 || l == 0) { //no items considered or truck has 0 capacity
                table[k][l] = 0;
            } else if (dataset.pallets[k - 1].weight <= l) { //table starts with no items considered at k=0 so k-1
                table[k][l] = max(dataset.pallets[k - 1].profit + table[k - 1][l - dataset.pallets[k - 1].weight], table[k - 1][l]);
            } else {
                table[k][l] = table[k - 1][l];
            }
        }
    }

    vector<Pallet> selectedPallets = {};
    totalProfit = table[i][j];
    totalWeight = 0;
    int remainingCapacity = j;

    for (int k = i; k > 0 && totalProfit > 0; k--) {
        if (totalProfit != table[k - 1][remainingCapacity]) { //item was included
            selectedPallets.push_back(dataset.pallets[k - 1]);
            totalProfit -= dataset.pallets[k - 1].profit;
            totalWeight += dataset.pallets[k - 1].weight;
            remainingCapacity -= dataset.pallets[k - 1].weight;
        }
    }
    
    return selectedPallets;
}