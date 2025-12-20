
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
<p align="right">Кацевич А. Ю.</p>
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
TEST(LinearModelTest, ZeroInputZeroState) {
    EXPECT_DOUBLE_EQ(computeLinearModel(0, 0), 0);
}

TEST(LinearModelTest, NegativeValues) {
    double y = -10;
    double u = -3;
    EXPECT_DOUBLE_EQ(computeLinearModel(y, u), LINEAR_A * y + LINEAR_B * u);
}

TEST(LinearModelTest, MonotonicityIncreaseInput) {
    double y = 5;
    double u1 = 1;
    double u2 = 3;
    double r1 = computeLinearModel(y, u1);
    double r2 = computeLinearModel(y, u2);
    EXPECT_GT(r2, r1);
}

TEST(LinearModelTest, MonotonicityIncreaseState) {
    double y1 = 2;
    double y2 = 5;
    double u = 4;
    EXPECT_GT(computeLinearModel(y2, u), computeLinearModel(y1, u));
}

TEST(LinearModelTest, LinearCoefficientVerification) {
    // Проверка, что коэффициенты работают как ожидается
    double y = 10.0;
    double u = 5.0;
    double expected = 0.9 * 10.0 + 0.01 * 5.0; // LINEAR_A * y + LINEAR_B * u
    EXPECT_DOUBLE_EQ(computeLinearModel(y, u), expected);
}

TEST(NonLinearModelTest, ZeroEverything) {
    EXPECT_DOUBLE_EQ(computeNonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonLinearModelTest, OnlyTemperature) {
    double y = 4;
    double y_prev = 4;
    EXPECT_DOUBLE_EQ(
        computeNonlinearModel(y, y_prev, 0, 0),
        NONLINEAR_A * y - NONLINEAR_B * std::pow(y_prev, 2)
    );
}

TEST(NonLinearModelTest, OnlyHeating) {
    double u_current = 3;
    double u_prev = 2;
    EXPECT_NEAR(
        computeNonlinearModel(0, 0, u_current, u_prev),
        NONLINEAR_C * u_current + NONLINEAR_D * std::sin(u_prev),
        1e-12
    );
}

TEST(NonLinearModelTest, NegativeInputs) {
    double y = -5;
    double y_prev = -4;
    double u_current = -2;
    double u_prev = -3;
    double expected = NONLINEAR_A * y 
                     - NONLINEAR_B * std::pow(y_prev, 2)
                     + NONLINEAR_C * u_current 
                     + NONLINEAR_D * std::sin(u_prev);
    EXPECT_NEAR(computeNonlinearModel(y, y_prev, u_current, u_prev), 
                expected, 1e-12);
}

TEST(NonLinearModelTest, SensitivityToPreviousInput) {
    double y = 5;
    double y_prev = 4;
    double u_current = 2;
    double r1 = computeNonlinearModel(y, y_prev, u_current, 0);
    double r2 = computeNonlinearModel(y, y_prev, u_current, 1);
    EXPECT_NE(r1, r2);
}

TEST(NonLinearModelTest, SinFunctionEffect) {
    // Проверка, что синус действительно влияет на результат
    double y = 1;
    double y_prev = 1;
    double u_current = 1;
    
    // При разных предыдущих управлениях результат должен отличаться
    double result1 = computeNonlinearModel(y, y_prev, u_current, 0);
    double result2 = computeNonlinearModel(y, y_prev, u_current, M_PI/2); // sin(π/2) = 1
    double result3 = computeNonlinearModel(y, y_prev, u_current, M_PI);   // sin(π) = 0
    
    EXPECT_NE(result1, result2);
    EXPECT_NE(result1, result3);
    EXPECT_NE(result2, result3);
}

TEST(NonLinearModelTest, QuadraticTermEffect) {
    // Проверка квадратичного члена
    double y = 2;
    double u_current = 1;
    double u_prev = 1;
    
    // При разных предыдущих температурах результат должен отличаться
    double result1 = computeNonlinearModel(y, 1, u_current, u_prev);  // y_prev = 1
    double result2 = computeNonlinearModel(y, 2, u_current, u_prev);  // y_prev = 2
    double result3 = computeNonlinearModel(y, 3, u_current, u_prev);  // y_prev = 3
    
    EXPECT_NE(result1, result2);
    EXPECT_NE(result1, result3);
    EXPECT_NE(result2, result3);
}

TEST(NonLinearModelTest, CombinedEffects) {
    // Комплексный тест со всеми компонентами
    double y = 3.0;
    double y_prev = 2.0;
    double u_current = 1.5;
    double u_prev = 0.8;
    
    double expected = NONLINEAR_A * y 
                     - NONLINEAR_B * std::pow(y_prev, 2)
                     + NONLINEAR_C * u_current 
                     + NONLINEAR_D * std::sin(u_prev);
    
    EXPECT_NEAR(computeNonlinearModel(y, y_prev, u_current, u_prev), 
                expected, 1e-12);
}

TEST(ConstantsTest, VerifyConstantValues) {
    // Проверка значений констант
    EXPECT_DOUBLE_EQ(LINEAR_A, 0.9);
    EXPECT_DOUBLE_EQ(LINEAR_B, 0.01);
    EXPECT_DOUBLE_EQ(NONLINEAR_A, 0.9);
    EXPECT_DOUBLE_EQ(NONLINEAR_B, 0.01);
    EXPECT_DOUBLE_EQ(NONLINEAR_C, 0.15);
    EXPECT_DOUBLE_EQ(NONLINEAR_D, 0.05);
    EXPECT_DOUBLE_EQ(ZERO_PREV_INPUT, 0.0);
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

**Вывод:** В ходе лабораторнойё работы были разработаны и выполнены модульные тесты для линейной и нелинейной функций с использованием фреймворка Google Test.
Все тесты успешно прошли, что подтвердило корректность реализованных алгоритмов.
Анализ покрытия кода с помощью OpenCppCoverage показал общее покрытие около 26%, при этом пользовательские функции протестированы полностью.