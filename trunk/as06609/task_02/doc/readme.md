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
<p align="right">Группы АС-66</p>
<p align="right">Куган Н.Л.</p>
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

### Тесты
```cpp
TEST(LinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(linearModel(0, 0), 0);
}

TEST(LinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(linearModel(18,0), A*18);
}

TEST(LinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(linearModel(0,5), B*5);
}

TEST(LinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(linearModel(18, 5), A*18 + B*5);
}

TEST(NonlinearModel, ZeroInput) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0,0,0,0), 0);
}

TEST(NonlinearModel, OnlyY) {
    EXPECT_DOUBLE_EQ(nonlinearModel(18,18,0,0), A*18 - B*pow(18,2));
}

TEST(NonlinearModel, OnlyU) {
    EXPECT_DOUBLE_EQ(nonlinearModel(0, 0, 5, 5), C*5 + D*sin(5));
}

TEST(NonlinearModel, GeneralCase) {
    EXPECT_DOUBLE_EQ(nonlinearModel(18, 18, 5, 5),
                     A*18 - B*pow(18,2) + C*5 + D*sin(5));
}
```

```bash
Test project E:/TMAU/task_02/src/build
    Start 1: LinearModel.ZeroInput
1/8 Test #1: LinearModel.ZeroInput ............   Passed
    Start 2: LinearModel.OnlyY
2/8 Test #2: LinearModel.OnlyY ................   Passed
    Start 3: LinearModel.OnlyU
3/8 Test #3: LinearModel.OnlyU ................   Passed
    Start 4: LinearModel.GeneralCase
4/8 Test #4: LinearModel.GeneralCase ..........   Passed
    Start 5: NonlinearModel.ZeroInput
5/8 Test #5: NonlinearModel.ZeroInput .........   Passed
    Start 6: NonlinearModel.OnlyY
6/8 Test #6: NonlinearModel.OnlyY .............   Passed
    Start 7: NonlinearModel.OnlyU
7/8 Test #7: NonlinearModel.OnlyU .............   Passed
    Start 8: NonlinearModel.GeneralCase
8/8 Test #8: NonlinearModel.GeneralCase .......   Passed

100% tests passed, 0 tests failed out of 8
``` 

Покрытие кода тестами
Для анализа покрытия использовался инструмент OpenCppCoverage. Запуск выполнялся командой:

```bash
"E:\Tools\OpenCppCoverage\OpenCppCoverage.exe" ^
--export_type=html:"E:\TMAU\task_02\coverage" ^
--sources="E:\TMAU\task_02\src" ^
-- "E:\TMAU\task_02\src\build\Debug\runTests.exe"
```
Результаты покрытия кода тестами:

Общее покрытие (с учётом библиотек): ~26%
Покрытие пользовательского файла func.cpp: 100%

Вывод: В ходе выполнения работы были написаны модульные тесты для функций linearModel и nonlinearModel. Все тесты прошли успешно, что подтверждает корректность реализованных алгоритмов. Покрытие кода показало, что пользовательские функции протестированы полностью.