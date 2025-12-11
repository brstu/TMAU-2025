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
<p align="right">Горобец А.В.</p>
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
TEST(LinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = linear(u);
    EXPECT_EQ(result.size(), iterations);
}

TEST(NonlinearTest, ReturnsCorrectSize) {
    double u = 5.0;
    std::vector<double> result = nonlinear(u);
    EXPECT_EQ(result.size(), iterations);
}

TEST(LinearTest, ValuesAreCorrect) {
    double u = 5.0;
    std::vector<double> expected(iterations);
    expected[0] = InpTemp;
    for (int i = 0; i < iterations - 1; ++i) {
        expected[i + 1] = a * expected[i] + b * u;
    }

    std::vector<double> result = linear(u);
    ASSERT_EQ(result.size(), expected.size());
    for (int i = 0; i < iterations; ++i) {
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
B:\tmau2\asd\src\build>ctest
Test project B:/tmau2/asd/src/build
    Start 1: LinearTest.ReturnsCorrectSize
1/3 Test #1: LinearTest.ReturnsCorrectSize ......   Passed    0.01 sec
    Start 2: LinearTest.ValuesAreCorrect
2/3 Test #2: LinearTest.ValuesAreCorrect ........   Passed    0.01 sec
    Start 3: NonlinearTest.ReturnsCorrectSize
3/3 Test #3: NonlinearTest.ReturnsCorrectSize ...   Passed    0.01 sec

100% tests passed, 0 tests failed out of 3

Total Test time (real) =   0.02 sec
```

Процент покрытия тестов
Для проверки покрытия кода тестами использовалась программа OpenCppCoverage.
Для запуска тестов использовали скрипт 
```bash
"B:\tmau2\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"B:\tmau2\asd\coverage" ^
--sources="B:\tmau2\asd\src" ^
-- "B:\tmau2\asd\src\build\Debug\as06605_tests.exe"
```
В результате тестирования был сформирован файл index.html, содержащий отчёт о покрытии кода. Общий уровень покрытия составляет 26%, однако в этот показатель входят также файлы сторонних библиотек, которые не являются объектом тестирования. function.cpp имеет 100% покрытие.

В процессе работы были разработаны модульные тесты для функций linear() и nonlinear() с использованием фреймворка Google Test. Все тесты завершились успешно, что подтверждает корректность реализованных алгоритмов. Согласно анализу покрытия кода с помощью OpenCppCoverage, общее покрытие составило около 26%, при этом пользовательские функции охвачены тестами полностью.