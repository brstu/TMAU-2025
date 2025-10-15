#include <iostream>
#include <cmath>
#include <array>

using namespace std;

const int steps = 10; 
const double kA = 0.95;
const double kB = 0.02;
const double kC = 0.45;
const double kD = 0.15;
const double yStart = 18; 

double linearModel(double y, double u) {
    return kA * y + kB * u;
}

double nonlinearModel(double y, double yPrev, double u, double uPrev) {
    return kA * y + kB * pow(yPrev, 2) + kC * u + kD * sin(uPrev);
}

int main() {
    setlocale(LC_ALL, "RU");
    
    cout << "Линейная модель" << endl;
    cout << "y0 = " << yStart << endl;
    

    const array<double, steps> control = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
    
    double y = yStart, yPrev = yStart;
    for (int i = 0; i < steps; i++) {
        y = linearModel(y, control[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }
    
    cout << "\n";
    y = yPrev = yStart;
    
    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << yStart << endl;
    
    for (int i = 0; i < steps - 1; i++) {
        y = nonlinearModel(y, yPrev, control[i + 1], control[i]);
        cout << "y" << i + 1 << " = " << y << endl;
    }
    
    system("pause");
    return 0;
}
