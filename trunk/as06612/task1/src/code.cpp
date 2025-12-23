#include <iostream>
#include <cmath>

const double coeff_temp = 0.6;
const double coeff_prev_temp = 0.3;
const double coeff_warm = 0.8;
const double coeff_prev_warm = 0.5;

double compute_linear(double temp_val, double warm_val);
double get_warm_variation(double warm_base, int step_num);
double compute_nonlinear(double curr_temp, double last_temp, double curr_warm, double last_warm);

int main() {
    
    int total_steps;
    double init_temp;
    double init_warm;
    
    std::cout << "Введите количество итераций, стартовую температуру T0 и стартовый тепловой поток W0: ";
    std::cin >> total_steps >> init_temp >> init_warm;

    double previous_temp_value = init_temp;
    double previous_warm_value = init_warm;

    std::cout << "\nРезультаты линейного расчета:\n";
    double linear_temp_result = init_temp;
    for (int step = 1; step <= total_steps; step++) {
        linear_temp_result = compute_linear(linear_temp_result, init_warm);
        std::cout << "Итерация " << step << ": T = " << linear_temp_result << std::endl;
    }

    std::cout << "\nРезультаты нелинейного расчета:\n";
    double nonlinear_temp_result = init_temp;
    for (int step = 1; step <= total_steps; step++) {
        double modified_warm = get_warm_variation(init_warm, step);
        double new_temp = compute_nonlinear(nonlinear_temp_result, previous_temp_value, modified_warm, previous_warm_value);
        std::cout << "Итерация " << step << ": T = " << new_temp << std::endl;
        previous_temp_value = nonlinear_temp_result;
        nonlinear_temp_result = new_temp;
        previous_warm_value = modified_warm;
    }

    return 0;
}

double compute_linear(double temp_val, double warm_val) {
    return coeff_temp * temp_val + coeff_prev_temp * warm_val;
}

double get_warm_variation(double warm_base, int step_num) {
    return warm_base + 0.1 * sin(step_num);
}

double compute_nonlinear(double curr_temp, double last_temp, double curr_warm, double last_warm) {
    double part1 = coeff_temp * curr_temp;
    double part2 = coeff_prev_temp * pow(last_temp, 2);
    double part3 = coeff_warm * curr_warm;
    double part4 = coeff_prev_warm * sin(last_warm);
    
    return part1 - part2 + part3 + part4;
}
