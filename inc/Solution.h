#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>

class Solution {
public:
    // Constructor Declaration
    Solution(double alpha, double length, double deltaX, double deltaT, int maxSteps);

    // Destructor Declaration
    ~Solution();

    // Member Functions Declarations
    void set_initial_conditions();
    double initial_condition(double x);
    void compute_next_step();
    bool check_convergence();
    void solve();
    void output_results(const std::string &filename);

private:
    double alpha, length, deltaX, deltaT;
    int maxSteps;
    // Other private member variables
};

#endif // SOLUTION_H

