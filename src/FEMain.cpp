#include "FEGrid.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * @brief Main function that drives the finite element analysis process.
 *
 * This function initializes the FEGrid object, reads node and element data from files,
 * performs calculations (e.g., gradient, area), and outputs the results.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return Returns 0 if successful, or a non-zero error code if an error occurs.
 */
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <nodeFile> <elementFile>" << endl;
        return 1;
    }

    // Initialize the grid with node and element files
    FEGrid grid(argv[1], argv[2]);

    // Example operation: compute element area
    for (int i = 0; i < grid.getNumElts(); ++i)
    {
        double area = grid.elementArea(i);
        cout << "Element " << i << " area: " << area << endl;
    }

    return 0;
}
