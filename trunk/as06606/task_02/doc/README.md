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
<p align="right">Езепчук А.С.</p>
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
#include <cmath>
#include "../src/func.h"   // подключение тестируемого кода

// Тесты для linear_step и nonlinear_step из func.h

TEST(linear_step, test_zero) {
    EXPECT_DOUBLE_EQ(linear_step(0, 0), 0);
}

TEST(linear_step, test_u_zero) {
    EXPECT_DOUBLE_EQ(linear_step(18, 0), A * 18);
}

TEST(linear_step, test_y_zero) {
    EXPECT_DOUBLE_EQ(linear_step(0, 5), B_LIN * 5);
}

TEST(linear_step, test_default) {
    EXPECT_DOUBLE_EQ(linear_step(18, 5), A * 18 + B_LIN * 5);
}

TEST(nonlinear_step, test_zero) {
    EXPECT_DOUBLE_EQ(nonlinear_step(0, 0, 0), 0);
}

TEST(nonlinear_step, test_u_zero) {
    EXPECT_NEAR(nonlinear_step(18, 0, 0), A * 18 - C * pow(18, 2), 1e-9);
}

TEST(nonlinear_step, test_y_zero) {
    EXPECT_NEAR(nonlinear_step(0, 5, 5), C * 5 + D * sin(5), 1e-9);
}

TEST(nonlinear_step, test_default) {
    EXPECT_NEAR(nonlinear_step(18, 5, 5),
                A * 18 - C * pow(18, 2) + C * 5 + D * sin(5),
                1e-9);
}

Test project D:/TiMAU/TMAU-2025/trunk/as06606/task_02/src/build
    Start 1: linear_step.test_zero
1/8 Test #1: linear_step.test_zero .............   Passed    0.01 sec
    Start 2: linear_step.test_u_zero
2/8 Test #2: linear_step.test_u_zero ..........   Passed    0.01 sec
    Start 3: linear_step.test_y_zero
3/8 Test #3: linear_step.test_y_zero ..........   Passed    0.01 sec
    Start 4: linear_step.test_default
4/8 Test #4: linear_step.test_default .........   Passed    0.01 sec
    Start 5: nonlinear_step.test_zero
5/8 Test #5: nonlinear_step.test_zero ........  Passed    0.01 sec
    Start 6: nonlinear_step.test_u_zero
6/8 Test #6: nonlinear_step.test_u_zero ........ Passed    0.01 sec
    Start 7: nonlinear_step.test_y_zero
7/8 Test #7: nonlinear_step.test_y_zero ........ Passed    0.01 sec
    Start 8: nonlinear_step.test_default
8/8 Test #8: nonlinear_step.test_default .....  Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) = 0.07 sec