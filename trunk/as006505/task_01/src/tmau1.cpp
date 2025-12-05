#include <iostream>
#include <cmath>

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev) {
    return params.a * y - params.b * (y_prev * y_prev) + params.c * u_prev + params.d * std::sin(u_prev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    
    NonlinearParams params{a, b, c, d};
    
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        double y_next = nextNonlinear(params, u_prev, y, y_prev);
        y_prev = y;
        y = y_next;
        u_prev = u; 
    }
}

int main() {
    double a1 = 0.3;
    double b1 = 0.3;
    double u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);
    std::cout << std::endl;

    double a2 = 0.1;
    double b2 = 0.2;
    double c2 = 0.4;
    double d2 = 0.2;
    double u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}