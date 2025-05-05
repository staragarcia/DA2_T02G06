#include <iostream>
#include <vector>
#include <fstream>
#include "structs.h"
#include <sstream>

Dataset readParseDataset(const std::string& id) {
    Dataset dataset;
    std::string line;
    std::ifstream truckFile("datasets/TruckAndPallets_" + id + ".csv");
    
    if (!truckFile.is_open()) {
        std::cerr << "Could not open truck file.\n";
    }

    std::getline(truckFile, line); //Skip first line

    int capacity, numPallets;
    char comma;

    if (std::getline(truckFile, line)) {
        std::istringstream iss(line);
        if (iss >> capacity >> comma >> numPallets) {
            dataset.truckCapacity = capacity;
        }
    }
    truckFile.close();

    std::ifstream palletFile("datasets/Pallets_" + id + ".csv");
    if (!palletFile.is_open()) {
        std::cerr << "Failed to open pallet file\n";
    }

    std::getline(palletFile, line); //Skip first line

    for (int i = 0; i < numPallets; i++) {
        std::getline(palletFile, line);
        std::istringstream ss(line);
        Pallet p;
        char comma;

        ss >> p.id >> comma >> p.weight >> comma >> p.profit;
        dataset.pallets.push_back(p);
    }

    palletFile.close();

    return dataset; 
}