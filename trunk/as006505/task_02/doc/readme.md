<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “ТМАУ"</p>
<p align="center">Тема: “Модульное тестирование. Покрытие исходного кода тестами.”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Егоренков Н.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Дворанинович Д.А.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk/as006515/task_02/test**.  
3. Исходный код модифицированной программы разместить в каталоге: **trunk/as006515/task_02/src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (например, с помощью [gcovr](https://gcovr.com/en/stable/)).  
5. Также необходимо отразить выполнение работы в общем [`readme.md`](https://github.com/brstu/OTIS-2025/blob/main/README.md) в соответствующей строке.

---

# Код юнит-тестов [ test/test.cpp ]

```cpp
#include <gtest/gtest.h>
#include <cmath>
#include "../src/model.h"

// Тесты для линейной модели
TEST(LinearModelTest, ZeroInitialValue) {
    EXPECT_NEAR(nextLinear(0.3, 0.3, 0.9, 0.0), 0.27, 1e-6);
}

TEST(LinearModelTest, WithNonZeroY) {
    EXPECT_NEAR(nextLinear(0.3, 0.3, 0.9, 1.0), 0.57, 1e-6);
}

TEST(LinearModelTest, NegativeValues) {
    EXPECT_NEAR(nextLinear(0.5, 0.2, -1.0, 2.0), 0.8, 1e-6);
}

// Тесты для нелинейной модели
TEST(NonlinearModelTest, ZeroInitialValues) {
    NonlinearParams params{0.1, 0.2, 0.4, 0.2};
    double result = nextNonlinear(params, 0.0, 0.0, 0.0); // u_prev, y, y_prev
    double expected = 0.1 * 0.0 - 0.2 * (0.0 * 0.0) + 0.4 * 0.0 + 0.2 * std::sin(0.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithPreviousValues) {
    NonlinearParams params{0.1, 0.2, 0.4, 0.2};
    double result = nextNonlinear(params, 0.8, 0.5, 0.3); // u_prev, y, y_prev
    double expected = 0.1 * 0.5 - 0.2 * (0.3 * 0.3) + 0.4 * 0.8 + 0.2 * std::sin(0.8);
    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, ComplexCase) {
    NonlinearParams params{0.5, 0.1, 0.3, 0.4};
    double result = nextNonlinear(params, 1.0, 2.0, 1.5); // u_prev, y, y_prev
    double expected = 0.5 * 2.0 - 0.1 * (1.5 * 1.5) + 0.3 * 1.0 + 0.4 * std::sin(1.0);
    EXPECT_NEAR(result, expected, 1e-6);
}

// Тесты для симуляции
TEST(SimulationTest, LinearSimulationRuns) {
    EXPECT_NO_THROW(simulateLinearVec(0.3, 0.3, 0.9, 5));
}

TEST(SimulationTest, NonlinearSimulationRuns) {
    EXPECT_NO_THROW(simulateNonlinearVec(0.1, 0.2, 0.4, 0.2, 0.8, 5));
}

TEST(SimulationTest, LinearSimulationValues) {
    auto result = simulateLinearVec(0.3, 0.3, 1.0, 3);
    EXPECT_EQ(result.size(), 3);
    EXPECT_NEAR(result[0], 0.0, 1e-6);
    EXPECT_NEAR(result[1], 0.3, 1e-6);  // 0.3*0 + 0.3*1 = 0.3
    EXPECT_NEAR(result[2], 0.39, 1e-6); // 0.3*0.3 + 0.3*1 = 0.39
}
