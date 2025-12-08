#include <iostream>
#include <vector>
#include "model.h"

int main() {
    double input = 20.0;

    std::vector<double> linearOutput = simulateLinear(input);
    std::vector<double> nonlinearOutput = simulateNonlinear(input);

    std::cout << "Step\tLinear\t\tNonlinear" << std::endl;
    for (int i = 0; i < iterationsCount; ++i) {
        std::cout << i << "\t" << linearOutput[i] << "\t\t" << nonlinearOutput[i] << std::endl;
    }

    return 0;
}
