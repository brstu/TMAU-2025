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
<p align="right">Батулин М.</p>
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

### Сборка и запуск

#### Сборка программы
```bash
cd src
mkdir build
cd build
cmake ..
make
./Modeling_as06602
```

#### Сборка и запуск тестов
```bash
cd test
mkdir build
cd build
cmake ..
make
./ModelTests
```

### Результаты тестирования

Running main() from /tmp/googletest-20250207-4735-e28tfc/googletest-1.16.0/googletest/src/gtest_main.cc
[==========] Running 12 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 12 tests from ModelTest
[ RUN      ] ModelTest.LinearModelBasicCalculation
[       OK ] ModelTest.LinearModelBasicCalculation (0 ms)
[ RUN      ] ModelTest.LinearModelZeroValues
[       OK ] ModelTest.LinearModelZeroValues (0 ms)
[ RUN      ] ModelTest.LinearModelNegativeValues
[       OK ] ModelTest.LinearModelNegativeValues (0 ms)
[ RUN      ] ModelTest.NonlinearModelBasicCalculation
[       OK ] ModelTest.NonlinearModelBasicCalculation (0 ms)
[ RUN      ] ModelTest.NonlinearModelZeroValues
[       OK ] ModelTest.NonlinearModelZeroValues (0 ms)
[ RUN      ] ModelTest.NonlinearModelSinZero
[       OK ] ModelTest.NonlinearModelSinZero (0 ms)
[ RUN      ] ModelTest.SimulateLinearSingleStep
[       OK ] ModelTest.SimulateLinearSingleStep (0 ms)
[ RUN      ] ModelTest.SimulateLinearMultipleSteps
[       OK ] ModelTest.SimulateLinearMultipleSteps (0 ms)
[ RUN      ] ModelTest.SimulateNonlinearSingleStep
[       OK ] ModelTest.SimulateNonlinearSingleStep (0 ms)
[ RUN      ] ModelTest.SimulateNonlinearMultipleSteps
[       OK ] ModelTest.SimulateNonlinearMultipleSteps (0 ms)
[ RUN      ] ModelTest.SimulateLinearEdgeCaseNZero
[       OK ] ModelTest.SimulateLinearEdgeCaseNZero (35 ms)
[ RUN      ] ModelTest.SimulateNonlinearEdgeCaseNZero
[       OK ] ModelTest.SimulateNonlinearEdgeCaseNZero (14 ms)
[----------] 12 tests from ModelTest (50 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 1 test suite ran. (50 ms total)
[  PASSED  ] 12 tests.

### Покрытие кода

Для генерации отчета о покрытии кода использовался инструмент gcovr.

```bash
gcovr -r . --html --html-details -o coverage.html
```

Отчет о покрытии:

```
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/model.cpp                                34      34   100%   
------------------------------------------------------------------------------
TOTAL                                        34      34   100%
------------------------------------------------------------------------------
```

Процент покрытия кода тестами: 100%
```