#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <vector>
using namespace std;


typedef struct {
    int id;       
    int weight;          
    int profit;      
    float ratio;   
} Pallet;

typedef struct {
    vector<Pallet> pallets;        
    int truckCapacity;        
} Dataset;


#endif