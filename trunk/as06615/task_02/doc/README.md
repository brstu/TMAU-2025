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
<p align="right">Неруш Е. С.</p>
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

### Тесты

```cpp
#include <gtest/gtest.h>
#include <vector>
#include "../src/model.h"

// -------------------------
// Тесты для compute_derivative
// -------------------------

TEST(DerivativeTest, EmptyErrors) {
    std::vector<double> errors;
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.1), 0.0);
}

TEST(DerivativeTest, SingleErrorValue) {
    std::vector<double> errors = {1.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.1), 0.0);
}

TEST(DerivativeTest, ZeroDeltaTime) {
    std::vector<double> errors = {1.0, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.0), 0.0);
}

TEST(DerivativeTest, PositiveDerivative) {
    std::vector<double> errors = {1.0, 2.5};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.5), 3.0);
}

TEST(DerivativeTest, NegativeDerivative) {
    std::vector<double> errors = {2.0, 1.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 1.0), -1.0);
}

TEST(DerivativeTest, ConstantError) {
    std::vector<double> errors = {2.0, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 1.0), 0.0);
}

TEST(DerivativeTest, SmallDeltaTime) {
    std::vector<double> errors = {1.0, 1.5};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.0001), 5000.0);
}

TEST(DerivativeTest, LongErrorSequence) {
    std::vector<double> errors = {0.0, 0.5, 1.0, 1.5, 2.0};
    EXPECT_DOUBLE_EQ(compute_derivative(errors, 0.5), 1.0);
}

TEST(DerivativeTest, NearZeroDeltaTime) {
    std::vector<double> errors = {1.0, 2.0};
    double dt = std::numeric_limits<double>::epsilon() / 2;
    EXPECT_DOUBLE_EQ(compute_derivative(errors, dt), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

```bash
$ ./runTests.exe
[==========] Running 9 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 9 tests from DerivativeTest
[ RUN      ] DerivativeTest.EmptyErrors
[       OK ] DerivativeTest.EmptyErrors (0 ms)
[ RUN      ] DerivativeTest.SingleErrorValue
[       OK ] DerivativeTest.SingleErrorValue (0 ms)
[ RUN      ] DerivativeTest.ZeroDeltaTime
[       OK ] DerivativeTest.ZeroDeltaTime (0 ms)
[ RUN      ] DerivativeTest.PositiveDerivative
[       OK ] DerivativeTest.PositiveDerivative (0 ms)
[ RUN      ] DerivativeTest.NegativeDerivative
[       OK ] DerivativeTest.NegativeDerivative (0 ms)
[ RUN      ] DerivativeTest.ConstantError
[       OK ] DerivativeTest.ConstantError (0 ms)
[ RUN      ] DerivativeTest.SmallDeltaTime
[       OK ] DerivativeTest.SmallDeltaTime (0 ms)
[ RUN      ] DerivativeTest.LongErrorSequence
[       OK ] DerivativeTest.LongErrorSequence (0 ms)
[ RUN      ] DerivativeTest.NearZeroDeltaTime
[       OK ] DerivativeTest.NearZeroDeltaTime (0 ms)
[----------] 9 tests from DerivativeTest (69 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 1 test suite ran. (89 ms total)
[  PASSED  ] 9 tests.