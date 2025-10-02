#include <iostream>
#include <cmath>
using namespace std;

const double a = 0.6;
const double b = 0.3;
const double c = 0.8;
const double d = 0.5;

double linearmodel(double inputtemperature, double inputwarm) {
    return a * inputtemperature + b * inputwarm;
}

double nonlinearmodel(double inputtemperature, double prevtemperature, double inputwarm, double prevwarm) {
    return a * inputtemperature - b * pow(prevtemperature, 2) + c * inputwarm + d * sin(prevwarm);
}

int main() {
    int time;
    double inputtemperature;
    double inputwarm;

    cout << "Enter simulation time steps, initial temperature y0, and initial warm input u0: ";
    cin >> time >> inputtemperature >> inputwarm;

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
        prevwarm = inputwarm;
    }

    return 0;
}
