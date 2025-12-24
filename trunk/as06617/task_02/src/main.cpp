#include <iostream>
#include <vector>
#include "func.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;
using namespace model_params;   // 👈 ВАЖНО

static void simulateLinear(const vector<double>& input) {
    double y = INITIAL_Y;
    cout << "=== Линейная модель ===\n";
    cout << "y0 = " << INITIAL_Y << '\n';

    for (int i = 0; i < STEPS_COUNT; ++i) {
        y = linear(y, input[i]);
        cout << "Шаг " << i + 1 << ": y = " << y << '\n';
    }
}

static void simulateNonlinear(const vector<double>& input) {
    double y = INITIAL_Y;
    double y_prev = INITIAL_Y;

    cout << "\n=== Нелинейная модель ===\n";
    cout << "y0 = " << INITIAL_Y << '\n';

    for (int i = 0; i < STEPS_COUNT; ++i) {
        double u_prev = (i == 0) ? input[0] : input[i - 1];
        double y_old = y;

        y = nonlinear(y, y_prev, input[i], u_prev);

        cout << "Шаг " << i + 1 << ": y = " << y << '\n';
        y_prev = y_old;
    }
}

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    vector<double> input;
    input.reserve(STEPS_COUNT);

    for (int i = 0; i < STEPS_COUNT; ++i) {
        switch (i % 3) {
            case 0: input.push_back(5); break;
            case 1: input.push_back(7); break;
            default: input.push_back(0); break;
        }
    }

    simulateLinear(input);
    simulateNonlinear(input);

    return 0;
}
