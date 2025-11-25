
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
<p align="right">Гуща И.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
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
 ```cpp

TEST(Linear, test_zero) {
    EXPECT_EQ(linear(0,0), 0);
}

TEST(Linear, test_u_zero) {
    EXPECT_EQ(linear(18,0), a*18);
}

TEST(Linear, test_y_zero) {
    EXPECT_EQ(linear(0, 5), b * 5);
}

TEST(Linear, test_default) {
    EXPECT_EQ(linear(18, 5),a*18+ b * 5);
}

TEST(NonLinear, test_zero) {
    EXPECT_EQ(nonlinear(0,0,0,0), 0);
}

TEST(NonLinear, test_u_zero) {
    EXPECT_EQ(nonlinear(18, 18, 0, 0), a*18 - b * pow(18, 2));
}

TEST(NonLinear, test_y_zero) {
    EXPECT_EQ(nonlinear(0, 0, 5, 5), c * 5 + d * sin(5));
}

TEST(NonLinear, test_default) {
    EXPECT_EQ(nonlinear(18, 18, 5, 5), a * 18 - b * pow(18, 2)+c * 5 + d * sin(5));
}
 ```
### Сборка проекта
Для сборки проекта в папке *src* необходимо произвести следующие действия:
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
ctest
```
Таким образом в итоге получим :
```bash
Test project E:/ТиМАУ/Задание2/src/build
    Start 1: Linear.test_zero
1/8 Test #1: Linear.test_zero .................   Passed    0.01 sec
    Start 2: Linear.test_u0
2/8 Test #2: Linear.test_u0 ...................   Passed    0.01 sec
    Start 3: Linear.test_y0
3/8 Test #3: Linear.test_y0 ...................   Passed    0.01 sec
    Start 4: Linear.test_default
4/8 Test #4: Linear.test_default ..............   Passed    0.01 sec
    Start 5: NonLinear.test_zero
5/8 Test #5: NonLinear.test_zero ..............   Passed    0.01 sec
    Start 6: NonLinear.test_u0
6/8 Test #6: NonLinear.test_u0 ................   Passed    0.01 sec
    Start 7: NonLinear.test_y0
7/8 Test #7: NonLinear.test_y0 ................   Passed    0.01 sec
    Start 8: NonLinear.test_default
8/8 Test #8: NonLinear.test_default ...........   Passed    0.01 sec

100% tests passed, 0 tests failed out of 8

Total Test time (real) =   0.07 sec
```
Как видим все тесты успешно пройдены.

### Покрытие кода тестами
Для проверки покрытия кода тестами использовали **OpenCppCoverage**.
Для запуска тестов использовали скрипт 
```bash
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\ТиМАУ\Задание2\src\build\coverage" ^
--sources="E:\ТиМАУ\Задание2\src" ^
-- "E:\ТиМАУ\Задание2\src\build\Debug\runTests.exe"
```



Таким образом получили файл *index.html*, в котором отражены результаты тестирования. Общий процент покрытия кодом составляет 26%, но в него также включаются и файлы используемых библиотек. Так как они тестированию не подвергаются, значимым показателем будем считать процент покрытия тестами только для файла *func.cpp*, в котором содержаться тестируемые функции. Для данного файла процент покрытия составляет 100%

**Вывод:** В ходе работы были разработаны и выполнены модульные тесты для функций linear() и nonlinear() с использованием фреймворка Google Test.
Все тесты успешно прошли, что подтвердило корректность реализованных алгоритмов.
Анализ покрытия кода с помощью OpenCppCoverage показал общее покрытие около 26%, при этом пользовательские функции протестированы полностью.