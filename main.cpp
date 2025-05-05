#include <iostream>
#include "utils/structs.h"
#include <stdio.h>
#include <vector>
#include "algorithms/bruteForce.cpp"
#include "utils\initializeDataset.cpp"

using namespace std;


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
         cout << "2. TBA\n";
         cout << "=====================================\n";
         cout << "Enter your choice: ";
    }


void handleAlgorithmSelection(int choice, const Dataset &dataset);

void handleMenuSelection(int choice, Dataset &dataset) {
    switch (choice) {
        case 1: {
            string datasetId;
            cout << "Enter dataset ID: ";
            cin >> datasetId;
            dataset = readParseDataset(datasetId);
            cout << "Dataset loaded successfully.\n";
            cout << "=====================================\n";
            cout << "Pick an algorithm to run:\n";
        
            int algorithmChoice;
            while (true) {
                displayAlgorithmOptions();
                cin >> algorithmChoice;

                if (algorithmChoice == 1) {
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

void handleAlgorithmSelection(int choice, const Dataset &dataset) {
    cout << "\nRunning algorithm...\n" << "\n";

    switch (choice) {
        case 1: {
            bruteForceKnapsack(dataset);
            break;
        }
        case 2:
            cout << "TBA\n";
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
