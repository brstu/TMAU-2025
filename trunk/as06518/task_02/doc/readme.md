<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №2</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Тестирование программы и процент покрытия тестами”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Степанова Д.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание #
Написать модульные тесты для программы, разработанной в Лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.  
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [OpenCppCoverage](https://opencppcoverage.codeplex.com/)).  
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.  

---

## Для проверки корректности функций linearModel и nonlinearModel были созданы восемь тестов.
## Каждый тест охватывает отдельную ситуацию использования модели — нулевые входы, влияние одного аргумента, а также комбинацию всех параметров.

### Сами тесты:
```cpp
#include <gtest/gtest.h>
#include "func.h"

TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18, 0), PARAM_A * 18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), PARAM_B * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), PARAM_A * 18 + PARAM_B * 5);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 0, 0),
        PARAM_A * 18 - PARAM_B * pow(18, 2)
    );
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 0, 5, 5),
        PARAM_C * 5 + PARAM_D * sin(5)
    );
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 5, 5),
        PARAM_A * 18 - PARAM_B * pow(18, 2) +
        PARAM_C * 5 + PARAM_D * sin(5)
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```

```bash
[==========] Running 8 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearModel
[ RUN      ] LinearModel.ZeroInput
[       OK ] LinearModel.ZeroInput (0 ms)
[ RUN      ] LinearModel.OnlyY
[       OK ] LinearModel.OnlyY (0 ms)
[ RUN      ] LinearModel.OnlyU
[       OK ] LinearModel.OnlyU (0 ms)
[ RUN      ] LinearModel.GeneralCase
[       OK ] LinearModel.GeneralCase (0 ms)
[----------] 4 tests from LinearModel (2 ms total)

[----------] 4 tests from NonlinearModel
[ RUN      ] NonlinearModel.ZeroInput
[       OK ] NonlinearModel.ZeroInput (0 ms)
[ RUN      ] NonlinearModel.OnlyY
[       OK ] NonlinearModel.OnlyY (0 ms)
[ RUN      ] NonlinearModel.OnlyU
[       OK ] NonlinearModel.OnlyU (0 ms)
[ RUN      ] NonlinearModel.GeneralCase
[       OK ] NonlinearModel.GeneralCase (0 ms)
[----------] 4 tests from NonlinearModel (1 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 2 test suites ran. (5 ms total)
[  PASSED  ] 8 tests.
``` 

Покрытие кода тестами.
Для анализа покрытия использовался инструмент OpenCppCoverage. Запуск выполнялся командой:

```bash
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\TMAU\task_02\coverage" ^
--sources="E:\TMAU\task_02\src" ^
-- "E:\TMAU\task_02\src\build\Debug\runTests.exe"
```
Общее покрытие проекта: ~26%

Покрытие пользовательского файла func.cpp: 100%

Таким образом, обе функции, реализованные в рамках лабораторной работы, полностью охвачены тестами, что подтверждает корректность их работы на проверяемых наборах входных данных.

Вывод: В процессе выполнения работы были: написаны и добавлены модульные тесты для функций математической модели, проведён запуск тестов и подтверждена корректность работы программы, выполнено измерение покрытия кода, достигнуто 100% покрытие пользовательских функций
