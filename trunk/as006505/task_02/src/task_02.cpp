#include "model.h"
#include <iostream>

int main() {
    double a1 = 0.3;
    double b1 = 0.3;
    double u1 = 0.9;
    int n1 = 10;
    
    std::cout << "Линейная модель:\n";
    auto result1 = simulateLinearVec(a1, b1, u1, n1);
    for (int i = 0; i < n1; ++i) {
        std::cout << "τ=" << i << ": y=" << result1[i] << std::endl;
    }
    
    std::cout << std::endl;

    double a2 = 0.1;
    double b2 = 0.2;
    double c2 = 0.4;
    double d2 = 0.2;
    double u2 = 0.8;
    int n2 = 10;
    
    std::cout << "Нелинейная модель:\n";
    auto result2 = simulateNonlinearVec(a2, b2, c2, d2, u2, n2);
    for (int i = 0; i < n2; ++i) {
        std::cout << "τ=" << i << ": y=" << result2[i] << std::endl;
    }

    return 0;
}
