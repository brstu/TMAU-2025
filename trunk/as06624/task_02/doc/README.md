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
<p align="right">Янчук А.Ю.</p>
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
4. В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).
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
    EXPECT_DOUBLE_EQ(linear_model(1.0, 1.0, 0.8, 0.2), 1.0);
}

TEST(LinearModelTest, OnlyControl) {
    EXPECT_DOUBLE_EQ(linear_model(0.0, 2.0, 0.8, 0.2), 0.4);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear_model(-1.0, -1.0, 0.8, 0.2), -1.0);
}

// -------------------------
// Тесты для nonlinear_model
// -------------------------
TEST(NonlinearModelTest, ZeroInput) {
    State s{0.0, 0.0, 0.0, 0.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    EXPECT_DOUBLE_EQ(nonlinear_model(s, p), 0.0);
}

TEST(NonlinearModelTest, StepInput) {
    State s{1.0, 1.0, 1.0, 0.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    EXPECT_NEAR(nonlinear_model(s, p), 0.7, 1e-9);
}

TEST(NonlinearModelTest, WithPrevControl) {
    State s{0.5, 0.5, 1.0, 1.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    double expected = 0.8*0.5 - 0.2*0.25 + 0.1*1.0 + 0.05*std::sin(1.0);
    EXPECT_NEAR(nonlinear_model(s, p), expected, 1e-9);
}

TEST(NonlinearModelTest, NegativeInputs) {
    State s{-1.0, -1.0, -1.0, -1.0};
    NonlinearParams p{0.8, 0.2, 0.1, 0.05};
    double expected = 0.8*(-1.0) - 0.2*1.0 + 0.1*(-1.0) + 0.05*std::sin(-1.0);
    EXPECT_NEAR(nonlinear_model(s, p), expected, 1e-9);
}

// -------------------------
// main для запуска тестов
// -------------------------
> **Примечание:**  
> В данном проекте функция `main` для запуска тестов не требуется, так как она предоставляется автоматически при линковке с `GTest::gtest_main` (см. строку 21 в `CMakeLists.txt`).  
PS C:\Users\Lenovo\Desktop\task_02\src\build> ./runTests.exe
[==========] Running 8 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearModelTest
[ RUN      ] LinearModelTest.ZeroInput
[       OK ] LinearModelTest.ZeroInput (0 ms)
[ RUN      ] LinearModelTest.StepInput
[       OK ] LinearModelTest.StepInput (0 ms)
[ RUN      ] LinearModelTest.OnlyControl
[       OK ] LinearModelTest.OnlyControl (0 ms)
[ RUN      ] LinearModelTest.NegativeValues
[       OK ] LinearModelTest.NegativeValues (0 ms)
[----------] 4 tests from LinearModelTest (22 ms total)

[----------] 4 tests from NonlinearModelTest
[ RUN      ] NonlinearModelTest.ZeroInput
[       OK ] NonlinearModelTest.ZeroInput (0 ms)
[ RUN      ] NonlinearModelTest.StepInput
[       OK ] NonlinearModelTest.StepInput (0 ms)
[ RUN      ] NonlinearModelTest.WithPrevControl
[       OK ] NonlinearModelTest.WithPrevControl (0 ms)
[ RUN      ] NonlinearModelTest.NegativeInputs
[       OK ] NonlinearModelTest.NegativeInputs (0 ms)
[----------] 4 tests from NonlinearModelTest (19 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 2 test suites ran. (64 ms total)
[  PASSED  ] 8 tests.


## Code Coverage

Code Coverage Report:
    Lines: 95.0% (57 out of 60)
    Functions: 100.0% (10 out of 10)
    Branches: 90.0% (18 out of 20)