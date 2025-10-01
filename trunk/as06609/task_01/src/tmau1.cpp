#include <iostream>
#include <cmath>
using namespace std;

const int N = 10;
const double COEFF_A = 0.7;
const double COEFF_B = 0.05;
const double COEFF_C = 0.3;
const double COEFF_D = 0.2;
double INITIAL_VALUE = 15;

double linearModel(double currentY, double inputU) {
    return COEFF_A * currentY + COEFF_B * inputU;
}

double nonlinearModel(double currentY, double previousY, double currentU, double previousU) {
    return COEFF_A * currentY - COEFF_B * pow(previousY, 2) + COEFF_C * currentU + COEFF_D * sin(previousU);
}

int main() {
    setlocale(LC_ALL, "RU");

    cout << "=== Линейная модель ===" << endl;
    cout << "Начальное значение y0 = " << INITIAL_VALUE << endl;

    double inputSequence[10] = { 12, 9, 14, 11, 13, 10, 8, 15, 12, 11 };
    double currentY = INITIAL_VALUE;
    double previousY = INITIAL_VALUE;

    // Линейная модель
    for (int step = 0; step < N; step++) {
        currentY = linearModel(currentY, inputSequence[step]);
        cout << "y" << step + 1 << " = " << currentY << endl;
    }

    cout << "\n=== Нелинейная модель ===" << endl;
    cout << "Начальное значение y0 = " << INITIAL_VALUE << endl;

    // Сбрасываем значения для нелинейной модели
    previousY = INITIAL_VALUE;
    currentY = INITIAL_VALUE;

    // Нелинейная модель
    for (int step = 0; step < N - 1; step++) {
        double temporaryY = currentY;
        currentY = nonlinearModel(currentY, previousY, inputSequence[step + 1], inputSequence[step]);
        previousY = temporaryY;
        cout << "y" << step + 1 << " = " << currentY << endl;
    }

    cout << "Нажмите Enter для завершения...";
    cin.get();
    return 0;
}