#include "ortools/linear_solver/linear_solver.h"
#include "../utils/structs.h"
#include <iostream>
#include <vector>

/**
 * @brief Function that solves the 0/1 knapsack problem using Integer Linear Programming (ILP) with OR-Tools.
 * 
 * @details This function uses the OR-Tools library to create a Mixed Integer Programming (MIP) solver.
 * The function's worst-case asymptotic complexity is O(2^N), where n is the number of items (pallets) in the dataset,
 * however, in pratice, the solver is efficient and can solve large instances of the problem.
 * 
 * @param dataset vector of pallets and truck capacity
 * @param totalWeight used to return the total weight of the selected pallets
 * @param totalProfit used to return the total profit of the selected pallets
 * @return std::vector<Pallet> selected pallets
 */
std::vector<Pallet> SolveKnapsackILP(Dataset& dataset, int &totalWeight, int &totalProfit) {
    const int num_items = dataset.pallets.size();

    // Create the MIP solver with the CBC backend.
    operations_research::MPSolver solver("KnapsackILP", operations_research::MPSolver::CBC_MIXED_INTEGER_PROGRAMMING);

    // Define decision variables: x[i] = 1 if item i is included, 0 otherwise.
    std::vector<const operations_research::MPVariable*> x(num_items);
    for (int i = 0; i < num_items; ++i) {
        x[i] = solver.MakeIntVar(0, 1, "x_" + std::to_string(i));
    }

    // Add the capacity constraint: sum(weights[i] * x[i]) <= capacity
    operations_research::MPConstraint* capacity_constraint = solver.MakeRowConstraint(0, dataset.truckCapacity, "capacity");
    for (int i = 0; i < num_items; ++i) {
        capacity_constraint->SetCoefficient(x[i], dataset.pallets[i].weight);
    }

    // Define the objective: maximize sum(values[i] * x[i])
    operations_research::MPObjective* objective = solver.MutableObjective();
    for (int i = 0; i < num_items; ++i) {
        objective->SetCoefficient(x[i], dataset.pallets[i].profit);
    }
    objective->SetMaximization();

    // Solve the problem.
    const operations_research::MPSolver::ResultStatus result_status = solver.Solve();
    
    // Print the results.
    if (result_status == operations_research::MPSolver::OPTIMAL) {
        std::vector<Pallet> selectedPallets;
        totalProfit = 0;
        totalWeight = 0;
        for (int i = 0; i < num_items; ++i) {
            if (x[i]->solution_value() == 1) {
              totalProfit += dataset.pallets[i].profit;
              totalWeight += dataset.pallets[i].weight;
              selectedPallets.emplace_back(dataset.pallets[i]);
            }
        }
        return selectedPallets;
    } else {
      totalProfit = 0;
      totalWeight = 0;
      return {};
    }
}
