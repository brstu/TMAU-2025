
<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Осовец М.М.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.

# Выполнение работы
## models.h  
```
#ifndef MODELS_H
#define MODELS_H

double linear_model(double y, double u, double a, double b);
double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
                       double a, double b, double c, double d);

#endif

```


## models.cpp
```
#include "models.h"
#include <cmath>

double linear_model(double y, double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev,
                       double a, double b, double c, double d) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}

```

## main.cpp
```
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double linear_model(double y,double u, double a, double b) {
    return a * y + b * u;
}

double nonlinear_model(double y_t, double y_prev, double u_t, double u_prev, double a, double b, double c, double d) {
    return a * y_t - b * y_prev * y_prev + c * u_t + d * sin(u_prev);
}

int main() {
    int n = 30;
    double a = 0.8, b = 0.15, c = 0.05, d = 0.1;

    std::vector<double> u(n, 1.0);
    std::vector<double> y_lin(n, 0.0);
    std::vector<double> y_nonlin(n, 0.0);

    y_lin[0] = 0.0;
    y_nonlin[0] = 0.0;

    for (int t = 1; t < n; ++t) {
        y_lin[t] = linear_model(y_lin[t-1], u[t-1], a, b);

        if (t > 1) {
            y_nonlin[t] = nonlinear_model(y_nonlin[t-1], y_nonlin[t-2], u[t-1], u[t-2], a, b, c, d);
        } else {
            y_nonlin[t] = linear_model(y_nonlin[t-1], u[t-1], a, b);
        }
    }

    std::cout << "\nTime\tLinear\t\tNonlinear\n";
    std::cout << "----\t------\t\t---------\n";
    for (int t = 0; t < n; ++t) {
        std::cout << t << "\t" << std::fixed << std::setprecision(5)
                  << y_lin[t] << "\t\t" << y_nonlin[t] << "\n";
    }

    return 0;
}


```
## CMakeLists.txt
```
cmake_minimum_required(VERSION 3.5)

project(tasl_02)

add_executable(task_02 main.cpp)
```

## test_models.cpp
```
#include <gtest/gtest.h>
#include "models.h"
#include <cmath>

TEST(LinearModelTest, ZeroInputs) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.15), 0.0);
}

TEST(LinearModelTest, BasicCase) {
    double result = linear_model(1.0, 1.0, 0.8, 0.15);
    EXPECT_NEAR(result, 0.95, 1e-9);
}

TEST(LinearModelTest, NegativeValues) {
    double result = linear_model(-2.0, -3.0, 0.8, 0.15);
    EXPECT_NEAR(result, -1.6 - 0.45, 1e-9);
}

TEST(NonlinearModelTest, ZeroInputs) {
    double result = nonlinear_model(0.0, 0.0, 0.0, 0.0,
                                    0.8, 0.15, 0.05, 0.1);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST(NonlinearModelTest, BasicCase) {
    double r = nonlinear_model(1.0, 1.0, 1.0, 1.0,
                               0.8, 0.15, 0.05, 0.1);
    double expected = 0.8 - 0.15 + 0.05 + 0.1 * sin(1.0);
    EXPECT_NEAR(r, expected, 1e-9);
}

TEST(NonlinearModelTest, NonlinearEffect) {
    double r1 = nonlinear_model(1.0, 1.0, 0.0, 0.0, 0.8, 0.15, 0.05, 0.1);
    double r2 = nonlinear_model(1.0, 2.0, 0.0, 0.0, 0.8, 0.15, 0.05, 0.1);
    EXPECT_LT(r2, r1); // из-за -b*y_prev^2
}

```

## CMakeLists.txt
```
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_models test_models.cpp ../src/models.cpp)
target_link_libraries(test_models GTest::GTest GTest::Main)

add_test(NAME ModelTests COMMAND test_models)
```

# Вывод тестов программы
```
./test/test_models
Running main() from /usr/src/debug/gtest/googletest-1.17.0/googletest/src/gtest_main.cc
[==========] Running 6 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.ZeroInputs
[       OK ] LinearModelTest.ZeroInputs (0 ms)
[ RUN      ] LinearModelTest.BasicCase
[       OK ] LinearModelTest.BasicCase (0 ms)
[ RUN      ] LinearModelTest.NegativeValues
[       OK ] LinearModelTest.NegativeValues (0 ms)
[----------] 3 tests from LinearModelTest (0 ms total)

[----------] 3 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.ZeroInputs
[       OK ] NonlinearModelTest.ZeroInputs (0 ms)
[ RUN      ] NonlinearModelTest.BasicCase
[       OK ] NonlinearModelTest.BasicCase (0 ms)
[ RUN      ] NonlinearModelTest.NonlinearEffect
[       OK ] NonlinearModelTest.NonlinearEffect (0 ms)
[----------] 3 tests from NonlinearModelTest (0 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 6 tests.
```

**Вывод:** В ходе данной лабораторной работы были усвоены и опробованы инструменты модульного тестирования googletest, а также инструменты анализа покрытия тестов gcovr.
