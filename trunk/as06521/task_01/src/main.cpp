#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    // Параметры линейной модели
    double a_linear = 0.8;
    double b_linear = 0.2;
    
    // Параметры нелинейной модели
    double a_nonlinear = 0.7;
    double b_nonlinear = 0.005;
    double c_nonlinear = 0.25;
    double d_nonlinear = 0.1;
    
    // Начальные условия для обеих моделей
    double y_linear = 20.0;      // Линейная модель
    double y_nonlinear = 20.0;   // Нелинейная модель
    double u_t = 1.0;
    double u_prev = 0.8;
    
    int time_steps = 30;
    
    std::cout << "Моделирование температуры объекта" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << std::setw(5) << "Время" << std::setw(15) << "Линейная" 
              << std::setw(15) << "Нелинейная" << std::setw(15) << "Управление" << std::endl;
    
    for (int t = 0; t < time_steps; ++t) {
        // Линейная модель
        double linear_next = a_linear * y_linear + b_linear * u_t;
        
        // Нелинейная модель
        double nonlinear_next = a_nonlinear * y_nonlinear - 
                              b_nonlinear * y_nonlinear * y_nonlinear + 
                              c_nonlinear * u_t + 
                              d_nonlinear * sin(u_prev - 1);
        
        std::cout << std::setw(5) << t << std::setw(15) << std::fixed << std::setprecision(2) 
                  << y_linear << std::setw(15) << y_nonlinear << std::setw(15) << u_t << std::endl;
        
        // Обновляем значения
        y_linear = linear_next;
        y_nonlinear = nonlinear_next;
        u_prev = u_t;
        
        // Простое управление
        if (y_linear > 28.0) {
            u_t = 0.0;
        } else if (y_linear < 18.0) {
            u_t = 1.5;
        } else {
            u_t = 1.0;
        }
    }
    
    return 0;
}