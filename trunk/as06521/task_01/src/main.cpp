#include <iostream>
#include <cmath>
#include <vector>

int main() {
    // Параметры для линейной модели
    double a = 0.8;
    double b = 0.2;
    
    // Параметры для нелинейной модели
    double c = 0.15;
    double d = 0.05;
    
    // Начальные условия
    double y_t = 20.0;    // текущая температура
    double y_t_prev = 19.5; // предыдущая температура (для нелинейной модели)
    double u_t = 1.0;     // управляющее воздействие
    
    int time_steps = 50;
    
    std::cout << "Моделирование температуры объекта" << std::endl;
    std::cout << "Время\tЛинейная модель\tНелинейная модель" << std::endl;
    
    for (int t = 0; t < time_steps; ++t) {
        // Линейная модель
        double linear_y = a * y_t + b * u_t;
        
        // Нелинейная модель
        double nonlinear_y = a * y_t - b * y_t_prev * y_t_prev + c * u_t + d * sin(u_t - 1);
        
        std::cout << t << "\t" << linear_y << "\t\t" << nonlinear_y << std::endl;
        
        // Обновляем значения для следующего шага
        y_t_prev = y_t;
        y_t = linear_y; // или можно использовать nonlinear_y
        
        // Простое управление (можно улучшить)
        if (y_t > 25.0) {
            u_t = 0.0;
        } else if (y_t < 15.0) {
            u_t = 1.0;
        }
    }
    
    return 0;
}