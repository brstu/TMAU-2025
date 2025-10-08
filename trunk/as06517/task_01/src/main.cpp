#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

float linear_model(float y_prev, float u_tau, float a, float b) {
    float y_next = a * y_prev + b * u_tau;
    return y_next;
}

float nonlinear_model(float y_prev, float y_prev_2, float u_prev, 
                     float u_tau, float a, float b, float c, float d) {
    float y_next = a * y_prev - b * pow(y_prev_2, 2) + c * u_tau + d * sin(u_prev);
    return y_next;
}

int main() {
    const float a = 0.8, b = 0.2, c = 0.25, d = 0.1;
    float u_prev = 0, u_tau;
    int n;
    float y_prev = 20, y_prev_2 = 20;
    
    vector<float> u_vec;
    vector<float> linear_result;
    vector<float> nonlinear_result;

    cout << "=== Temperature Control Object Simulation ===" << endl;
    cout << "Linear model: y_{τ+1} = a*y_τ + b*u_τ" << endl;
    cout << "Nonlinear model: y_{τ+1} = a*y_τ - b*y_{τ-1}² + c*u_τ + d*sin(u_{τ-1})" << endl;
    cout << "Parameters: a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << endl;
    cout << "Initial temperature: " << y_prev << "°C" << endl << endl;

    cout << "Enter number of steps: ";
    cin >> n;
    cout << "Enter control inputs u(τ) separated by spaces:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> u_tau;
        u_vec.push_back(u_tau);
    }

    float y_prev_linear = y_prev;
    float y_prev_nonlinear = y_prev;

    cout << endl << "Simulation Results:" << endl;
    cout << string(60, '-') << endl;
    cout << setw(5) << "Step" << setw(10) << "u(τ)" 
         << setw(20) << "Linear Model" << setw(20) << "Nonlinear Model" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < n; i++) {
        u_tau = u_vec[i];

        float linear_temp = linear_model(y_prev_linear, u_tau, a, b);
        float nonlinear_temp = nonlinear_model(y_prev_nonlinear, y_prev_2,
                                            u_prev, u_tau, a, b, c, d);
        
        linear_result.push_back(linear_temp);
        nonlinear_result.push_back(nonlinear_temp);

        cout << setw(5) << i + 1 
             << setw(10) << fixed << setprecision(2) << u_tau
             << setw(20) << fixed << setprecision(3) << linear_temp
             << setw(20) << fixed << setprecision(3) << nonlinear_temp 
             << endl;

        y_prev_linear = linear_temp;
        y_prev_2 = y_prev_nonlinear;
        y_prev_nonlinear = nonlinear_temp;
        u_prev = u_tau;
    }
    cout << string(60, '-') << endl;
    cin.get();

    return 0;
}