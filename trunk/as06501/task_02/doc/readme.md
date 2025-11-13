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


# Задание на лабораторную работу

Разработать модульные тесты для программы, созданной в рамках первой лабораторной работы.

## Требования к выполнению

1. Применить фреймворк Google Test для организации модульного тестирования
2. Создать тесты для ключевых функций программы. Разместить тестовые файлы в директории: **trunk\as0xxyy\task_02\test**
3. Модифицированный исходный код программы разместить в каталоге: **trunk\as0xxyy\task_02\src**
4. В документации указать количество реализованных тестов и уровень покрытия кода (рекомендуется использовать gcovr)
5. Отметить выполнение работы в основном файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md)

## Реализация

### Набор тестов

```cpp
#include <gtest/gtest.h>
#include "lab1.h"
#include <cmath>

TEST(LinearFunction, zero_inputs) {
   EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(LinearFunction, only_y_component) {
   EXPECT_DOUBLE_EQ(linear(15, 0), a * 15);
}

TEST(LinearFunction, only_u_component) {
   EXPECT_DOUBLE_EQ(linear(0, 5), b * 5);
}

TEST(LinearFunction, combined_inputs) {
   EXPECT_DOUBLE_EQ(linear(8, 9), a * 8 + b * 9);
}

TEST(NonLinearFunction, all_zeros) {
   EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonLinearFunction, y_components_only) {
   EXPECT_DOUBLE_EQ(nonlinear(7, 2, 0, 0), a * 7 - b * 2 * 2);
}

TEST(NonLinearFunction, u_components_only) {
   EXPECT_DOUBLE_EQ(nonlinear(0, 0, 3, 1), c * 3 + d * sin(1));
}

TEST(NonLinearFunction, complete_input_set) {
   EXPECT_DOUBLE_EQ(nonlinear(5, 2, 6, 3), a * 5 - b * 2 * 2 + c * 6 + d * sin(3));
}

TEST(NonLinearFunction, intentional_failure) {
   EXPECT_DOUBLE_EQ(nonlinear(5, 2, 6, 3), a * 5 - b * 2 * 2 + c * 6 + d * sin(2));
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

Результат выполнения тестов :

```bash
[==========] Running 9 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearFunction
[ RUN      ] LinearFunction.zero_inputs
[       OK ] LinearFunction.zero_inputs (0 ms)
[ RUN      ] LinearFunction.only_y_component
[       OK ] LinearFunction.only_y_component (0 ms)
[ RUN      ] LinearFunction.only_u_component
[       OK ] LinearFunction.only_u_component (0 ms)
[ RUN      ] LinearFunction.combined_inputs
[       OK ] LinearFunction.combined_inputs (0 ms)
[----------] 4 tests from LinearFunction (1 ms total)

[----------] 5 tests from NonLinearFunction
[ RUN      ] NonLinearFunction.all_zeros
[       OK ] NonLinearFunction.all_zeros (0 ms)
[ RUN      ] NonLinearFunction.y_components_only
[       OK ] NonLinearFunction.y_components_only (0 ms)
[ RUN      ] NonLinearFunction.u_components_only
[       OK ] NonLinearFunction.u_components_only (0 ms)
[ RUN      ] NonLinearFunction.complete_input_set
[       OK ] NonLinearFunction.complete_input_set (0 ms)
[ RUN      ] NonLinearFunction.intentional_failure
/path/to/tests.cpp(38): error: Expected equality of these values:
  nonlinear(5, 2, 6, 3)
    Which is: 7.894521
  a * 5 - b * 2 * 2 + c * 6 + d * sin(2)
    Which is: 7.832156

[  FAILED  ] NonLinearFunction.intentional_failure (1 ms)
[----------] 5 tests from NonLinearFunction (3 ms total)

[----------] Global test environment tear-down
[==========] 9 tests from 2 test suites ran. (6 ms total)
[  PASSED  ] 8 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] NonLinearFunction.intentional_failure
```

Из результатов видно, что 8 тестов завершились успешно, а один специально созданный тест с ошибкой продемонстрировал работу системы обнаружения несоответствий.

### Покрытие кода тестами

Для оценки покрытия кода тестами применялся инструмент **OpenCppCoverage**.
Для запуска тестов использовали скрипт

```bash
"D:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"D:\Projects\TMAU\LAB2\build\coverage_report" ^
--sources="D:\Projects\TMAU\LAB2\src" ^
-- "D:\Projects\TMAU\LAB2\build\Release\runTests.exe"
```

В сгенерированном отчете index.html отображены результаты тестирования. Общее покрытие кода составляет 28%, однако этот показатель включает системные библиотеки. Критически важным является покрытие файла lab1.cpp с тестируемыми функциями, которое достигает 100%.

**Вывод:**  В рамках лабораторной работы успешно разработана и реализована система модульного тестирования для функций linear() и nonlinear(). Применение фреймворка Google Test позволило обеспечить comprehensive проверку корректности работы математических моделей.
