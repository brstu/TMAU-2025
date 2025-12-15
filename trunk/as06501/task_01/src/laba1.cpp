#include <iostream>
#include <cmath>
#include <iomanip>
#include <array>
#include <vector>

using namespace std;

const int SIZE = 8;  
const double COEFF_A = 0.85;      
const double COEFF_B = 0.05;       
const double COEFF_C = 0.35;       
const double COEFF_D = 0.12;      
const double INITIAL_VALUE = 10;  


const std::array<double, SIZE> INPUT_SIGNAL = { 
    1.5, 3.5, 2.8, 4.7, 3.9, 5.6, 2.5, 4.8 
};


double computeLinearModel(double previous_y, double current_u) {
    return COEFF_A * previous_y + COEFF_B * current_u;
}

double computeNonlinearModel(double y_current, double y_previous, 
                            double u_current, double u_previous) {
    double term1 = COEFF_A * y_current;
    double term2 = COEFF_B * y_previous * y_previous; 
    double term3 = COEFF_C * u_current;
    double term4 = COEFF_D * std::sin(u_previous);
    
    return term1 - term2 + term3 + term4;
}


void printHeader(const string& title) {
    cout << "\n" << string(40, '=') << endl;
    cout << title << endl;
    cout << string(40, '=') << endl;
}


void printStepResult(int step, double value) {
    cout << "Шаг " << step << ": y" << step << " = " << value << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(4);


    printHeader("ЛИНЕЙНАЯ МОДЕЛЬ (Модель 1)");
    cout << "Начальное значение y0 = " << INITIAL_VALUE << endl;
    
    double current_y = INITIAL_VALUE;
    for (int i = 0; i < SIZE; i++) {
        current_y = computeLinearModel(current_y, INPUT_SIGNAL[i]);
        printStepResult(i + 1, current_y);
    }


    printHeader("НЕЛИНЕЙНАЯ МОДЕЛЬ");
    cout << "Начальное значение y0 = " << INITIAL_VALUE << endl;
    
    std::vector<double> nonlinearResults;
    nonlinearResults.reserve(SIZE);
    nonlinearResults.push_back(INITIAL_VALUE);

    for (int i = 0; i < SIZE - 1; i++) {
    
        double previous_y = (i > 0) ? nonlinearResults[i - 1] : INITIAL_VALUE;
        
    
        double next_y = computeNonlinearModel(
            nonlinearResults[i],   
            previous_y,           
            INPUT_SIGNAL[i],      
            INPUT_SIGNAL[i]       
        );
        
        nonlinearResults.push_back(next_y);
        printStepResult(i + 1, next_y);
    }


    cout << "\n" << string(40, '=') << endl;
    cout << "АНАЛИЗ РЕЗУЛЬТАТОВ:" << endl;
    cout << "Количество шагов: " << SIZE << endl;
    cout << "Линейная модель - последнее значение: " << current_y << endl;
    cout << "Нелинейная модель - последнее значение: " 
         << nonlinearResults.back() << endl;
    
    cout << "\nДля выхода нажмите Enter...";
    cin.ignore();
    cin.get();
    
    return 0;
}
