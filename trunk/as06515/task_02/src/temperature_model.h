#pragma once
#include <vector>

class TemperatureModel {
private:
    double a;
    double b; 
    double c;
    double d;
    double startTemp;
    std::vector<double> heatInput;
    std::vector<double> linearResults;
    std::vector<double> nonlinearResults;
    bool verbose; 

public:
    TemperatureModel(double a_val, double b_val, double c_val, double d_val,
                    double temp, const std::vector<double>& inputs, bool verbose_mode = true);

    void runLinear();
    void runNonlinear();
    
    
    const std::vector<double>& getLinearResults() const { return linearResults; }
    const std::vector<double>& getNonlinearResults() const { return nonlinearResults; }
    void setVerbose(bool verbose_mode) { verbose = verbose_mode; }
};