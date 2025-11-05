#include <iostream>
#include <vector>
#include <cmath>
#include "model.h"

using namespace std;

int main() {
    NonlinearParams params{0.8, 0.2, 0.1, 0.05};
    int N = 20;

    vector<double> y(N + 1, 0.0);
    vector<double> u(N + 1, 0.0);

    // формируем управление
    for (int t = 0; t <= N; t++) {
        u[t] = (t < 5) ? 0.0 : 1.0;
    }

    cout << "linear model" << endl;
    for (int t = 0; t < N; t++) {
        y[t + 1] = linear_model(y[t], u[t], params.a, params.b);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    fill(y.begin(), y.end(), 0.0);

    cout << "\nnonlinear model" << endl;
    for (int t = 1; t < N; t++) {
        State s{y[t], y[t - 1], u[t], u[t - 1]};
        y[t + 1] = nonlinear_model(s, params);
        cout << "t=" << t + 1 << "  y=" << y[t + 1] << endl;
    }

    return 0;
}