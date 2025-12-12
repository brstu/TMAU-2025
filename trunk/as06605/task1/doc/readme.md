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
<p align="right">Группы АС-66</p>
<p align="right">Горобец А.В.</p>
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
const double a = 0.1;
const double b = 0.2;
const double c = 0.3;
const double d = 0.4;
const double InpTemp = 20;
const int iterations = 50;
```
Имея данные параметры получим результат работы программы:
```bash
i       Линейная        Нелинейная
0       20              20
1       6               0
2       4.6             -73.94
3       4.46            -1.33405
4       4.446           -1087.5
5       4.4446          -103.046
6       4.44446         -236535
7       4.44445         -25771.2
8       4.44444         -1.11898e+10
9       4.44444         -1.25181e+09
10      4.44444         -2.50423e+19
11      4.44444         -2.81764e+18
12      4.44444         -1.25423e+38
13      4.44444         -1.41302e+37
14      4.44444         -3.14621e+75
15      4.44444         -3.54553e+74
16      4.44444         -1.97972e+150
17      4.44444         -2.23114e+149
18      4.44444         -7.8386e+299
19      4.44444         -8.83419e+298
20      4.44444         -inf
21      4.44444         -inf
22      4.44444         -inf
23      4.44444         -inf
24      4.44444         -inf
25      4.44444         -inf
26      4.44444         -inf
27      4.44444         -inf
28      4.44444         -inf
29      4.44444         -inf
30      4.44444         -inf
31      4.44444         -inf
32      4.44444         -inf
33      4.44444         -inf
34      4.44444         -inf
35      4.44444         -inf
36      4.44444         -inf
37      4.44444         -inf
38      4.44444         -inf
39      4.44444         -inf
40      4.44444         -inf
41      4.44444         -inf
42      4.44444         -inf
43      4.44444         -inf
44      4.44444         -inf
45      4.44444         -inf
46      4.44444         -inf
47      4.44444         -inf
48      4.44444         -inf
49      4.44444         -inf
```
**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.
