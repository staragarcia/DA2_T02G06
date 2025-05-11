#include <iostream>
#include "utils/structs.h"
#include <stdio.h>
#include <vector>
#include <chrono>
#include "utils/InitializeDataset.cpp"
#include "algorithms/bruteForce.cpp"
#include "algorithms/Greedy.cpp"
#include "algorithms/dynamicProgramming.cpp"

using namespace std;
using namespace std::chrono;


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
         cout << "2. Dynamic Programming\n";
         cout << "3. Greedy Approach\n";
         cout << "4. TBA\n";
         cout << "=====================================\n";
         cout << "Enter your choice: ";
}

void handleAlgorithmSelection(int choice, Dataset &dataset) {
    cout << "\nRunning algorithm...\n";
    vector<Pallet> selected_pallets;
    int totalWeight, totalProfit;

    switch (choice) {
        case 1: {
            auto start = high_resolution_clock::now();

            selected_pallets = bruteForceKnapsack(dataset, totalWeight, totalProfit);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start); 

            cout << "\nSelected Pallets using Brute Force:\n";
            for (const Pallet &p : selected_pallets) {
                cout << "Pallet ID: " << p.id << ", Weight: " << p.weight << ", Profit: " << p.profit << endl;
            }
            cout << "\nTotal Profit: " << totalProfit << endl;
            cout << "\nTotal Weight: " << totalWeight << endl;
            cout << "\nExecution Time: " << duration.count() << " microseconds\n";
            
            break;
        }
        case 2: {
            auto start = high_resolution_clock::now();

            selected_pallets = dynamicKnapsack(dataset, totalWeight, totalProfit);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start); 

            cout << "\nSelected Pallets using Dynamic Programming:\n";
            for (const Pallet &p : selected_pallets) {
                cout << "Pallet ID: " << p.id << ", Weight: " << p.weight << ", Profit: " << p.profit << endl;
            }
            cout << "\nTotal Profit: " << totalProfit << endl;
            cout << "\nTotal Weight: " << totalWeight << endl;
            cout << "\nExecution Time: " << duration.count() << " microseconds\n";
            
            break;
        }
        case 3: {
            auto start = high_resolution_clock::now();

            selected_pallets = greedyKnapsack(dataset, totalWeight, totalProfit);

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start); 

            cout << "\nSelected Pallets using Greedy Approach:\n";
            for (const Pallet &p : selected_pallets) {
                cout << "Pallet ID: " << p.id << ", Weight: " << p.weight << ", Profit: " << p.profit << endl;
            }
            cout << "\nTotal Profit: " << totalProfit << endl;
            cout << "\nTotal Weight: " << totalWeight << endl;
            cout << "\nExecution Time: " << duration.count() << " microseconds\n";
            
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
}

void handleMenuSelection(int choice, Dataset &dataset) {
    switch (choice) {
        case 1: {
            string datasetId;
            cout << "Enter dataset ID (01-10): ";
            cin >> datasetId;
            dataset = readParseDataset(datasetId);
            cout << "Dataset loaded successfully.\n";
            cout << "=====================================\n";
            cout << "Pick an algorithm to run:\n";
        
            int algorithmChoice;
            while (true) {
                displayAlgorithmOptions();
                cin >> algorithmChoice;

                if (algorithmChoice == 1 || algorithmChoice == 2 || algorithmChoice == 3) {
                    handleAlgorithmSelection(algorithmChoice, dataset);
                    break;
                } else {
                    cout << "Invalid choice. Please try again.\n";
                }
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
