#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/module.h"

// Тесты для функции compute_linear
TEST(ComputeLinearTest, BasicCalculation) {
    int N = 3;
    double a = 0.5;
    double b = 1.0;
    std::vector<double> u = {1.0, 2.0, 3.0};
    std::vector<double> y_lin(N + 1, 0.0);
    y_lin[0] = 1.0;

    compute_linear(N, a, b, u, y_lin);

    // Проверяем вычисления: y[t+1] = a * y[t] + b * u[t]
    EXPECT_NEAR(y_lin[1], 1.5, 1e-10);   // 0.5*1.0 + 1.0*1.0
    EXPECT_NEAR(y_lin[2], 2.75, 1e-10);  // 0.5*1.5 + 1.0*2.0
    EXPECT_NEAR(y_lin[3], 4.375, 1e-10); // 0.5*2.75 + 1.0*3.0
}

TEST(ComputeLinearTest, SingleStep) {
    int N = 1;
    double a = 1.0;
    double b = 2.0;
    std::vector<double> u = {5.0};
    std::vector<double> y_lin(N + 1, 0.0);
    y_lin[0] = 10.0;

    compute_linear(N, a, b, u, y_lin);

    EXPECT_NEAR(y_lin[1], 20.0, 1e-10); // 1.0*10.0 + 2.0*5.0
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
// *НОВЫЙ ТЕСТ*
TEST(ComputeLinearTest, ZeroSteps) {
    int N = 0; // Проверяем случай, когда цикл не выполняется
    double a = 1.0;
    double b = 1.0;
    std::vector<double> u = {};
    std::vector<double> y_lin(1, 10.0); // y[0] = 10.0

    compute_linear(N, a, b, u, y_lin);
    
    // y_lin[0] не должно измениться, других элементов нет
    EXPECT_NEAR(y_lin[0], 10.0, 1e-10);
    EXPECT_EQ(y_lin.size(), 1); // Размер остался N+1=1
}


TEST(ComputeNonLinearTest, SingleStepN2) {
    int N = 2; 
    double a = 1.0;
    double b = 1.0;
    double c = 1.0;
    double d = 1.0;
    std::vector<double> u = {1.0, 2.0}; 
    std::vector<double> y_nl(N + 1, 0.0);
    y_nl[0] = 5.0; 
    y_nl[1] = 10.0; 

    compute_nonlinear(N, a, b, c, d, u, y_nl);

    EXPECT_NEAR(y_nl[2], -12.15852902, 1e-8);
}

TEST(ComputeNonLinearTest, ZeroOrOneSteps) {

    int N = 1; 
    double a = 1.0;
    double b = 1.0;
    double c = 1.0;
    double d = 1.0;
    std::vector<double> u = {1.0};
    std::vector<double> y_nl(N + 1, 0.0);
    y_nl[0] = 5.0; 
    y_nl[1] = 10.0; 

    compute_nonlinear(N, a, b, c, d, u, y_nl);

    EXPECT_NEAR(y_nl[0], 5.0, 1e-10);
    EXPECT_NEAR(y_nl[1], 10.0, 1e-10);
}