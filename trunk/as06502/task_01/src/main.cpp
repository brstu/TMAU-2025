#include <iostream>
#include <cmath>
using namespace std;

struct Constants{
const double A = 0.2;
const double B = 0.02;
const double C = 0.03;
const double D = 0.04;
};

double calcLinear(double currentY, double inputU) {
    Constants c = Constants();
    return (c.A * currentY) + (c.B * inputU);
}

double calcNonlinear(double currentY, double prevY, double inputU, double prevU) {
    Constants c = Constants();
    return (c.A * currentY) - (c.B * prevY * prevY) + (c.C * inputU) + c.D * sin(prevU);
}

int main() {
    setlocale(LC_ALL, "RU");

    const int STEPS = 10;
    double temperatureInitial = 20.0;
    const Constants c = Constants();

    double inputs[STEPS] = {
        15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0
    };

    cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double prevTemperature = temperatureInitial;

    for (int t = 0; t < STEPS; ++t) {
        double newTemperature = calcLinear(prevTemperature, inputs[t]);
        cout << "y[" << t + 1 << "] = " << newTemperature << endl;
        prevTemperature = newTemperature;
    }

    cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    double currentY = temperatureInitial;
    double previousY = temperatureInitial;

    for (int t = 1; t < STEPS; ++t) {
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
//pls claim it