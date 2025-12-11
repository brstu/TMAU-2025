#include "model.h"
#include <iostream>
#include <vector>

int main() {
    Constants con;
    std::vector<double> u(10, 4.0);

    auto y_linear = linear(con, u);
    auto y_nonlinear = nonlinear(con, u);

    std::cout << "Linear:\n";
    for (int i = 0; i < static_cast<int>(y_linear.size()); ++i)
        std::cout << "y" << i << ": " << y_linear[i] << std::endl;

    std::cout << "\nNonlinear:\n";
    for (int i = 0; i < static_cast<int>(y_nonlinear.size()); ++i)
        std::cout << "y" << i << ": " << y_nonlinear[i] << std::endl;

    return 0;
}
