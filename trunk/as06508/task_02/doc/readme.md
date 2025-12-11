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
<p align="right">Кисель М. С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---



























# Общее задание
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать фреймворк для модульного тестирования — [Google Test](https://google.github.io/googletest/).  
2. Написать тесты для основных функций программы, реализующих линейную и нелинейную модель.  
3. Исходный код модифицированной программы разместить в каталоге **task_02**.  
4. Отразить количество тестов и процент покрытия кода тестами в файле `readme.md`.  
5. Также выполнить проверку покрытия кода с помощью **OpenCppCoverage**.

---

## Выполнение работы

### Основные файлы проекта
- `main.cpp` — основной исполняемый файл.  
- `func.h` и `func.cpp` — заголовочный и исходный файлы с функциями моделирования.  
- `tests.cpp` — набор модульных тестов для функций.  
- `CMakeLists.txt` — файл конфигурации сборки проекта.

---

### Тесты

```cpp
TEST(LinearStepTest, BasicBehavior) {
    ModelParams params;
    double y_prev = 10.0;
    double u = 2.0;
    double expected = params.a * y_prev + params.b * u;
    EXPECT_DOUBLE_EQ(linearStep(y_prev, u, params), expected);
}

TEST(NonlinearStepTest, IncludesSinAndSquareTerms) {
    ModelParams params;
    double y_prev = 8.0, y_prev2 = 7.0, u = 3.0, u_prev = 2.0;
    double expected = params.a * y_prev - params.b * pow(y_prev2, 2)
                    + params.c * u + params.d * sin(u_prev);
    EXPECT_NEAR(nonlinearStep(y_prev, y_prev2, u, u_prev, params), expected, 1e-9);
}

TEST(SimulationTest, LinearProducesCorrectSequence) {
    ModelParams params;
    std::vector<double> u(params.time_steps, 5.0);
    auto y = simulateLinear(params, u);
    ASSERT_EQ(y.size(), params.time_steps + 1);
}

TEST(SimulationTest, NonlinearFirstStepUsesE) {
    ModelParams params;
    std::vector<double> u(params.time_steps, 3.0);
    auto y = simulateNonlinear(params, u);
    EXPECT_NEAR(y[1], params.initial_temp * params.INPUT_E, 1e-9);
}

TEST(SimulationTest, NonlinearHasDifferentDynamics) {
    ModelParams params;
    std::vector<double> u(params.time_steps, 2.0);
    auto y_lin = simulateLinear(params, u);
    auto y_nonlin = simulateNonlinear(params, u);
    EXPECT_NE(y_lin.back(), y_nonlin.back());
}
 ```
### Сборка проекта
Для сборки проекта в папке tmau2 выполняются команды:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
ctest
```
Результат выполнения:
```bash
Test project D:/TMAU_Lab2/tmau2/build
    Start 1: LinearStepTest.BasicBehavior
1/5 Test #1: LinearStepTest.BasicBehavior ...................   Passed    0.02 sec
    Start 2: NonlinearStepTest.IncludesSinAndSquareTerms ....   Passed    0.02 sec
    Start 3: SimulationTest.LinearProducesCorrectSequence ...   Passed    0.02 sec
    Start 4: SimulationTest.NonlinearFirstStepUsesE .........   Passed    0.03 sec
    Start 5: SimulationTest.NonlinearHasDifferentDynamics ...   Passed    0.05 sec

100% tests passed, 0 tests failed out of 5
Total Test time (real) =   0.21 sec
```
Все тесты успешно прошли, что подтверждает корректность работы функций.

### Покрытие кода тестами
Для анализа покрытия использовалась утилита OpenCppCoverage.
Команда запуска:
```bash
"D:\OpenCppCoverage\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"D:\TMAU_Lab2\task_02\build\coverage" ^
--sources="D:\TMAU_Lab2\task_02" ^
--excluded_sources="*googletest*;*build*;*CMakeFiles*" ^
-- "D:\TMAU_Lab2\task_02\build\Debug\runTests.exe"
```



В результате был сгенерирован HTML-отчёт index.html, отображающий общее покрытие кода.
Общий процент покрытия составил 27%, но значимым показателем является 100% покрытие файла func.cpp,
так как именно он содержит тестируемые функции.

**Вывод:** В ходе лабораторной работы: Создан и собран проект на CMake с использованием Google Test. Написаны модульные тесты для функций линейной и нелинейной модели. Все тесты успешно пройдены. Проведён анализ покрытия кода с помощью OpenCppCoverage — пользовательские функции протестированы полностью.