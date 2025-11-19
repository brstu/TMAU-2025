#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>



// Линейная модель системы
double linear_model(double current_y, double input_u, double param_a, double param_b) {
    double result = param_a * current_y + param_b * input_u;
    return result;
}

// Нелинейная модель системы с дополнительными эффектами
double nonlinear_model(double y_current, double y_previous, 
                      double u_current, double u_previous, 
                      double a_param, double b_param, 
                      double c_param, double d_param) {
    // Вычисление нелинейной компоненты
    double nonlinear_component = a_param * y_current - b_param * std::pow(y_previous, 2) 
                               + c_param * u_current + d_param * std::sin(u_previous);
    return nonlinear_component;
}

// Вспомогательная функция для инициализации вектора
std::vector<double> initialize_vector(int size, double initial_value) {
    return std::vector<double>(size, initial_value);
}

int main() {
    // Параметры симуляции
    const int TIME_STEPS = 30;
    const double PARAM_A = 0.8;
    const double PARAM_B = 0.15; 
    const double PARAM_C = 0.05;
    const double PARAM_D = 0.1;
    const double INPUT_VALUE = 1.0;

    // Инициализация массивов данных
    std::vector<double> input_signal = initialize_vector(TIME_STEPS, INPUT_VALUE);
    std::vector<double> linear_output = initialize_vector(TIME_STEPS, 0.0);
    std::vector<double> nonlinear_output = initialize_vector(TIME_STEPS, 0.0);

    // Установка начальных условий
    linear_output[0] = 0.0;
    nonlinear_output[0] = 0.0;

    // Процесс моделирования системы
    for (int time_step = 1; time_step < TIME_STEPS; ++time_step) {
        // Обновление линейной модели
        linear_output[time_step] = linear_model(
            linear_output[time_step - 1], 
            input_signal[time_step - 1], 
            PARAM_A, 
            PARAM_B
        );

        // Обновление нелинейной модели
        if (time_step >= 2) {
            nonlinear_output[time_step] = nonlinear_model(
                nonlinear_output[time_step - 1],
                nonlinear_output[time_step - 2], 
                input_signal[time_step - 1],
                input_signal[time_step - 2],
                PARAM_A, PARAM_B, PARAM_C, PARAM_D
            );
        } else {
            // Используем линейную аппроксимацию для первых шагов
            nonlinear_output[time_step] = linear_model(
                nonlinear_output[time_step - 1],
                input_signal[time_step - 1],
                PARAM_A,
                PARAM_B
            );
        }
    }

    // Форматированный вывод результатов
    std::cout << "\n=== РЕЗУЛЬТАТЫ МОДЕЛИРОВАНИЯ ===\n";
    std::cout << "Время\tЛинейная\tНелинейная\n";
    std::cout << "-----\t---------\t----------\n";
    
    for (int t = 0; t < TIME_STEPS; ++t) {
        std::cout << std::setw(2) << t << "\t" 
                  << std::fixed << std::setprecision(6)
                  << linear_output[t] << "\t" 
                  << nonlinear_output[t] << "\n";
    }

    std::cout << "\nМоделирование завершено успешно!\n";

    return 0;
}
