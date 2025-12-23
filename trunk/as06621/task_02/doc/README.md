
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
<p align="right">Рогожин А. С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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
#include <gtest/gtest.h>
#include <cmath>
#include "func.h"

TEST(Linear, ZeroInputZeroState) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(Linear, NegativeValues) {
    double y = -10;
    double u = -3;
    EXPECT_DOUBLE_EQ(linear(y, u), a * y + b * u);
}

TEST(Linear, MonotonicityIncreaseInput) {
    // Если u2 > u1 и y одинаковые, выход должен вырасти
    double y = 5;
    double u1 = 1;
    double u2 = 3;

    double r1 = linear(y, u1);
    double r2 = linear(y, u2);

    EXPECT_GT(r2, r1);
}

TEST(Linear, MonotonicityIncreaseState) {
    // Если y2 > y1 при одинаковом u, выход должен вырасти
    double y1 = 2;
    double y2 = 5;
    double u = 4;

    EXPECT_GT(linear(y2, u), linear(y1, u));
}

TEST(NonLinear, ZeroEverything) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinear, OnlyTemperature) {
    // ut = 0, ut_1 = 0 → остаётся только a*y - b*(y1^2)
    double y = 4;
    double y1 = 4;

    EXPECT_DOUBLE_EQ(
        nonlinear(y, y1, 0, 0),
        a * y - b * y1 * y1
    );
}

TEST(NonLinear, OnlyHeating) {
    // y = 0 → остаётся c*ut + d*sin(ut_1)
    double ut = 3;
    double ut1 = 2;

    EXPECT_NEAR(
        nonlinear(0, 0, ut, ut1),
        c * ut + d * std::sin(ut1),
        1e-12
    );
}

TEST(NonLinear, NegativeInputs) {
    double y = -5;
    double y1 = -4;
    double ut = -2;
    double ut1 = -3;

    double expected = a * y - b * y1 * y1 + c * ut + d * std::sin(ut1);

    EXPECT_NEAR(nonlinear(y, y1, ut, ut1), expected, 1e-12);
}

TEST(NonLinear, SensitivityToPreviousInput) {
    // Проверяем, что sin(ut1) реально влияет
    double y = 5, y1 = 4, ut = 2;

    double r1 = nonlinear(y, y1, ut, 0);
    double r2 = nonlinear(y, y1, ut, 1);

    EXPECT_NE(r1, r2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

### Сборка проекта
Для сборки проекта в папке *src* необходимо произвести следующие действия:

mkdir build
cd build
cmake ..
cmake --build . --config Debug
ctest
```
Таким образом в итоге получим :
[==========] Running 9 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from Linear
[ RUN      ] Linear.ZeroInputZeroState
[       OK ] Linear.ZeroInputZeroState (0 ms)
[ RUN      ] Linear.NegativeValues
[       OK ] Linear.NegativeValues (0 ms)
[ RUN      ] Linear.MonotonicityIncreaseInput
[       OK ] Linear.MonotonicityIncreaseInput (0 ms)
[ RUN      ] Linear.MonotonicityIncreaseState
[       OK ] Linear.MonotonicityIncreaseState (0 ms)
[----------] 4 tests from Linear (0 ms total)

[----------] 5 tests from NonLinear
[ RUN      ] NonLinear.ZeroEverything
[       OK ] NonLinear.ZeroEverything (0 ms)
[ RUN      ] NonLinear.OnlyTemperature
[       OK ] NonLinear.OnlyTemperature (0 ms)
[ RUN      ] NonLinear.OnlyHeating
[       OK ] NonLinear.OnlyHeating (0 ms)
[ RUN      ] NonLinear.NegativeInputs
[       OK ] NonLinear.NegativeInputs (0 ms)
[ RUN      ] NonLinear.SensitivityToPreviousInput
[       OK ] NonLinear.SensitivityToPreviousInput (0 ms)
[----------] 5 tests from NonLinear (0 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 9 tests.

Таким образом получили файл *index.html*, в котором отражены результаты тестирования. Общий процент покрытия кодом составляет 26%, но в него также включаются и файлы используемых библиотек. Так как они тестированию не подвергаются, значимым показателем будем считать процент покрытия тестами только для файла *func.cpp*, в котором содержаться тестируемые функции. Для данного файла процент покрытия составляет 100%

**Вывод:** В ходе работы были разработаны и выполнены модульные тесты для линейной и нелинейной функций с использованием фреймворка Google Test.
Все тесты успешно прошли, что подтвердило корректность реализованных алгоритмов.
Анализ покрытия кода с помощью OpenCppCoverage показал общее покрытие около 26%, при этом пользовательские функции протестированы полностью.