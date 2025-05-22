#include <iostream>
#include "utils/structs.h"
#include <stdio.h>
#include <vector>
#include <chrono>
#include "utils/InitializeDataset.cpp"
#include "algorithms/backtrackingBruteForce.cpp"
#include "algorithms/bruteForce.cpp"
#include "algorithms/Greedy.cpp"
#include "algorithms/dynamicProgramming.cpp"
#include "algorithms/ilp.cpp"

using namespace std;
using namespace std::chrono;

vector<function<vector<Pallet>(Dataset&, int&, int&)>> knapsackAlgorithms = {
    bruteForceKnapsack,
    backtrackingKnapsack,
    dynamicKnapsack,
    greedyKnapsack,
    SolveKnapsackILP
};

vector<string> knapsackAlgorithmNames = {
    "Brute Force",
    "Brute Force with Backtracking",
    "Dynamic Programming",
    "Greedy Approach",
    "Integer Linear Programming (ILP)"
};


void displayMenu() {  
cout << "\n=====================================\n";
    cout << "  Pallet Packing Optimization Tool\n";
     cout << "=====================================\n";
     cout << "1. Select Dataset\n";
     cout << "2. Exit\n";
     cout << "=====================================\n";
     cout << "Enter your choice: ";
}


void displayAlgorithmOptions() {  
         cout << "1. Brute Force\n";
         cout << "2. Brute Force with Backtracking\n";
         cout << "3. Dynamic Programming\n";
         cout << "4. Greedy Approach\n";
         cout << "5. Integer Linear Programming (ILP)\n";
         cout << "=====================================\n";
         cout << "Enter your choice: ";
}

void handleAlgorithmSelection(int choice, Dataset &dataset) {
    if (choice < 1 || choice > 5) {
        cout << "Invalid choice. Please try again.\n";
        return;
    }
    cout << "\nRunning algorithm...\n";
    vector<Pallet> selected_pallets;
    int totalWeight, totalProfit;

    auto start = high_resolution_clock::now();

    selected_pallets = knapsackAlgorithms[choice-1](dataset, totalWeight, totalProfit);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start); 

    cout << "\nSelected Pallets using " << knapsackAlgorithmNames[choice-1] << ":\n";
    for (const Pallet &p : selected_pallets) {
        cout << "Pallet ID: " << p.id << ", Weight: " << p.weight << ", Profit: " << p.profit << endl;
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
    cout << "\nTotal Weight: " << totalWeight << endl;
    cout << "\nExecution Time: " << duration.count() << " microseconds\n";
}

void handleMenuSelection(int choice, Dataset &dataset) {
    switch (choice) {
        case 1: {
            string datasetId;
            cout << "Enter dataset ID (01-10): ";
            cin >> datasetId;
            dataset = readParseDataset(datasetId);
            cout << "=====================================\n";
            cout << "Pick an algorithm to run:\n";
        
            int algorithmChoice;
            while (true) {
                displayAlgorithmOptions();
                cin >> algorithmChoice;
                handleAlgorithmSelection(algorithmChoice, dataset);
            }
            break;
        }
        case 2:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
}

int main() {
    Dataset dataset;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;
        if (choice == 2) break;
        handleMenuSelection(choice, dataset);
    }
    return 0;
}
