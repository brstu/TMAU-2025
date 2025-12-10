#include <iostream>
#include <vector>
#include "func.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main() {

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    vector<double> input;
    input.reserve(STEPS);
    for (int i = 0; i < STEPS; ++i) {
        switch (i % 3) {
            case 0: input.push_back(5); break;
            case 1: input.push_back(7); break;
            default: input.push_back(0); break;
        }
    }

    simulateLinear(input);
    simulateNonlinear(input);

    return 0;
}
