#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class TemperatureModel {
private:
    double a;
    double b;
    double c;
    double d;
    double startTemp;
    vector<double> heatInput;

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double temp, const vector<double>& inputs)  // Передаём по константной ссылке
        : a(a_val),
          b(b_val),
          c(c_val),
          d(d_val),
          startTemp(temp),
          heatInput(inputs) {}

    void runLinear() {
        cout << "Linear model results:" << endl;
        double current = startTemp;
        
        for (int i = 0; i < heatInput.size(); i++) {
            current = a * current + b * heatInput[i];
            cout << "Y" << i + 1 << ": " << current << endl;
        }
    }

    void runNonlinear() {
        cout << "\nResults of the nonlinear model:" << endl;
        double prev = startTemp;
        double current = startTemp;
        
        for (int i = 0; i < heatInput.size(); i++) {
            double prevHeat = (i > 0) ? heatInput[i - 1] : 0;

            double next = a * current - b * prev + c * heatInput[i] + d * sin(prevHeat);
            cout << "Y" << i + 1 << ": " << next << endl;

            prev = current;
            current = next;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    vector<double> inputs = {3, 4, 5, 6, 7, 8, 9, 10, 9, 8};

    TemperatureModel model(0.7, 0.3, 0.05, 0.01, 20.0, inputs);
  
    model.runLinear();
    model.runNonlinear();
    
    return 0;
}
