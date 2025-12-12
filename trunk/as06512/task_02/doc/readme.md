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
<p align="right">Группы АС-65</p>
<p align="right">Нестюк Н.C.</p>
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
#include "functions.h"
#include <cmath>

TEST(Linear, test_zero) {
    EXPECT_EQ(linear(0, 0), 0);
}

TEST(Linear, test_u0) {
    EXPECT_EQ(linear(18, 0), a * 18);
}

TEST(Linear, test_y0) {
    EXPECT_EQ(linear(0, 5), b * 5);
}

TEST(Linear, test_default) {
    EXPECT_EQ(linear(18, 5), a * 18 + b * 5);
}

TEST(Linear, test_negative_values) {
    EXPECT_EQ(linear(-10, -5), a * (-10) + b * (-5));
}

TEST(Linear, test_fractional_values) {
    EXPECT_DOUBLE_EQ(linear(2.5, 3.7), a * 2.5 + b * 3.7);
}

TEST(Linear, test_large_values) {
    EXPECT_EQ(linear(1000, 500), a * 1000 + b * 500);
}

TEST(NonLinear, test_zero) {
    EXPECT_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinear, test_u0) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 0, 0), a * 18 - b * 18 * 18);
}

TEST(NonLinear, test_y0) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 5, 5), c * 5 + d * sin(5));
}

TEST(NonLinear, test_default) {
    EXPECT_DOUBLE_EQ(nonlinear(18, 18, 5, 5), a * 18 - b * 18 * 18 + c * 5 + d * sin(5));
}

TEST(NonLinear, test_negative_inputs) {
    EXPECT_DOUBLE_EQ(nonlinear(-5, -3, -2, -1),
        a * (-5) - b * (-3) * (-3) + c * (-2) + d * sin(-1));
}

TEST(NonLinear, test_different_yt_yt1) {
    EXPECT_DOUBLE_EQ(nonlinear(10, 5, 3, 2),
        a * 10 - b * 5 * 5 + c * 3 + d * sin(2));
}

TEST(NonLinear, test_fractional_values) {
    double yt = 2.5, yt1 = 1.5, ut = 3.7, ut1 = 0.5;
    EXPECT_DOUBLE_EQ(nonlinear(yt, yt1, ut, ut1),
        a * yt - b * yt1 * yt1 + c * ut + d * sin(ut1));
}

TEST(NonLinear, test_large_values) {
    EXPECT_DOUBLE_EQ(nonlinear(100, 50, 25, 10),
        a * 100 - b * 50 * 50 + c * 25 + d * sin(10));
}


TEST(NonLinear, test_precision) {
    double result = nonlinear(1.234567, 2.345678, 3.456789, 4.567890);
    double expected = a * 1.234567 - b * 2.345678 * 2.345678 + c * 3.456789 + d * sin(4.567890);
    EXPECT_NEAR(result, expected, 1e-10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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
Провели анализ покрытия кода тестами при помощи утилиты OpenCppCoverage. Суммарное покрытие — 27%. functions.cpp имеет 100% покрытие.
```bash
"D:\0101\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"D:\TMAU02\coverage" ^
--sources="D:\TMAU02\task02\src" ^
-- "D:\TMAU02\task02\src\build\Debug\runTests.exe"
```
**Вывод:** Функции linear() и nonlinear() протестированы с помощью Google Test — все тесты пройдены успешно. Покрытие кода по данным OpenCppCoverage составило 27%, при этом пользовательские функции охвачены полностью.