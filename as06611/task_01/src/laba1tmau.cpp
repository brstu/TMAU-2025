#include <iostream>
#include <cmath>

using namespace std;

const int STEPS = 12;         // количество шагов моделирования
const double ALPHA = 0.92;    // коэффициент для линейной части
const double BETA = 0.02;     // коэффициент для входного сигнала
const double GAMMA = 0.40;    // коэффициент при u[k] в нелинейной модели
const double DELTA = 0.10;    // коэффициент при sin(u[k-1])
double Y0 = 18.5;             // начальное значение температуры

double calcLinear(double y, double u) {
    return ALPHA * y + BETA * u;
}

double calcNonlinear(double y_now, double y_prev, double u_now, double u_prev) {
    return ALPHA * y_now - BETA * (y_prev * y_prev) + GAMMA * u_now + DELTA * sin(u_prev);
}

int main() {
    setlocale(LC_ALL, "Russian");

    double U[STEPS] = { 3, 5, 6, 4, 5, 7, 3, 6, 5, 4, 6, 5 };

    cout << "=== Линейная модель ===" << endl;
    cout << "y0 = " << Y0 << endl;

    double y_lin = Y0;
    for (int k = 0; k < STEPS; k++) {
        y_lin = calcLinear(y_lin, U[k]);
        cout << "y" << k + 1 << " = " << y_lin << endl;
    }

    cout << "\n=== Нелинейная модель ===" << endl;
    cout << "y0 = " << Y0 << endl;

    double y_prev = Y0;
    double y_now = Y0;

    for (int k = 0; k < STEPS - 1; k++) {
        double y_next = calcNonlinear(y_now, y_prev, U[k + 1], U[k]);
        cout << "y" << k + 1 << " = " << y_next << endl;
        y_prev = y_now;
        y_now = y_next;
    }

    return 0;
}
