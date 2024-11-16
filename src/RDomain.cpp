#include "RDomain.h"
#include <cstdio>   // For fopen, fwrite, fclose
#include <iostream>

void RDomain::PrintGrid(std::string outputFileName) const {
    // Open the file in binary write mode
    FILE* outFile = fopen(outputFileName.c_str(), "wb");
    if (!outFile) {
        std::cerr << "Failed to open file: " << outputFileName << std::endl;
        return;
    }

    // First, write X-coordinates to the file
    for (double x : xGrid) {
        fwrite(&x, sizeof(double), 1, outFile);  // Write each X-coordinate as double
    }

    // Then, write Y-coordinates to the file (if it's a rectangular grid)
    if (!yGrid.empty()) {
        for (double y : yGrid) {
            fwrite(&y, sizeof(double), 1, outFile);  // Write each Y-coordinate as double
        }
    }

    // Close the file after writing
    fclose(outFile);
}

