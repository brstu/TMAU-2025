#include <iostream>
#include <cmath>
using namespace std;

const double LINEAR_COEFF_A = 0.6;
const double LINEAR_COEFF_B = 0.3;
const double NONLINEAR_COEFF_C = 0.8;
const double NONLINEAR_COEFF_D = 0.5;

double linearmodel(double inputtemperature, double inputwarm) {
    return LINEAR_COEFF_A * inputtemperature + LINEAR_COEFF_B * inputwarm;
}

double nonlinearmodel(double inputtemperature, double prevtemperature, double inputwarm, double prevwarm) {
    return LINEAR_COEFF_A * inputtemperature - LINEAR_COEFF_B * pow(prevtemperature, 2) + NONLINEAR_COEFF_C * inputwarm + NONLINEAR_COEFF_D * sin(prevwarm);
}

int main() {
    int time;
    double inputtemperature;
    double inputwarm;

    cout << "Enter simulation time steps, initial temperature y0, and constant warm input u: ";
    cin >> time >> inputtemperature >> inputwarm;
    if (cin.fail()) {
        cerr << "Invalid input. Please enter an integer for time and two numbers for temperature and warm input." << endl;
        return 1;
    }

    double prevtemperature = inputtemperature; 
    double prevwarm = inputwarm;              

    cout << "\nLinear Model Simulation:\n";
    double y_linear = inputtemperature;
    for (int t = 1; t <= time; t++) {
        y_linear = linearmodel(y_linear, inputwarm);
        cout << "Step " << t << ": y = " << y_linear << endl;
    }

    cout << "\nNonlinear Model Simulation:\n";
    double y_nl = inputtemperature;
    for (int t = 1; t <= time; t++) {
        double next = nonlinearmodel(y_nl, prevtemperature, inputwarm, prevwarm);
        cout << "Step " << t << ": y = " << next << endl;
        prevtemperature = y_nl;
        y_nl = next;
    }

    return 0;
}
