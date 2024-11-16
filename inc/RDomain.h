#ifndef RDOMAIN_H
#define RDOMAIN_H

#include "Domain.h"
#include <vector>
#include <string>

class RDomain : public Domain {
private:
    double length;   // Length of the domain (for rectangular/1D domains)
    double deltaX;   // Step size in x-direction for grid
    double deltaY;   // Step size in y-direction for grid (only for rectangular)
    
    std::vector<double> xGrid;  // Grid in x-direction
    std::vector<double> yGrid;  // Grid in y-direction (empty for 1D)

public:
    // Constructor to initialize the domain
    RDomain(double length, double deltaX, double deltaY = 0);

    // Method to generate a rectangular grid or 1D grid
    void GenerateGrid();

    // Override the PrintGrid function to output grid to file
    void PrintGrid(std::string outputFileName) const override;
    
    // Getters for the grids
    const std::vector<double>& GetXGrid() const { return xGrid; }
    const std::vector<double>& GetYGrid() const { return yGrid; }
};

#endif // RDOMAIN_H

