<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Кисель М.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Выполнение работы
Константы  
```
const double INPUT_OFFSET = 10.0;
const double INPUT_AMPLITUDE = 2.0;
const double INPUT_FREQUENCY = 0.5;
const double INPUT_E = 0.95;
const double a = 0.85;
const double b = 0.002;
const double c = 0.6;
const double d = 0.025;
int time_steps = 10;
double initial_temp = 24.0;
```
Имея такие константы мы сможем получить такой результат работы программы:

Linear Model Results:
Time    Temperature
----------------
0       24
1       20.42
2       17.3789
3       14.7954
4       12.6001
5       10.7337
6       9.14607
7       7.79473
8       6.64411
9       5.66447
10      4.83089

Nonlinear Model Results:
Time    Temperature
----------------
0       24
1       22.8
2       24.7897
3       27.0164
4       28.9125
5       30.1935
6       30.6938
7       30.4113
8       29.5255
9       28.342
10      27.1943
```
**Вывод:** Если мы знаем функцию, то мы можем моделировать параметры модели в зависимости от времени.
