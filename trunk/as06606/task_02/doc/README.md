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

TEST(LinearModel, test_zero) {
    LinearModel model(0.9, 0.2);
    EXPECT_DOUBLE_EQ(model.step(0, 0), 0);
}

TEST(LinearModel, test_u_zero) {
    LinearModel model(0.9, 0.2);
    EXPECT_DOUBLE_EQ(model.step(18, 0), 0.9 * 18);
}

TEST(LinearModel, test_y_zero) {
    LinearModel model(0.9, 0.2);
    EXPECT_DOUBLE_EQ(model.step(0, 5), 0.2 * 5);
}

TEST(LinearModel, test_default) {
    LinearModel model(0.9, 0.2);
    EXPECT_DOUBLE_EQ(model.step(18, 5), 0.9 * 18 + 0.2 * 5);
}

TEST(NonlinearModel, test_zero) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    EXPECT_DOUBLE_EQ(model.step(0, 0, 0), 0);
}

TEST(NonlinearModel, test_u_zero) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    EXPECT_NEAR(model.step(18, 0, 0), 0.9 * 18 - 0.01 * pow(18, 2), 1e-9);
}

TEST(NonlinearModel, test_y_zero) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    EXPECT_NEAR(model.step(0, 5, 5), 0.15 * 5 + 0.05 * sin(5), 1e-9);
}

TEST(NonlinearModel, test_default) {
    NonlinearModel model(0.9, 0.01, 0.15, 0.05);
    EXPECT_NEAR(model.step(18, 5, 5),
                0.9 * 18 - 0.01 * pow(18, 2) + 0.15 * 5 + 0.05 * sin(5),
                1e-9);
}

Test project D:/TiMAU/TMAU-2025/trunk/as06606/task_02/src/build
    Start 1: LinearModel.test_zero
1/8 Test #1: LinearModel.test_zero .............   Passed    0.01 sec
    Start 2: LinearModel.test_u_zero
2/8 Test #2: LinearModel.test_u_zero ..........   Passed    0.01 sec
    Start 3: LinearModel.test_y_zero
3/8 Test #3: LinearModel.test_y_zero ..........   Passed    0.01 sec
    Start 4: LinearModel.test_default
4/8 Test #4: LinearModel.test_default .........   Passed    0.01 sec
    Start 5: NonlinearModel.test_zero
5/8 Test #5: NonlinearModel.test_zero ........  Passed    0.01 sec
    Start 6: NonlinearModel.test_u_zero
6/8 Test #6: NonlinearModel.test_u_zero ........ Passed    0.01 sec
    Start 7: NonlinearModel.test_y_zero
7/8 Test #7: NonlinearModel.test_y_zero ........ Passed    0.01 sec
    Start 8: NonlinearModel.test_default
8/8 Test #8: NonlinearModel.test_default .....  Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) = 0.07 sec