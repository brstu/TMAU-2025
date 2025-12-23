#include "func.h"

namespace TemperatureModels {
    double computeLinearModel(double currentTemperature, double controlSignal) {
        using namespace ModelConstants;
        return LINEAR_A * currentTemperature + LINEAR_B * controlSignal;
    }
    
    double computeNonlinearModel(double currentTemperature,
                                 double previousTemperature,
                                 double currentControlSignal,
                                 double previousControlSignal) {
        using namespace ModelConstants;
        return NONLINEAR_A * currentTemperature 
               - NONLINEAR_B * std::pow(previousTemperature, 2) 
               + NONLINEAR_C * currentControlSignal 
               + NONLINEAR_D * std::sin(previousControlSignal);
    }
}