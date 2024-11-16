#include "GridFn.h"
#include <iostream>
#include <fstream>

// Constructor to initialize grid
//GridFn::GridFn(int numPoints, double length)
//    : n(numPoints), l(length), deltaX(length / (numPoints - 1)) {
//    grid.resize(n, 0.0);  // Initialize grid with zero values
//}
GridFn::GridFn(int numPoints, double length)
    : deltaX(length / (numPoints - 1)),  // Correct initialization order
      l(length),
      n(numPoints) {
    // Initialize the grid with all zeroes
    grid.resize(n, 0.0);
}

// Method to initialize the temperature distribution based on f(x)
void GridFn::initializeTemperature() {
    for (int i = 0; i < n; ++i) {
        double x = i * deltaX;
        grid[i] = x * std::sqrt(std::pow((l - x), 3));
    }
}

// Method to perform one time step of the heat diffusion calculation
void GridFn::step(double deltaT, double alpha) {
    std::vector<double> newGrid = grid;  // Create a copy for the new values

    // Use the three-point stencil for the interior points
    for (int i = 1; i < n - 1; ++i) {
        newGrid[i] = grid[i] + deltaT * alpha * (grid[i-1] - 2*grid[i] + grid[i+1]) / (deltaX * deltaX);
    }

    grid = newGrid;  // Update the grid with the new temperature values
}

// Method to get the temperature at a specific grid point
double GridFn::getTemperature(int i) const {
    if (i >= 0 && i < n) {
        return grid[i];
    }
    return -1; // Invalid index
}

// Method to print the grid (for debugging/validation)
void GridFn::printGrid() const {
    for (int i = 0; i < n; ++i) {
        std::cout << "x = " << i * deltaX << ", T = " << grid[i] << std::endl;
    }
}

// Optional: Method to save grid data to a binary file for external use
void GridFn::saveGridToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&n), sizeof(n));  // Write number of grid points
        outFile.write(reinterpret_cast<const char*>(&l), sizeof(l));  // Write length of the domain
        outFile.write(reinterpret_cast<const char*>(&deltaX), sizeof(deltaX));  // Write spatial step size
        outFile.write(reinterpret_cast<const char*>(grid.data()), grid.size() * sizeof(double));  // Write grid data
        outFile.close();
    } else {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }
}

