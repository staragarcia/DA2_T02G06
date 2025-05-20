#include <iostream>
#include "utils/structs.h"
#include <stdio.h>
#include <vector>
#include <chrono>
#include "utils/InitializeDataset.cpp"
#include "algorithms/bruteForce.cpp"
#include "algorithms/Greedy.cpp"
#include "algorithms/dynamicProgramming.cpp"
#include "algorithms/ilp.cpp"

using namespace std;
using namespace std::chrono;

// Colors
const string blue = "\033[34m";
const string gray = "\033[90m";
const string yellow = "\033[33m";
const string green = "\033[32m";
const string red = "\033[31m";
const string reset = "\033[0m";

vector<function<vector<Pallet>(Dataset&, int&, int&)>> knapsackAlgorithms = {
    bruteForceKnapsack,
    dynamicKnapsack,
    greedyKnapsack,
    SolveKnapsackILP
};

vector<string> knapsackAlgorithmNames = {
    "Brute Force",
    "Dynamic Programming",
    "Greedy Approach",
    "Integer Linear Programming (ILP)"
};


void displayMenu() {  
    cout << gray << "\n=====================================\n" << reset;
    cout << blue << "  Pallet Packing Optimization Tool\n" << reset;
    cout << gray << "=====================================\n" << reset;
    cout << yellow << "1." << reset << " Select Dataset\n";
    cout << yellow << "2." << reset << " Exit\n";
    cout << gray << "=====================================\n" << reset;
    cout << blue << "Enter your choice: " << reset;
}

void displayAlgorithmOptions() {  
    cout << yellow << "1." << reset << " Brute Force\n";
    cout << yellow << "2." << reset << " Dynamic Programming\n";
    cout << yellow << "3." << reset << " Greedy Approach\n";
    cout << yellow << "4." << reset << " Integer Linear Programming (ILP)\n";
    cout << yellow << "5." << reset << " Go Back\n";
    cout << gray << "=====================================\n" << reset;
    cout << blue << "Enter your choice: " << reset;
}

void handleAlgorithmSelection(int choice, Dataset &dataset) {
    if (choice < 1 || choice > 4) {
        cout << red << "Invalid choice. Please try again.\n" << reset;
        return;
    }
    cout << "\nRunning algorithm... " << reset;

    vector<Pallet> selected_pallets;
    int totalWeight, totalProfit;

    auto start = high_resolution_clock::now();

    bool success = false;
    try {
        selected_pallets = knapsackAlgorithms[choice-1](dataset, totalWeight, totalProfit);
        success = true;
    } catch (...) {
        cout << red << "An error occurred while running the algorithm.\n" << reset;
    }

    if (success) {
        cout << green << "Success!" << reset << endl;
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start); 

        cout << "\nSelected Pallets using " << knapsackAlgorithmNames[choice-1] << ":\n";
        for (const Pallet &p : selected_pallets) {
            cout << "Pallet ID: " << gray << p.id << reset
                << ", Weight: " << gray << p.weight << reset
                << ", Profit: " << gray << p.profit << reset << endl;
        }
        cout << "\nTotal Profit: " << gray << totalProfit << reset;
        cout << "\nTotal Weight: " << gray << totalWeight << reset;
        cout << "\nExecution Time: " << gray << duration.count() << reset << " microseconds\n" << endl;
    }
}

void handleMenuSelection(int choice, Dataset &dataset) {
    switch (choice) {
        case 1: {
            string datasetId;
            while (true) {
                cout << blue << "Enter dataset ID " << gray << "(01-10)" << reset << blue << ": " << reset;
                cin >> datasetId;

                if (datasetId.length() != 2 || datasetId < "01" || datasetId > "10") {
                    cout << red << "Invalid dataset ID. Please enter a value between 01 and 10.\n" << reset;
                    cout << gray << "=====================================\n" << reset;
                    continue; 
                }
                break; 
            }

            dataset = readParseDataset(datasetId);
            cout << gray << "=====================================\n" << reset;
            cout << blue << "Pick an algorithm to run:\n" << reset;
        
            int algorithmChoice;
            while (true) {
                displayAlgorithmOptions();
                cin >> algorithmChoice;
                if (algorithmChoice == 5) break;
                handleAlgorithmSelection(algorithmChoice, dataset);
                cout << gray << "=====================================\n" << reset;
                cout << blue << "Pick an algorithm to run:\n" << reset;
            }
            break;
        }
        case 2:
            cout << "Exiting...\n";
            break;
        default:
            cout << red << "Invalid choice. Please try again.\n" << reset;
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
