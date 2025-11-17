<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский государственный технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине "Теория и методы автоматического управления"</p>
<p align="center">Тема: "Моделирование управляемого объекта"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-66</p>
<p align="right">Лысюк Р.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – output temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants. After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Выполнение работы

Константы

```cpp
const int N = 15;
const double A = 0.9;
const double B = 0.01;
const double C_val = 0.4;
const double D_val = 0.1;
const double Y_start = 20;
std::array<double, N> U = {4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 6, 5, 4, 5, 6};
```

Имея данные параметры получим результат работы программы:

```
Линейная модель:
y0 = 20
y1 = 18.04
y2 = 16.296
y3 = 14.7164
y4 = 13.2848
y5 = 12.0163
y6 = 10.8647
y7 = 9.81819
y8 = 8.89637
y9 = 8.05673
y10 = 7.29106
y11 = 6.62195
y12 = 6.00976
y13 = 5.44878
y14 = 4.9539
y15 = 4.51851

Нелинейная модель:
y0 = 20
y1 = 16.3243
y2 = 12.6639
y3 = 10.2368
y4 = 9.93371
y5 = 9.86447
y6 = 9.39534
y7 = 9.80705
y8 = 9.91568
y9 = 9.46644
y10 = 9.86091
y11 = 9.95074
y12 = 9.4874
y13 = 9.47281
y14 = 9.92953
y15 = 9.95074
```

**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.