#include "model.h"
#include <iostream>
#include <vector>

int main() {
    Params prm;
    std::vector<double> input(10, 4.0);

    auto y_linear = lin_model(prm, input);
    auto y_nonlinear = nonlin_model(prm, input);

    std::cout << "Linear:\n";
    for (int idx = 0; idx < static_cast<int>(y_linear.size()); ++idx)
        std::cout << "y" << idx << ": " << y_linear[idx] << std::endl;

    std::cout << "\nNonlinear:\n";
    for (int idx = 0; idx < static_cast<int>(y_nonlinear.size()); ++idx)
        std::cout << "y" << idx << ": " << y_nonlinear[idx] << std::endl;

    return 0;
}
