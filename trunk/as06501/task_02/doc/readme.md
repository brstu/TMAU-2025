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
<p align="right">Вавдийчик Н.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание #
Написать модульные тесты для программы, разработанной в лабораторной работе №1.

1. Использовать следующий фреймворк для модульного тестирования - [Google Test](https://google.github.io/googletest/).  
2. Написать модульные тесты для основных функций программы. Разместить тесты в каталоге: **trunk\as0xxyy\task_02\test**.  
3. Исходный код модифицированной программы разместить в каталоге: **trunk\as0xxyy\task_02\src**.  
4. В файле `readme.md` отразить количество написанных тестов и процент покрытия кода тестами (использовать любой инструмент для анализа покрытия, например, [OpenCppCoverage](https://opencppcoverage.codeplex.com/)).  
5. Также необходимо отразить выполнение работы в общем файле [`readme.md`](https://github.com/brstu/TMAU-2025/blob/main/README.md) в соответствующей строке.  

---

## Ход работы

### Тесты программы(tests.cpp)
```cpp
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linear(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linear(10, 0), a * 10);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linear(0, 5), b * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linear(10, 4), a * 10 + b * 4);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(nonlinear(10, 10, 0, 0), a * 10 - b * pow(10, 2));
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(nonlinear(0, 0, 4, 4), c * 4 + d * sin(4));
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinear(10, 10, 4, 4),
        a * 10 - b * pow(10, 2) + c * 4 + d * sin(4)
    );
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
[----------] 4 tests from LinearModel (1 ms total)

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
[==========] 8 tests from 2 test suites ran. (4 ms total)
[  PASSED  ] 8 tests.
``` 

Для анализа покрытия использовался инструмент OpenCppCoverage.
Запуск выполнялся следующей командой:
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\TMAU\task_02\coverage" ^
--sources="E:\TMAU\task_02\src" ^
-- "E:\TMAU\task_02\src\build\Debug\task02_tests.exe"

Результаты покрытия кода тестами:

Общее покрытие проекта: ~27–30%

Покрытие пользовательского файла func.cpp: 100%

Вывод:В ходе выполнения лабораторной работы были написаны модульные тесты для функций:linearModel|nonlinearModelВсе тесты завершились успешно, что подтверждает корректность реализованных моделей.Покрытие кода показывает, что пользовательские функции протестированы полностью, а непокрытые участки приходятся на ввод/вывод в main.cpp, что является нормальным для модульного тестирования.
