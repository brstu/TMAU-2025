#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

struct Lin {
    double a;
    double b;
};

struct Nonlin {
    double a;
    double b;
    double c;
    double d;
};

double step_lin(double y, double u, const Lin& p) {
    return p.a * y + p.b * u;
}

double step_nonlin(double y1, double y2, double u1, double u2, const Nonlin& p) {
    double nonlinear_term = p.b * (y2 * y2);
    return p.a * y1 - nonlinear_term + p.c * u1 + p.d * std::sin(u2);
}

void simulate(int N) {
    Lin lp{0.80, 0.22};
    Nonlin np{0.76, 0.18, 0.09, 0.14};

    std::vector<double> u(N, 1.0);
    std::vector<double> yL(N, 0.0);
    std::vector<double> yN(N, 0.0);

    for (int t = 1; t < N; ++t) {
        yL[t] = step_lin(yL[t - 1], u[t - 1], lp);

        if (t == 1) {
            Lin tmp{np.a, np.c};
            yN[t] = step_lin(yN[t - 1], u[t - 1], tmp);
        } else {
            yN[t] = step_nonlin(yN[t - 1], yN[t - 2], u[t - 1], u[t - 2], np);
        }
    }

    std::cout << std::fixed;
    std::cout << "t       linear          nonlinear\n";
    std::cout << "----------------------------------\n";

    for (int t = 0; t < N; ++t) {
        std::cout << t << "\t" <<  yL[t] << "\t" << yN[t] << "\n";
    }
}

int main() {
    simulate(20);
    return 0;
}
