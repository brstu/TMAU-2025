<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Батулин М.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования – [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.  
3. Исходный код программы – в каталоге: **trunk\as0xxyy\task_02\src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).  
5. Также отметить выполнение работы в общем [`README.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md).

---

## Выполнение работы

### Сборка и запуск

#### Сборка программы
```bash
cd src
mkdir build
cd build
cmake ..
make
./Modeling_as06602
```

#### Сборка и запуск тестов
```bash
cd test
mkdir build
cd build
cmake ..
make
./ModelTests
```

### Тесты

```cpp
#include <gtest/gtest.h>
#include "model.h"
#include <cmath>

TEST(LinearModelTest, BasicCalculation) {
    const double A = 0.8;
    const double B = 0.1;
    const double Y_T = 20.0;
    const double U_T = 5.0;
    double expected = A * Y_T + B * U_T;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), expected);
}

TEST(LinearModelTest, ZeroValues) {
    const double A = 0.0;
    const double B = 0.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), 0.0);
}

TEST(LinearModelTest, NegativeValues) {
    const double A = -0.5;
    const double B = -0.2;
    const double Y_T = -10.0;
    const double U_T = -3.0;
    double expected = A * Y_T + B * U_T;
    EXPECT_DOUBLE_EQ(linearModel(A, B, Y_T, U_T), expected);
}

TEST(NonlinearModelTest, BasicCalculation) {
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y_T = 20.0;
    const double U_T = 5.0;
    const double U_PREV = 4.0;
    double expected = A * Y_T - B_NL * Y_T * Y_T + C * U_T + D * sin(U_PREV);
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), expected);
}

TEST(NonlinearModelTest, ZeroValues) {
    const double A = 0.0;
    const double B_NL = 0.0;
    const double C = 0.0;
    const double D = 0.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    const double U_PREV = 0.0;
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), 0.0);
}

TEST(NonlinearModelTest, SinZero) {
    const double A = 1.0;
    const double B_NL = 0.0;
    const double C = 0.0;
    const double D = 1.0;
    const double Y_T = 0.0;
    const double U_T = 0.0;
    const double U_PREV = 0.0;
    EXPECT_DOUBLE_EQ(nonlinearModel(A, B_NL, C, D, Y_T, U_T, U_PREV), 0.0);
}

TEST(SimulateLinearTest, SingleStep) {
    const int N = 1;
    const double A = 0.8;
    const double B = 0.1;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], linearModel(A, B, Y0, U0));
}

TEST(SimulateLinearTest, MultipleSteps) {
    const int N = 3;
    const double A = 0.5;
    const double B = 0.2;
    const double Y0 = 10.0;
    const double U0 = 2.0;
    auto result = simulateLinear(N, A, B, Y0, U0);
    ASSERT_EQ(result.size(), 4);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], linearModel(A, B, result[t-1], U0));
    }
}

TEST(SimulateNonlinearTest, SingleStep) {
    const int N = 1;
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    EXPECT_DOUBLE_EQ(result[1], nonlinearModel(A, B_NL, C, D, Y0, U0, U0));
}

TEST(SimulateNonlinearTest, MultipleSteps) {
    const int N = 2;
    const double A = 0.8;
    const double B_NL = 0.12;
    const double C = 0.05;
    const double D = 0.02;
    const double Y0 = 20.0;
    const double U0 = 5.0;
    auto result = simulateNonlinear(N, A, B_NL, C, D, Y0, U0);
    ASSERT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[0], Y0);
    for (int t = 1; t <= N; t++) {
        EXPECT_DOUBLE_EQ(result[t], nonlinearModel(A, B_NL, C, D, result[t-1], U0, U0));
    }
}
```

Test project /Users/motorolla/trash/mihail_pornohub/TMAU-2025/trunk/as06602/task_02/test/build
    Start 1: LinearModelTest.BasicCalculation
1/10 Test #1: LinearModelTest.BasicCalculation ...   Passed    0.00 sec
    Start 2: LinearModelTest.ZeroValues
2/10 Test #2: LinearModelTest.ZeroValues .........   Passed    0.00 sec
    Start 3: LinearModelTest.NegativeValues
3/10 Test #3: LinearModelTest.NegativeValues ......   Passed    0.00 sec
    Start 4: NonlinearModelTest.BasicCalculation
4/10 Test #4: NonlinearModelTest.BasicCalculation    Passed    0.00 sec
    Start 5: NonlinearModelTest.ZeroValues
5/10 Test #5: NonlinearModelTest.ZeroValues ........   Passed    0.00 sec
    Start 6: NonlinearModelTest.SinZero
6/10 Test #6: NonlinearModelTest.SinZero ...........   Passed    0.00 sec
    Start 7: SimulateLinearTest.SingleStep
7/10 Test #7: SimulateLinearTest.SingleStep ........   Passed    0.00 sec
    Start 8: SimulateLinearTest.MultipleSteps
8/10 Test #8: SimulateLinearTest.MultipleSteps .....   Passed    0.00 sec
    Start 9: SimulateNonlinearTest.SingleStep
9/10 Test #9: SimulateNonlinearTest.SingleStep ......   Passed    0.00 sec
    Start 10: SimulateNonlinearTest.MultipleSteps
10/10 Test #10: SimulateNonlinearTest.MultipleSteps ...   Passed    0.00 sec

100% tests passed, 0 tests failed out of 10

Total Test time (real) = 0.01 sec

### Покрытие кода

Для генерации отчета о покрытии кода использовался инструмент gcovr.

```bash
gcovr -r . --html --html-details -o coverage.html
```

Отчет о покрытии:

```
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/model.cpp                                45      45   100%   
------------------------------------------------------------------------------
TOTAL                                        45      45   100%
------------------------------------------------------------------------------
```

Процент покрытия кода тестами: 100%
```