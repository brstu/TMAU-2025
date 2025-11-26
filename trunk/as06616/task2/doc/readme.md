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
<p align="right">Николова М.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1.Использовать следующий фреймворк для модульного тестирования - Google Test.
2.Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: trunk\as0xxyy\task_02\test.
3.Исходный код модифицированной программы разместить в каталоге: trunk\as0xxyy\task_02\src.
4.В файле readme.md отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, gcovr).
5.Также необходимо отразить выполнение работы в общем файле readme.md в соответствующей строке.

Выполнение работы

Тесты
 ```cpp
#include <gtest/gtest.h>
#include "func.h"
#include <cmath>

// Тесты для линейной модели
TEST(LinearModel, test_zero) {
    EXPECT_DOUBLE_EQ(linearmodel(0, 0), 0);
}

TEST(LinearModel, test_u0) {
    EXPECT_DOUBLE_EQ(linearmodel(18, 0), temperatureCoeff * 18);
}

TEST(LinearModel, test_y0) {
    EXPECT_DOUBLE_EQ(linearmodel(0, 5), prevTemperatureCoeff * 5);
}

TEST(LinearModel, test_default) {
    EXPECT_DOUBLE_EQ(linearmodel(18, 5), temperatureCoeff * 18 + prevTemperatureCoeff * 5);
}

// Тесты для нелинейной модели
TEST(NonLinearModel, test_zero) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(0, 0, 0, 0), 0);
}

TEST(NonLinearModel, test_u0) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(18, 18, 0, 0),
        temperatureCoeff * 18 - prevTemperatureCoeff * std::pow(18, 2));
}

TEST(NonLinearModel, test_y0) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(0, 0, 5, 5),
        warmCoeff * 5 + prevWarmCoeffSin * std::sin(5));
}

TEST(NonLinearModel, test_default) {
    EXPECT_DOUBLE_EQ(nonlinearmodel(18, 18, 5, 5),
        temperatureCoeff * 18 - prevTemperatureCoeff * std::pow(18, 2) +
        warmCoeff * 5 + prevWarmCoeffSin * std::sin(5));
}

// Тесты для функции updateWarm
TEST(UpdateWarm, test_zero) {
    EXPECT_DOUBLE_EQ(updateWarm(0, 0), 0.1 * std::sin(0));
}

TEST(UpdateWarm, test_base_only) {
    EXPECT_DOUBLE_EQ(updateWarm(5, 0), 5 + 0.1 * std::sin(0));
}

TEST(UpdateWarm, test_time_only) {
    EXPECT_DOUBLE_EQ(updateWarm(0, 2), 0.1 * std::sin(2));
}

TEST(UpdateWarm, test_default) {
    EXPECT_DOUBLE_EQ(updateWarm(3, 1), 3 + 0.1 * std::sin(1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

 
Результаты тестов:
```
[==========] Running 12 tests from 3 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearModel
[ RUN      ] LinearModel.test_zero
[       OK ] LinearModel.test_zero (0 ms)
[ RUN      ] LinearModel.test_u0
[       OK ] LinearModel.test_u0 (0 ms)
[ RUN      ] LinearModel.test_y0
[       OK ] LinearModel.test_y0 (0 ms)
[ RUN      ] LinearModel.test_default
[       OK ] LinearModel.test_default (0 ms)
[----------] 4 tests from LinearModel (3 ms total)

[----------] 4 tests from NonLinearModel
[ RUN      ] NonLinearModel.test_zero
[       OK ] NonLinearModel.test_zero (0 ms)
[ RUN      ] NonLinearModel.test_u0
[       OK ] NonLinearModel.test_u0 (0 ms)
[ RUN      ] NonLinearModel.test_y0
[       OK ] NonLinearModel.test_y0 (0 ms)
[ RUN      ] NonLinearModel.test_default
[       OK ] NonLinearModel.test_default (0 ms)
[----------] 4 tests from NonLinearModel (2 ms total)

[----------] 4 tests from UpdateWarm
[ RUN      ] UpdateWarm.test_zero
[       OK ] UpdateWarm.test_zero (0 ms)
[ RUN      ] UpdateWarm.test_base_only
[       OK ] UpdateWarm.test_base_only (0 ms)
[ RUN      ] UpdateWarm.test_time_only
[       OK ] UpdateWarm.test_time_only (0 ms)
[ RUN      ] UpdateWarm.test_default
[       OK ] UpdateWarm.test_default (0 ms)
[----------] 4 tests from UpdateWarm (4 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 3 test suites ran. (12 ms total)
[  PASSED  ] 12 tests.
```
Общий уровень покрытия составляет 26%, однако в этот показатель входят также файлы сторонних библиотек, которые не являются объектом тестирования. func.cpp имеет 100% покрытие.

В процессе работы были разработаны модульные тесты для функций linear() и nonlinear() с использованием фреймворка Google Test. Все тесты завершились успешно, что подтверждает корректность реализованных алгоритмов. Согласно анализу покрытия кода с помощью OpenCppCoverage, общее покрытие составило около 26%, при этом пользовательские функции охвачены тестами полностью.