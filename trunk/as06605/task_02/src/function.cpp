#include "function.h"
#include <vector>
#include <cmath>
#include <iostream> // добавим вывод для различия

using std::vector;

static double computeLinearStep(double prev, double u) {
    return a * prev + b * u;
}

static double computeNonlinearStep(double prev, double prev2, double u) {
    return a * prev - b * prev2 * prev2 + c * u + d * sin(u);
}

vector<double> linear(double u)
{
    vector<double> temps(iterations);
    temps.at(0) = InpTemp;
    for (int i = 0; i < iterations - 1; ++i) {
        temps.at(i + 1) = computeLinearStep(temps.at(i), u);
    }
    return temps;
}

vector<double> nonlinear(double u)
{
    vector<double> temps(iterations);
    temps.at(0) = InpTemp;

    // первая итерация отдельно
    temps.at(1) = computeNonlinearStep(temps.at(0), temps.at(0), u);

    for (int i = 1; i < iterations - 1; ++i) {
        temps.at(i + 1) = computeNonlinearStep(temps.at(i), temps.at(i - 1), u);
    }
    return temps;
}
