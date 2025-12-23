<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнила:</p>
<p align="right">Студентка 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Занько Я.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Выполнение работы
__Константы:__
```cpp
const int N = 30;
const double a = 0.9;
const double b = 0.02;
const double c = 0.03;
const double d = 0.1;
```

__Результаты моделирования:__
```bash
t       Linear y        Nonlinear y
------------------------------------
0       0.000000        0.000000
1       0.020000        0.000000
2       0.038000        0.114147
3       0.054200        0.216879
4       0.068780        0.309078
5       0.081902        0.391377
6       0.093712        0.464475
7       0.104341        0.529111
8       0.113907        0.586033
9       0.122516        0.635977
10      0.130264        0.679658
11      0.137238        0.717750
12      0.143514        0.750883
13      0.149163        0.779639
14      0.154246        0.804546
15      0.158822        0.826081
16      0.162940        0.844674
17      0.166646        0.860706
18      0.169981        0.874513
19      0.172983        0.886392
20      0.175685        0.896605
21      0.178116        0.905378
22      0.180305        0.912909
23      0.182274        0.919371
24      0.184047        0.924913
25      0.185642        0.929664
26      0.187078        0.933735
27      0.188370        0.937223
28      0.189533        0.940211
29      0.190580        0.942769
30      0.191522        0.944959
```

---
__Вывод:__ в ходе лабораторной работы была реализована имитационная модель управляемого объекта по линейному и нелинейному уравнениям.
