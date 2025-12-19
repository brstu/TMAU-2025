// main.cpp
#include "temperature_model.h"
#include <iostream>

int main() {
    int total_steps = 30;

    LinearParams lin_params{0.8, 0.15};
    NonlinearParams nonlin_params{0.8, 0.15, 0.05, 0.1};

    run_simulation(total_steps, lin_params, nonlin_params);

    return 0;
}
