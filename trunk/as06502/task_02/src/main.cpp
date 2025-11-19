#include <iostream>
#include <cstdlib>
#include "temperature_model.h"

using namespace std;

// для винды и с wsl
void systemPause() {
    #ifdef _WIN32
        system("pause");
    #else
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    #endif
}

// та же шляпа что и прошлое
void setConsoleEncoding() {
    #ifdef _WIN32
        system("chcp 6501 > nul");
    #endif
}

int main() {
    setConsoleEncoding();

    double temperatureInitial = 20.0;

    double inputs[TemperatureModel::STEPS] = {
        15.0, 16.5, 18.0, 20.0, 22.5, 25.0, 24.0, 21.0, 18.0, 16.0
    };

    cout << "Линейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        double linearResults[TemperatureModel::STEPS];
        TemperatureModel::calculateLinearModel(temperatureInitial, inputs, TemperatureModel::STEPS, linearResults);
        
        for (int t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t + 1 << "] = " << linearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в линейной модели: " << e.what() << endl;
        return 1;
    }

    cout << "\nНелинейная модель\nНачальное значение: " << temperatureInitial << "\n";

    try {
        double nonlinearResults[TemperatureModel::STEPS];
        TemperatureModel::calculateNonlinearModel(temperatureInitial, inputs, TemperatureModel::STEPS, nonlinearResults);
        
        for (int t = 0; t < TemperatureModel::STEPS; ++t) {
            cout << "y[" << t << "] = " << nonlinearResults[t] << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка в нелинейной модели: " << e.what() << endl;
        return 1;
    }

    systemPause();
    return 0;
}