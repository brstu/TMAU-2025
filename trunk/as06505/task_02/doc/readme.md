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
<p align="right">Сергиевич М.А.</p>
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

## Выполнение задания 2
Проведение модульного тестирования

Для проверки корректности функций линейной и нелинейной моделей были разработаны и выполнены модульные тесты на базе GoogleTest.
Набор тестов охватывает граничные случаи, изолированные проверки отдельных параметров, а также комбинированные сценарии вычислений.

Ниже представлена итоговая версия тестов:
```cpp
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18, 0), A * 18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0, 5), B * 5);
}

TEST(LinearModel, MixedValues) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), A * 18 + B * 5);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 0, 0), 0);
}

TEST(NonlinearModel, InfluenceOfY) {
    EXPECT_DOUBLE_EQ(nonlinearModel(18, 18, 0, 0),
                     A * 18 - B * pow(18, 2));
}

TEST(NonlinearModel, InfluenceOfU) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 5, 5),
                     C * 5 + D * sin(5));
}

TEST(NonlinearModel, CombinedEffect) {
    EXPECT_DOUBLE_EQ(nonlinearModel(18, 18, 5, 5),
                     A * 18 - B * pow(18, 2) + C * 5 + D * sin(5));
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
[----------] 4 tests from LinearModel (7 ms total)

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
[==========] 8 tests from 2 test suites ran. (14 ms total)
[  PASSED  ] 8 tests.
``` 

Покрытие кода тестами
Для анализа покрытия использовался инструмент OpenCppCoverage. Запуск выполнялся командой:

```bash
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\TMAU\task_02\coverage" ^
--sources="E:\TMAU\task_02\src" ^
-- "E:\TMAU\task_02\src\build\Debug\runTests.exe"
```

Общее покрытие проекта	около 26%
Файл func.cpp	100%

Поскольку остальная часть проекта включает служебный код, сборочные файлы и стандартные библиотеки, высокий процент покрытия именно пользовательских функций указывает на качественное тестирование ключевой логики.

Вывод: В рамках выполнения задания были разработаны тесты для двух математических моделей. Все тестовые сценарии показали корректность работы функций. Проверка покрытия подтвердила, что весь функционал, реализованный в func.cpp, охвачен тестами полностью. Это говорит о надёжности и правильности реализации алгоритмов в лабораторной работе.
