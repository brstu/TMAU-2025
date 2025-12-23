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
<p align="right">Лопато А.В.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---

# Общее задание #
Модульное тестирование (Google Test)
Общее задание
В рамках лабораторной работы №2 были разработаны модульные тесты для программы, реализованной в лабораторной работе №1. Для модульного тестирования использовался фреймворк Google Test.  

Тестируемые функции

В ходе работы были протестированы следующие функции:

linearModel(double y, double u)

nonlinearModel(double y, double yPrev, double u, double uPrev)

---

## Выполнение задания №2

## Реализованные тесты
Линейная модель
```
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18, 0), kA * 18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), kB * 5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), kA * 18 + kB * 5);
}
```
Нелинейная модель
```
TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, OnlyYPrev) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 4, 0, 0),
        kB * pow(4, 2)
    );
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(0, 0, 6, 6),
        kC * 6 + kD * sin(6)
    );
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(
        nonlinearModel(18, 18, 5, 5),
        kA * 18 + kB * pow(18, 2) + kC * 5 + kD * sin(5)
    );
}

```
## Результаты выполнения тестов

Результат запуска модульных тестов:

```[==========] Running 8 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 4 tests from LinearModel
[ RUN      ] LinearModel.ZeroInput
[       OK ] LinearModel.ZeroInput
[ RUN      ] LinearModel.OnlyY
[       OK ] LinearModel.OnlyY
[ RUN      ] LinearModel.OnlyU
[       OK ] LinearModel.OnlyU
[ RUN      ] LinearModel.GeneralCase
[       OK ] LinearModel.GeneralCase
[----------] 4 tests from LinearModel

[----------] 4 tests from NonlinearModel
[ RUN      ] NonlinearModel.ZeroInput
[       OK ] NonlinearModel.ZeroInput
[ RUN      ] NonlinearModel.OnlyYPrev
[       OK ] NonlinearModel.OnlyYPrev
[ RUN      ] NonlinearModel.OnlyU
[       OK ] NonlinearModel.OnlyU
[ RUN      ] NonlinearModel.GeneralCase
[       OK ] NonlinearModel.GeneralCase
[----------] 4 tests from NonlinearModel

[==========] 8 tests from 2 test suites ran.
[  PASSED  ] 8 tests.
``` 
Всего тестов: 8
Успешно пройдено: 8
Ошибок: 0

Покрытие кода тестами

Для анализа покрытия кода использовался инструмент OpenCppCoverage.

```bash
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\TMAU\task_02\coverage" ^
--sources="E:\TMAU\task_02\src" ^
-- "E:\TMAU\task_02\src\build\Debug\runTests.exe"
```

Результаты покрытия
Общее покрытие проекта (с учётом библиотек): ~25–30%
Покрытие пользовательского файла func.cpp: 100%

Вывод: В ходе выполнения лабораторной работы были разработаны и успешно выполнены модульные тесты для функций линейной и нелинейной моделей. Все тесты завершились без ошибок. Анализ покрытия показал, что пользовательский код протестирован полностью, что подтверждает корректность реализации основных вычислительных алгоритмов.
