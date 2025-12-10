<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Макарский А. Э.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **trunk/as06511/task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---
## Ход работы
---
### Тесты

```cpp
#include <gtest/gtest.h>
#include "../src/temp_model.h"
#include <cmath>


TEST(LinearModelTest, ZeroInputZeroState) {
    Lin p{0.8, 0.2};
    
    double expected = p.a * 0.0 + p.b * 0.0;
    double result = step_lin(0.0, 0.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(LinearModelTest, SimpleStep) {
    Lin p{0.8, 0.2};

    double expected = p.a * 10.0 + p.b * 5.0;
    double result = step_lin(10.0, 5.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(LinearModelTest, NegativeValues) {
    Lin p{0.5, 0.5};

    double expected = p.a * (-4.0) + p.b * (-2.0);
    double result = step_lin(-4.0, -2.0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}


TEST(NonlinearModelTest, ZeroEverything) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = 0.0;
    double result = step_nonlin(0, 0, 0, 0, p);

    EXPECT_DOUBLE_EQ(result, expected);
}

TEST(NonlinearModelTest, NoSinEffect) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = p.a * 10.0 - p.b * (2.0 * 2.0) + p.c * 1.0 + p.d * std::sin(0.0);
    double result = step_nonlin(10.0, 2.0, 1.0, 0.0, p);

    EXPECT_NEAR(result, expected, 1e-6);
}

TEST(NonlinearModelTest, WithSinEffect) {
    Nonlin p{0.76, 0.18, 0.09, 0.14};

    double expected = p.a * 5.0 - p.b * (1.0 * 1.0) + p.c * 2.0 + p.d * std::sin(M_PI / 2);
    double result = step_nonlin(5.0, 1.0, 2.0, M_PI/2, p);

    EXPECT_NEAR(result, expected, 1e-9);
}
```

### Результат выполнения тестов:
```bash
1: [==========] Running 6 tests from 2 test suites.
1: [----------] Global test environment set-up.
1: [----------] 3 tests from LinearModelTest
1: [ RUN      ] LinearModelTest.ZeroInputZeroState
1: [       OK ] LinearModelTest.ZeroInputZeroState (0 ms)
1: [ RUN      ] LinearModelTest.SimpleStep
1: [       OK ] LinearModelTest.SimpleStep (0 ms)
1: [ RUN      ] LinearModelTest.NegativeValues
1: [       OK ] LinearModelTest.NegativeValues (0 ms)
1: [----------] 3 tests from LinearModelTest (0 ms total)
1: 
1: [----------] 3 tests from NonlinearModelTest
1: [ RUN      ] NonlinearModelTest.ZeroEverything
1: [       OK ] NonlinearModelTest.ZeroEverything (0 ms)
1: [ RUN      ] NonlinearModelTest.NoSinEffect
1: [       OK ] NonlinearModelTest.NoSinEffect (0 ms)
1: [ RUN      ] NonlinearModelTest.WithSinEffect
1: [       OK ] NonlinearModelTest.WithSinEffect (0 ms)
1: [----------] 3 tests from NonlinearModelTest (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 6 tests from 2 test suites ran. (0 ms total)
1: [  PASSED  ] 6 tests.
1/1 Test #1: AllTests .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec
```

# Процент покрытия кода тестами

```bash
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: ..
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
main.cpp                                       3       0     0%   3-5
temp_model.cpp                                23       5    21%   15-17,19-21,23-24,26-28,30,34-36,38-39,41
------------------------------------------------------------------------------
TOTAL                                         26       5    19%
------------------------------------------------------------------------------
```



**Вывод:** в ходе лабораторной работы были разработаны модульные тесты для проверки линейной и нелинейной модели температуры. Согласно отчёту покрытия, основной функциональный модуль temp_model.cpp имеет частичное покрытие (21%), что свидетельствует о необходимости расширения набора тестов для проверки всех ветвей и условий. Низкий общий процент покрытия (19%) объясняется отсутствием тестирования файла main.cpp, который выполняет лишь запуск программы и не требует отдельной проверки. Все существующие тесты были успешно пройдены, что подтверждает корректность базовой реализации моделей.
