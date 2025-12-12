<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Прокурат В. Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06523/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---
## Выполнение работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/temp_model.h"

TEST(TemperatureModelTest, LinearInitialConditions) {
    TemperatureModel model(0.8, 0.2);
    model.setInitialConditions(20.0);

    EXPECT_DOUBLE_EQ(model.getCurrentTemperature(), 20.0);
}

TEST(TemperatureModelTest, LinearNextValueCalculation) {
    TemperatureModel model(0.8, 0.2);
    model.setInitialConditions(20.0);

    double y = model.calculateNext(10.0);
    EXPECT_NEAR(y, 0.8 * 20.0 + 0.2 * 10.0, 1e-9);
}

TEST(TemperatureModelTest, NonlinearUpdateCalculation) {
    TemperatureModel model(0.7, 0.01, 0.3, 0.1);
    model.setInitialConditions(20.0, 19.5, 5.0);

    double y = model.calculateNext(10.0);
    double expected = 0.7 * 20.0
                    - 0.01 * 19.5 * 19.5
                    + 0.3 * 10.0
                    + 0.1 * sin(5.0);

    EXPECT_NEAR(y, expected, 1e-9);
}

TEST(TemperatureModelTest, NonlinearMultipleSteps) {
    TemperatureModel model(0.7, 0.01, 0.3, 0.1);
    model.setInitialConditions(20.0, 19.5, 5.0);

    model.calculateNext(10);
    model.calculateNext(15);
    EXPECT_NO_THROW(model.getCurrentTemperature());
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 4 tests from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 4 tests from TemperatureModelTest
1: [ RUN      ] TemperatureModelTest.LinearInitialConditions
1: [       OK ] TemperatureModelTest.LinearInitialConditions (0 ms)
1: [ RUN      ] TemperatureModelTest.LinearNextValueCalculation
1: [       OK ] TemperatureModelTest.LinearNextValueCalculation (0 ms)
1: [ RUN      ] TemperatureModelTest.NonlinearUpdateCalculation
1: [       OK ] TemperatureModelTest.NonlinearUpdateCalculation (0 ms)
1: [ RUN      ] TemperatureModelTest.NonlinearMultipleSteps
1: [       OK ] TemperatureModelTest.NonlinearMultipleSteps (0 ms)
1: [----------] 4 tests from TemperatureModelTest (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 4 tests from 1 test suite ran. (0 ms total)
1: [  PASSED  ] 4 tests.
1/1 Test #1: AllTests .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

# Процент покрытия кода тестами

## 📂 Overall coverage

| Metric        | Coverage |
|---------------|----------|
| **Lines**     | 🔴 23/76 (30.3%) |
| **Functions** | 🔴 5/12 (41.7%) |
| **Branches**  | 🔴 2/60 (3.3%) |

## 📄 File coverage

| File                   | Lines | Functions | Branches |
|------------------------|-------|-----------|----------|
| **`main.cpp`** | 🔴 0/53 (0.0%) | 🔴 0/7 (0.0%) | 🔴 0/58 (0.0%) |
| **`temp_model.cpp`** | 🟢 23/23 (100.0%) | 🟢 5/5 (100.0%) | 🟢 2/2 (100.0%) |



**Вывод:** В рамках лабораторной работы были успешно реализованы модульные тесты для линейной и нелинейной модели температуры. Основной функциональный модуль temp_model.cpp протестирован полностью, что подтверждается 100% покрытием строк, функций и ветвлений в данном файле. Низкий общий процент покрытия объясняется тем, что файл main.cpp не подлежит тестированию. Все разработанные тесты успешно пройдены, что подтверждает корректность работы модели.
