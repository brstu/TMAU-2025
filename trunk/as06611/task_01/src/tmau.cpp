#include <iostream>
#include <cmath>
#include <locale>
#include <array>

const int N = 15;
const double A = 0.9;
const double B = 0.01;
const double C_val = 0.4;
const double D_val = 0.1;
const double Y_start = 20;

/**
 * Computes the next temperature value using a linear model (equation 2 from the documentation).
 * @param y Current temperature value (y_τ).
 * @param u Current control input (u_τ).
 * @return Next temperature value (y_{τ+1}) calculated as A * y + B * u.
 */
double linearModel(double y, double u) {
    return A * y + B * u;
}

/**
 * Computes the next temperature value using a nonlinear model (equation 3 from the documentation).
 *
 * Parameters:
 *   y_curr  - current temperature value (y_τ)
 *   y_prev  - previous temperature value (y_{τ-1})
 *   u_curr  - current control input (u_τ)
 *   u_prev  - previous control input (u_{τ-1})
 *
 * Returns:
 *   The next temperature value according to the nonlinear model.
 */
double nonlinearModel(double y_curr, double y_prev, double u_curr, double u_prev) {
    return A * y_curr - B * pow(y_prev, 2) + C_val * u_curr + D_val * sin(u_prev);
}

int main() {
    if (!std::setlocale(LC_ALL, "ru_RU.UTF-8")) {
        std::cerr << "Warning: Locale 'ru_RU.UTF-8' not available. Using default locale." << std::endl;
    }
    
    std::array<double, N> U = {4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 5, 6};

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
    // Для первого шага используем полное уравнение модели, 
    // Используем Y_start для y_prev и U[0] для u_prev, чтобы начальное условие было согласовано с входной последовательностью.
    double y_curr = nonlinearModel(Y_start, Y_start, U[0], U[0]);  // y_τ

    std::cout << "y1 = " << y_curr << std::endl;

    // Остальные значения
    for (int i = 1; i < N; i++) {
        double y_next = nonlinearModel(y_curr, y_prev, U[i], U[i - 1]);
        std::cout << "y" << i + 1 << " = " << y_next << std::endl;
        
        // Сдвиг значений для следующей итерации
        y_prev = y_curr;
        y_curr = y_next;
    }

#ifdef PAUSE_ON_EXIT
    std::cin.get();
#endif
    return 0;
}