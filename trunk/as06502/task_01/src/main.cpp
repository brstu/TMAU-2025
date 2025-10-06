#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

namespace Constants {
    const double A = 0.2;
    const double B = 0.02;
    const double C = 0.03;
    const double D = 0.04;
}

double calcLinear(double currentY, double inputU) {
    return (Constants::A * currentY) + (Constants::B * inputU);
}

double calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    return (Constants::A * currentY) - (Constants::B * prevY * prevY) + (Constants::C * inputU) + Constants::D * sin(prevU);
}

int main() {
    setlocale(LC_ALL, "RU");

    double temperatureInitial = 20.0;

    vector<double> inputs = {
        15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0
    };

    cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double prevTemperature = temperatureInitial;

    for (int t = 0; t < inputs.size(); ++t) {
        double newTemperature = calcLinear(prevTemperature, inputs[t]);
        cout << "y[" << t + 1 << "] = " << newTemperature << endl;
        prevTemperature = newTemperature;
    }

    cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double currentY = temperatureInitial;
    double previousY = temperatureInitial;

    for (int t = 1; t < inputs.size(); ++t) {
        double uCurr = inputs[t];
        double uPrev = inputs[t-1];

        double newY = calcNonlinear(currentY, previousY, uCurr, uPrev);
        cout << "y[" << t << "] = " << newY << endl;

        previousY = currentY;
        currentY = newY;
    }

    system("pause");
    return 0;
}