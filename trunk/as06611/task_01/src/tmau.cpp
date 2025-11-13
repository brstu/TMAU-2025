#include <iostream>
#include <cmath>
#include <locale>

const int N = 15;
const double A = 0.9;
const double B = 0.01;
const double C = 0.4;
const double D = 0.1;
const double Y_start = 20;

double linearModel(double y, double u) {
    return A * y + B * u;
}

double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev) {
    return A * y_curr - B * pow(y_prev, 2) + C * u_curr + D * sin(u_prev);
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    
    double U[N] = {4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 5, 6};

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

    // Для нелинейной модели нужны два предыдущих значения y
    double y_prev = Y_start;  // y_{τ-1}
    // Для первого шага используем упрощенный расчет y₁
    double y_curr = A * Y_start + C * U[0];  // y_τ

    std::cout << "y1 = " << y_curr << std::endl;

    // Остальные значения
    for (int i = 1; i < N; i++) {
        double y_next = nonlinearModel(y_curr, y_prev, U[i], U[i - 1]);
        std::cout << "y" << i + 1 << " = " << y_next << std::endl;
        
        // Сдвиг значений для следующей итерации
        y_prev = y_curr;
        y_curr = y_next;
    }

    std::cin.get();
    return 0;
}