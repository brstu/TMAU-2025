#include <iostream>
#include <vector>
#include "func.h"

using namespace std;

static void simulateLinear(const vector<double>& input) {
    double y = Y0;
    cout << "=== Линейная модель ===\n";
    cout << "y0 = " << Y0 << '\n';
    for (int i = 0; i < STEPS; ++i) {
        y = linear(y, input[i]);
        cout << "Шаг " << i + 1 << ": y = " << y << '\n';
    }
}

static void simulateNonlinear(const vector<double>& input) {
    double y = Y0;
    double y_prev = Y0;
    cout << "\n=== Нелинейная модель ===\n";
    cout << "y0 = " << Y0 << '\n';
    for (int i = 0; i < STEPS; ++i) {
        double u_prev = (i == 0) ? input[0] : input[i - 1];
        y = nonlinear(y, y_prev, input[i], u_prev);
        cout << "Шаг " << i + 1 << ": y = " << y << '\n';
        y_prev = y;
    }
}

int main() {
    vector<double> input;
    input.reserve(STEPS);
    for (int i = 0; i < STEPS; ++i) {
        switch (i % 3) {
            case 0: input.push_back(5); break;
            case 1: input.push_back(7); break;
            default: input.push_back(6); break; 
        }
    }

    simulateLinear(input);
    simulateNonlinear(input);
    return 0;
}

