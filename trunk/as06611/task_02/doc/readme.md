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
<p align="right">Лысюк Р.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/). 
3. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
4. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
5. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
6. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.
## Выполнение работы

### Тесты
 ```cpp
#include <gtest/gtest.h>
#include "../src/functions.h"
#include <cmath>

// Тесты для линейной модели
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0.0, 0.0), 0.0);
}

TEST(LinearModel, OnlyYNonZero) {
    EXPECT_DOUBLE_EQ(linear(18.0, 0.0), a * 18.0);
}

TEST(LinearModel, OnlyUNonZero) {
    EXPECT_DOUBLE_EQ(linear(0.0, 5.0), b * 5.0);
}

TEST(LinearModel, TypicalValues) {
    EXPECT_DOUBLE_EQ(linear(18.0, 5.0), a * 18.0 + b * 5.0);
}

TEST(LinearModel, NegativeValues) {
    EXPECT_DOUBLE_EQ(linear(-10.0, -5.0), a * (-10.0) + b * (-5.0));
}

TEST(LinearModel, FractionalValues) {
    EXPECT_DOUBLE_EQ(linear(2.5, 3.7), a * 2.5 + b * 3.7);
}

TEST(LinearModel, LargeValues) {
    EXPECT_DOUBLE_EQ(linear(1000.0, 500.0), a * 1000.0 + b * 500.0);
}

// Тесты для нелинейной модели
TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 0.0, 0.0), 0.0);
}

TEST(NonlinearModel, OnlyYNonZero) {
    EXPECT_DOUBLE_EQ(nonlinear(18.0, 18.0, 0.0, 0.0), a * 18.0 - b * 18.0 * 18.0);
}

TEST(NonlinearModel, OnlyUNonZero) {
    EXPECT_DOUBLE_EQ(nonlinear(0.0, 0.0, 5.0, 5.0), c * 5.0 + d * sin(5.0));
}

TEST(NonlinearModel, TypicalValues) {
    EXPECT_DOUBLE_EQ(nonlinear(18.0, 18.0, 5.0, 5.0),
                     a * 18.0 - b * 18.0 * 18.0 + c * 5.0 + d * sin(5.0));
}

TEST(NonlinearModel, NegativeInputs) {
    EXPECT_DOUBLE_EQ(nonlinear(-5.0, -3.0, -2.0, -1.0),
                     a * (-5.0) - b * (-3.0) * (-3.0) + c * (-2.0) + d * sin(-1.0));
}

TEST(NonlinearModel, DifferentYtYt1) {
    EXPECT_DOUBLE_EQ(nonlinear(10.0, 5.0, 3.0, 2.0),
                     a * 10.0 - b * 25.0 + c * 3.0 + d * sin(2.0));
}

TEST(NonlinearModel, FractionalValues) {
    EXPECT_DOUBLE_EQ(nonlinear(2.5, 1.5, 3.7, 0.5),
                     a * 2.5 - b * 1.5 * 1.5 + c * 3.7 + d * sin(0.5));
}

TEST(NonlinearModel, LargeValues) {
    EXPECT_DOUBLE_EQ(nonlinear(100.0, 50.0, 25.0, 10.0),
                     a * 100.0 - b * 2500.0 + c * 25.0 + d * sin(10.0));
}

TEST(NonlinearModel, PrecisionCheck) {
    double result = nonlinear(1.234567, 2.345678, 3.456789, 4.567890);
    double expected = a * 1.234567 - b * 2.345678 * 2.345678 + c * 3.456789 + d * sin(4.567890);
    EXPECT_NEAR(result, expected, 1e-10);
}


 ```

Таким образом в итоге получим :
```bash
[==========] Running 16 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 7 tests from Linear
[ RUN      ] Linear.test_zero
[       OK ] Linear.test_zero (0 ms)
[ RUN      ] Linear.test_u0
[       OK ] Linear.test_u0 (0 ms)
[ RUN      ] Linear.test_y0
[       OK ] Linear.test_y0 (0 ms)
[ RUN      ] Linear.test_default
[       OK ] Linear.test_default (0 ms)
[ RUN      ] Linear.test_negative_values
[       OK ] Linear.test_negative_values (0 ms)
[ RUN      ] Linear.test_fractional_values
[       OK ] Linear.test_fractional_values (0 ms)
[ RUN      ] Linear.test_large_values
[       OK ] Linear.test_large_values (0 ms)
[----------] 7 tests from Linear (1 ms total)

[----------] 9 tests from NonLinear
[ RUN      ] NonLinear.test_zero
[       OK ] NonLinear.test_zero (0 ms)
[ RUN      ] NonLinear.test_u0
[       OK ] NonLinear.test_u0 (0 ms)
[ RUN      ] NonLinear.test_y0
[       OK ] NonLinear.test_y0 (0 ms)
[ RUN      ] NonLinear.test_default
[       OK ] NonLinear.test_default (0 ms)
[ RUN      ] NonLinear.test_negative_inputs
[       OK ] NonLinear.test_negative_inputs (0 ms)
[ RUN      ] NonLinear.test_different_yt_yt1
[       OK ] NonLinear.test_different_yt_yt1 (0 ms)
[ RUN      ] NonLinear.test_fractional_values
[       OK ] NonLinear.test_fractional_values (0 ms)
[ RUN      ] NonLinear.test_large_values
[       OK ] NonLinear.test_large_values (0 ms)
[ RUN      ] NonLinear.test_precision
[       OK ] NonLinear.test_precision (0 ms)
[----------] 9 tests from NonLinear (1 ms total)

[----------] Global test environment tear-down
[==========] 16 tests from 2 test suites ran. (3 ms total)
[  PASSED  ] 16 tests.
```

### Покрытие кода тестами
Провели анализ покрытия кода тестами при помощи утилиты OpenCppCoverage. Суммарное покрытие — 27% (включая все файлы, такие как тестовый фреймворк и вспомогательные файлы), при этом functions.cpp (пользовательские функции) имеет 100% покрытие.
```bash
"D:\0101\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"C:\Users\Rostislav\TMAU-2025\trunk\as06611\task_02\coverage" ^
--sources="C:\Users\Rostislav\TMAU-2025\trunk\as06611\task_02\src" ^
-- "C:\Users\Rostislav\TMAU-2025\trunk\as06611\task_02\src\build\Debug\runTests.exe"
```
**Вывод:** Функции Linear() и NonLinear() протестированы с помощью Google Test — все тесты пройдены успешно. Покрытие кода по данным OpenCppCoverage составило 27%, при этом пользовательские функции охвачены полностью.