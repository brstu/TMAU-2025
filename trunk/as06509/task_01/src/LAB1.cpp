#include <iostream>
#include <vector>
#include <cmath> 

using namespace std;

int n = 10;  

float a = 1.2;
float b = 0.01;
float c = 0.75;
float d = 0.03;

vector<float> u(n + 1, 4.0);

void linear() {
    vector<float> y(n + 1, 0.0); 
    y[0] = 25;

    for (int t = 0; t < n; ++t) {
        y[t + 1] = a * y[t] + b * u[t];
    }

    cout << "Linear:\n";
    for (int t = 0; t <= n; ++t) {
        cout << "y" << t << ": " << y[t] << endl;
    }
}

void Nonlinear() {
    vector<float> y(n + 1, 0.0); 
    y[0] = 25;
    y[1] = y[0];

    for (int t = 1; t < n; ++t) {
        y[t + 1] = a * y[t] - b * pow(y[t - 1], 2) + c * u[t] + d * sin(u[t - 1]);
    }


    cout << "\nNonlinear:\n";
    for (int t = 0; t <= n; ++t) {
        cout << "y" << t << ": " << y[t] << endl;
    }
}

int main() {
    linear();
    Nonlinear();

    return 0;
}
