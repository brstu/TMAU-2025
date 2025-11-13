<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Модульное тестирование”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Вавдийчик Н.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание

Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [gcovr](https://gcovr.com/en/stable/)).
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.

## Выполнение работы

### Тесты

```cpp

#include <gtest/gtest.h>
#include "lab1.h"
#include <cmath>

TEST(LinearModel, linear_all_zero) {
   EXPECT_EQ(linear(0, 0), 0);
}

TEST(LinearModel, linear_y_only) {
   EXPECT_EQ(linear(10, 0), a * 10);
}

TEST(LinearModel, linear_u_only) {
   EXPECT_EQ(linear(0, 7), b * 7);
}

TEST(LinearModel, linear_general_case) {
   EXPECT_EQ(linear(10, 7), a * 10 + b * 7);
}

TEST(NonLinearModel, nonlinear_all_zero) {
   EXPECT_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinearModel, nonlinear_y_terms) {
   EXPECT_EQ(nonlinear(6, 3, 0, 0), a * 6 - b * 3 * 3);
}

TEST(NonLinearModel, nonlinear_u_terms) {
   EXPECT_EQ(nonlinear(0, 0, 4, 2), c * 4 + d * sin(2));
}

TEST(NonLinearModel, nonlinear_full_case) {
   EXPECT_EQ(nonlinear(6, 3, 4, 2), a * 6 - b * 3 * 3 + c * 4 + d * sin(2));
}

TEST(NonLinearModel, nonlinear_fail_test) {
   EXPECT_EQ(nonlinear(6, 3, 4, 2), a * 6 - b * 3 * 3 + c * 4 + d * sin(3));
}

int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}

```

### Сборка проекта

Для сборки проекта в папке _src_ необходимо произвести следующие действия:

```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug
ctest
```

Таким образом в итоге получим :

```bash
[==========] Running 9 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearModel
[ RUN      ] LinearModel.linear_all_zero
[       OK ] LinearModel.linear_all_zero (0 ms)
[ RUN      ] LinearModel.linear_y_only
[       OK ] LinearModel.linear_y_only (0 ms)
[ RUN      ] LinearModel.linear_u_only
[       OK ] LinearModel.linear_u_only (0 ms)
[ RUN      ] LinearModel.linear_general_case
[       OK ] LinearModel.linear_general_case (0 ms)
[----------] 4 tests from LinearModel (2 ms total)

[----------] 5 tests from NonLinearModel
[ RUN      ] NonLinearModel.nonlinear_all_zero
[       OK ] NonLinearModel.nonlinear_all_zero (0 ms)
[ RUN      ] NonLinearModel.nonlinear_y_terms
[       OK ] NonLinearModel.nonlinear_y_terms (0 ms)
[ RUN      ] NonLinearModel.nonlinear_u_terms
[       OK ] NonLinearModel.nonlinear_u_terms (0 ms)
[ RUN      ] NonLinearModel.nonlinear_full_case
[       OK ] NonLinearModel.nonlinear_full_case (0 ms)
[ RUN      ] NonLinearModel.nonlinear_fail_test
D:\laba2tm\laba2tmay\laba2tmay\tests.cpp(38): error: Expected equality of these values:
  nonlinear(6, 3, 4, 2)
    Which is: 7.557743794146055
  a * 6 - b * 3 * 3 + c * 4 + d * sin(3)
    Which is: 7.4962896006447899

[  FAILED  ] NonLinearModel.nonlinear_fail_test (1 ms)
[----------] 5 tests from NonLinearModel (3 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 2 test suites ran. (7 ms total)
[  PASSED  ] 8 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] NonLinearModel.nonlinear_fail_test

 1 FAILED TEST
```

Как видим большинство тестов успешно пройдены и еще один специально созданный падающий тест выдал ошибку (так мы продемонстрировали работу системы).

### Покрытие кода тестами

Для проверки покрытия кода тестами использовали **OpenCppCoverage**.
Для запуска тестов использовали скрипт

```bash
"D:\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"D:\TMAU\LAB2\src\build\coverage" ^
--sources="D:\TMAU\LAB2\src" ^
-- "D:\TMAU\LAB2\src\build\Debug\runTests.exe"
```

Получили файл _index.html_, в котором отражены результаты тестирования. Общий процент покрытия кодом составляет 26%, но в него также включаются и файлы используемых библиотек. Так как они тестированию не подвергаются, значимым показателем будем считать процент покрытия тестами только для файла _lab1.cpp_, в котором содержаться тестируемые функции. Для данного файла процент покрытия составляет 100%

**Вывод:** В ходе работы были разработаны и выполнены модульные тесты для функций linear() и nonlinear() с использованием фреймворка Google Test.
