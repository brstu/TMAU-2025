#include <iostream>
#include <vector>
#include <cmath>
#include "module.h"
using namespace std;
int main() {
    std::setlocale(LC_ALL, "rus");

    int N;
    std::cout << "Введите число шагов N (N < 100): ";
    std::cin >> N;
    if (N >= 100) {
        std::cout << "Ошибка: выход за границу\n";
        return 1;
    }

    double a;
    double b;
    double c;
    double d;

    std::cout << "Введите константы a, b, c, d: ";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cin >> d;

    std::vector<double> u(N);
    std::cout << "Введите значения u(t) для t = 0.." << N - 1 << ":\n";
    for (int t = 0; t < N; ++t) {
        std::cout << "u[" << t << "] = ";
        std::cin >> u[t];
    }

    std::vector<double> y_lin(N + 1);
    std::vector<double> y_nl(N + 1);

    std::cout << "Введите начальную температуру y[0]: ";
    std::cin >> y_lin[0];
    y_nl[0] = y_lin[0];

    std::cout << "Введите y[1] для нелинейной модели: ";
    std::cin >> y_nl[1];

    // Линейная модель
    compute_linear(N, a, b, u, y_lin);

    // Нелинейная модель
    compute_nonlinear(N, a, b, c, d, u, y_nl);

    std::cout << "\nРезультаты моделирования:\n";
    std::cout << "t  y_lin  y_nl\n";
    for (int t = 0; t <= N; ++t) {
        std::cout << t << "  " << y_lin[t] << "  " << y_nl[t] << "\n";
    }

    return 0;
}
