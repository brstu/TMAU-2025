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
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\as0xxyy\task_02\test.  
3. Исходный код программы – в каталоге: trunk\as0xxyy\task_02\src.  
4. В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).  Expand commentComment on line R27ResolvedCode has comments. Press enter to view.
5. Также отметить выполнение работы в общем [README.md](https://github.com/brstu/TMAU-2025/blob/main/README.md).

---

## Выполнение работы

### Тесты

```cpp
#include <gtest/gtest.h>
#include "model.h"

// -------------------------
// Тесты для linear_model
// -------------------------
TEST(LinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 0.0, 0.8, 0.2), 0.0);
}

TEST(LinearModelTest, StepInput) {
    // y=1, u=1, a=0.8, b=0.2 → 0.8*1 + 0.2*1 = 1.0
    EXPECT_DOUBLE_EQ(linear_model(1.0, 1.0, 0.8, 0.2), 1.0);
}

TEST(LinearModelTest, OnlyControl) {
    // y=0, u=2, a=0.8, b=0.2 → 0 + 0.4 = 0.4
    EXPECT_DOUBLE_EQ(linear_model(0.0, 2.0, 0.8, 0.2), 0.4);
}

// -------------------------
// Тесты для nonlinear_model
// -------------------------
TEST(NonlinearModelTest, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear_model(0.0, 0.0, 0.0, 0.0, 0.8, 0.2, 0.1, 0.05), 0.0);
}

TEST(NonlinearModelTest, StepInput) {
    // y=1, y_prev=1, u=1, u_prev=0
    // 0.8*1 - 0.2*1^2 + 0.1*1 + 0.05*sin(0) = 0.7
    EXPECT_NEAR(nonlinear_model(1.0, 1.0, 1.0, 0.0, 0.8, 0.2, 0.1, 0.05), 0.7, 1e-9);
}

TEST(NonlinearModelTest, WithPrevControl) {
    // y=0.5, y_prev=0.5, u=1, u_prev=1
    double result = nonlinear_model(0.5, 0.5, 1.0, 1.0, 0.8, 0.2, 0.1, 0.05);
    // 0.8*0.5 - 0.2*0.25 + 0.1*1 + 0.05*sin(1)
    double expected = 0.4 - 0.05 + 0.1 + 0.05*std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-9);
}

// -------------------------
// main для запуска тестов
// -------------------------
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

Test project C:\Users\Lenovo\Desktop\task_02\src\build> ./runTests.exe
[==========] Running 6 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 3 tests from LinearModelTest
[ RUN      ] LinearModelTest.ZeroInput
[       OK ] LinearModelTest.ZeroInput (0 ms)
[ RUN      ] LinearModelTest.StepInput
[       OK ] LinearModelTest.StepInput (0 ms)
[ RUN      ] LinearModelTest.OnlyControl
[       OK ] LinearModelTest.OnlyControl (0 ms)
[----------] 3 tests from LinearModelTest (28 ms total)

[----------] 3 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.ZeroInput
[       OK ] NonlinearModelTest.ZeroInput (0 ms)
[ RUN      ] NonlinearModelTest.StepInput
[       OK ] NonlinearModelTest.StepInput (0 ms)
[ RUN      ] NonlinearModelTest.WithPrevControl
[       OK ] NonlinearModelTest.WithPrevControl (0 ms)
[----------] 3 tests from NonlinearModelTest (38 ms total)

[----------] Global test environment tear-down
[==========] 6 tests from 2 test suites ran. (105 ms total)
[  PASSED  ] 6 tests.