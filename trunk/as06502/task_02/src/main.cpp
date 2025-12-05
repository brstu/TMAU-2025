#include <iostream>
#include <cstdlib>
#include <vector>
#include "temperature_model.h"

using namespace std;

void systemPause() {
    #ifdef _WIN32
        system("pause");
    #else
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    #endif
}

void setConsoleEncoding() {
    #ifdef _WIN32
        system("chcp 6501 > nul");
    #endif
}

int main() {
    setConsoleEncoding();

    auto temperatureInitial = 20.0;

    vector<double> inputs = {15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0};

    cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        vector<double> linearResults(TemperatureModel::STEPS);
        TemperatureModel::calculateLinearModel(temperatureInitial, inputs, linearResults);
        
        for (auto t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t + 1 << "] = " << linearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в линейной модели: " << e.what() << endl;
        return 1;
    }

    cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        vector<double> nonlinearResults(TemperatureModel::STEPS);
        TemperatureModel::calculateNonlinearModel(temperatureInitial, inputs, nonlinearResults);
        
        for (auto t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t << "] = " << nonlinearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в нелинейной модели: " << e.what() << endl;
        return 1;
    }

    systemPause();
    return 0;
}