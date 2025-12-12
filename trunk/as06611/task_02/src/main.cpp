#include <iostream>
#include "functions.h"

int main() {
    // Линейная модель
    std::cout << "Линейная модель:" << std::endl;
    std::cout << "y0 = " << Y_start << std::endl;
    
    double y = Y_start;
    for (int i = 0; i < N; i++) {
        y = linearModel(y, U[i]);
        std::cout << "y" << i + 1 << " = " << y << std::endl;
    }
    
    // Нелинейная модель
    std::cout << "\nНелинейная модель:" << std::endl;
    std::cout << "y0 = " << Y_start << std::endl;
    
    double y_prev = Y_start;
    double y_curr = nonlinearModel(Y_start, Y_start, U[0], U[0]);
    std::cout << "y1 = " << y_curr << std::endl;
    
    for (int i = 1; i < N; i++) {
        double y_next = nonlinearModel(y_curr, y_prev, U[i], U[i - 1]);
        std::cout << "y" << i + 1 << " = " << y_next << std::endl;
        
        y_prev = y_curr;
        y_curr = y_next;
    }
    
    return 0;
}
