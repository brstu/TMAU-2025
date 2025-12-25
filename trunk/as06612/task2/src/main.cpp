#include <iostream>
#include <cmath>
#include "func.h"

using namespace std;

int main() {
    int time = 0;
    double inputtemperature = 0;
    double inputwarm = 0;

    cout << "Vvedite kolichestvo shagov modelirovaniya, nachalnuyu temperatury y0 i nachalnyy teplovoy vhod u0: ";
    cin >> time >> inputtemperature >> inputwarm;

    double prevtemperature = inputtemperature;
    double prevwarm = inputwarm;

    cout << "\nModel lineynoy modeli:\n";
    double y_linear = inputtemperature;
    for (int t = 1; t <= time; t++) {
        // Используйте правильные имена функций из func.h
        y_linear = computeLinearModel(y_linear, inputwarm);
        cout << "Shag " << t << ": y = " << y_linear << endl;
    }

    cout << "\nModel nelineynoy modeli:\n";
    double y_nl = inputtemperature;
    for (int t = 1; t <= time; t++) {
        // Используйте правильные имена функций из func.h
        double currentWarm = adjustWarmInput(inputwarm, t);
        double next = computeNonLinearModel(y_nl, prevtemperature, currentWarm, prevwarm);
        cout << "Shag " << t << ": y = " << next << endl;
        prevtemperature = y_nl;
        y_nl = next;
        prevwarm = currentWarm;
    }

    return 0;
}