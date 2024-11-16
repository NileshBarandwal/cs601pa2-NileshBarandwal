#ifndef GRIDFN_H
#define GRIDFN_H

#include <vector>
#include <cmath>
#include <string>  // For std::string
#include <fstream> // For file operations

class GridFn {
private:
    double deltaX;            // Spatial step size
    double l;                  // Length of the bar
    int n;                    // Number of grid points
    std::vector<double> grid; // Stores the temperature at each grid point


public:
    // Constructor to initialize grid with the given number of grid points and length of the bar
    GridFn(int numPoints, double length);

    // Method to initialize the temperature distribution f(x)
    void initializeTemperature();

    // Method to perform one step of the diffusion calculation (using the three-point stencil)
    void step(double deltaT, double alpha);

    // Method to get the current temperature at a particular grid point
    double getTemperature(int i) const;

    // Method to print the grid (for debugging/validation)
    void printGrid() const;

    // Method to save grid data to a binary file for external use
    void saveGridToFile(const std::string& filename) const;
};

#endif

