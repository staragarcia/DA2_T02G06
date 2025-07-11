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
#include <limits>
#include <fstream> 

using namespace std;
using namespace std::chrono;

/// @cond
// Colors
const string blue = "\033[34m";
const string gray = "\033[90m";
const string yellow = "\033[33m";
const string green = "\033[32m";
const string red = "\033[31m";
const string reset = "\033[0m";
/// @endcond

vector<function<vector<Pallet>(Dataset&, int&, int&)>> knapsackAlgorithms = {
    bruteForceKnapsack,
    backtrackingKnapsack,
    dynamicKnapsack,
    greedyKnapsack,
    SolveKnapsackILP
};

vector<int> maxDatasetSizePerAlgorithm = {
    25, // Brute Force, with 25 pallets should take around 20 seconds
    34, // Brute Force with Backtracking
    std::numeric_limits<int>::max(), // Dynamic Programming
    std::numeric_limits<int>::max(), // Greedy Approach
    1000000 // Integer Linear Programming (ILP)
};

vector<string> knapsackAlgorithmNames = {
    "Brute Force",
    "Brute Force with Backtracking",
    "Dynamic Programming",
    "Greedy Approach",
    "Integer Linear Programming (ILP)"
};

/**
 * @brief Displays the main menu for the user interface.
 */
void displayMenu() {  
    cout << gray << "\n=====================================\n" << reset;
    cout << blue << "  Pallet Packing Optimization Tool\n" << reset;
    cout << gray << "=====================================\n" << reset;
    cout << yellow << "1." << reset << " Select Dataset\n";
    cout << yellow << "2." << reset << " Exit\n";
    cout << gray << "=====================================\n" << reset;
    cout << blue << "Enter your choice: " << reset;
}

/**
 * @brief Shows the list of available algorithm options.
 */
void displayAlgorithmOptions() {  
    cout << yellow << "1." << reset << " Brute Force\n";
    cout << yellow << "2." << reset << " Brute Force with Backtracking\n";
    cout << yellow << "3." << reset << " Dynamic Programming\n";
    cout << yellow << "4." << reset << " Greedy Approach\n";
    cout << yellow << "5." << reset << " Integer Linear Programming (ILP)\n";
    cout << yellow << "6." << reset << " Run All Algorithms\n";
    cout << yellow << "7." << reset << " Go Back\n";
    cout << gray << "=====================================\n" << reset;
    cout << blue << "Enter your choice: " << reset;
}

/**
 * @brief Handles the execution of the selected algorithm and displays results.
 */
void handleAlgorithmSelection(int choice, Dataset &dataset) {
    if (choice < 1 || choice > 5) {
        cout << red << "Invalid choice. Please try again.\n" << reset;
        return;
    }
    if (dataset.pallets.size() > maxDatasetSizePerAlgorithm[choice-1]) {
        cout << red << "Dataset size exceeds the maximum limit for this algorithm.\n" << reset;
        return;
    }
    cout << "\nRunning algorithm...\n";
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

        //Output file
        std::ofstream outfile("outputs/output.txt");
        outfile << "Selected Pallets using " << knapsackAlgorithmNames[choice-1] << ":\n";
        for (const Pallet &p : selected_pallets) {
            outfile << "Pallet ID: " << p.id
                    << ", Weight: " << p.weight
                    << ", Profit: " << p.profit << std::endl;
        }
        outfile << "\nTotal Profit: " << totalProfit;
        outfile << "\nTotal Weight: " << totalWeight;
        outfile << "\nExecution Time: " << duration.count() << " microseconds\n";
        outfile.close();
    }
}

/**
 * @brief Runs all available algorithms on the current dataset and outputs results.
 */
void runAllAlgorithms(Dataset &dataset) {
    cout << gray << "\n=====================================\n" << reset;
    cout << "Running all algorithms on the current dataset:\n" << reset;

    std::ofstream outfile("outputs/output.txt");
    outfile << "Results for all algorithms:\n";
    outfile.close();

    for (size_t i = 0; i < knapsackAlgorithms.size(); ++i) {
        cout << gray << "-------------------------------------\n" << reset;
        cout << blue << knapsackAlgorithmNames[i] << ":" << reset << endl; // <-- Move this line up

        int totalWeight = 0, totalProfit = 0;

        if (dataset.pallets.size() > maxDatasetSizePerAlgorithm[i]) {
            cout << red << "Dataset size exceeds the maximum limit for this algorithm." << reset << endl;
            continue;
        }

        auto start = high_resolution_clock::now();
        vector<Pallet> selected_pallets;
        bool success = false;
        try {
            selected_pallets = knapsackAlgorithms[i](dataset, totalWeight, totalProfit);
            success = true;
        } catch (...) {
            cout << red << "An error occurred while running " << knapsackAlgorithmNames[i] << "." << reset << endl;
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        if (success) {
            cout << green << "  Success!" << reset << endl;
            cout << "  Selected Pallet IDs: " << gray;
            vector<int> ids;
            for (const Pallet &p : selected_pallets) {
                ids.push_back(p.id);
            }
            sort(ids.begin(), ids.end());
            for (size_t i = 0; i < ids.size(); ++i) {
                cout << ids[i];
                if (i < ids.size() - 1) cout << ", ";
            }
            cout << reset << endl;
            cout << "  Total Profit: " << gray << totalProfit << reset << endl;
            cout << "  Total Weight: " << gray << totalWeight << reset << endl;
            cout << "  Execution Time: " << gray << duration.count() << reset << " microseconds" << endl;
        }

        // Append to output file
        std::ofstream outfile("outputs/output.txt", std::ios::app);
        outfile << knapsackAlgorithmNames[i] << ":\n";
        if (success) {
            for (const Pallet &p : selected_pallets) {
                outfile << "Pallet ID: " << p.id
                        << ", Weight: " << p.weight
                        << ", Profit: " << p.profit << std::endl;
            }
            outfile << "Total Profit: " << totalProfit << std::endl;
            outfile << "Total Weight: " << totalWeight << std::endl;
            outfile << "Execution Time: " << duration.count() << " microseconds\n";
        } else {
            outfile << "Error or limit exceeded.\n";
        }
        outfile << std::endl;
        outfile.close();
    }
}

/**
 * @brief Processes the user's main menu selection.
 */
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
                if (algorithmChoice == 6) {
                    runAllAlgorithms(dataset);
                    cout << gray << "=====================================\n" << reset;
                    cout << blue << "Pick an algorithm to run:\n" << reset;
                    continue;
                }
                if (algorithmChoice == 7) break;
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
