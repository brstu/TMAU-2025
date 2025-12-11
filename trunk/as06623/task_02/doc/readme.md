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
<p align="right">Цеван К.А</p>
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
TEST(SimulateLinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = simulateLinear(u);
    EXPECT_EQ(result.size(), iterationsCount);
}

TEST(SimulateNonlinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = simulateNonlinear(u);
    EXPECT_EQ(result.size(), iterationsCount);
}

TEST(SimulateLinearTest, ValuesAreCorrect) {
    double u = 5.0;
    std::vector<double> expected(iterationsCount);
    expected[0] = initialTemperature;
    for (int i = 0; i < iterationsCount - 1; ++i) {
        expected[i + 1] = coeffA * expected[i] + coeffB * u;
    }

    std::vector<double> result = simulateLinear(u);
    ASSERT_EQ(result.size(), expected.size());
    for (int i = 0; i < iterationsCount; ++i) {
        EXPECT_NEAR(result[i], expected[i], 1e-6);
    }
}
 ```
Сборка проекта при помощи cmake
Для сборки проекта в папке src необходимо произвести следующие действия:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
ctest
```
Результаты тестов(3 штуки):
```bash
Test project B:/tmau2/lab2/src/build
    Start 1: SimulateLinearTest.ReturnsCorrectSize
1/3 Test #1: SimulateLinearTest.ReturnsCorrectSize ......   Passed    0.01 sec
    Start 2: SimulateLinearTest.ValuesAreCorrect
2/3 Test #2: SimulateLinearTest.ValuesAreCorrect ........   Passed    0.01 sec
    Start 3: SimulateNonlinearTest.ReturnsCorrectSize
3/3 Test #3: SimulateNonlinearTest.ReturnsCorrectSize ...   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.02 sec

```

Процент покрытия тестов
Для проверки покрытия кода тестами использовалась программа OpenCppCoverage.
Для запуска тестов  использовался скрипт 
```bash
"C:\TMAU-2025\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"C:\TMAU-2025\trunk\as06623\task_02\coverage" ^
--sources="C:\TMAU-2025\trunk\as06623\task_02\src" ^
-- "C:\TMAU-2025\trunk\as06623\task_02\src\build\Debug\runTests.exe"
В результате тестирования был сформирован файл index.html, содержащий отчёт о покрытии кода. Общий уровень покрытия составляет 26%, однако в этот показатель входят также файлы сторонних библиотек, которые не являются объектом тестирования. Файл model.cpp имеет 100% покрытие, что подтверждает полное тестирование пользовательских функций.

В процессе работы были разработаны модульные тесты для функций simulateLinear() и simulateNonlinear() с использованием фреймворка Google Test. Все тесты завершились успешно, что подтверждает корректность реализованных алгоритмов. Согласно анализу покрытия кода с помощью OpenCppCoverage, пользовательские функции охвачены тестами полностью.