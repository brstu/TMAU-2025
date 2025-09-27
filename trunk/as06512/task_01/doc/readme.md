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
<p align="right">Нестюк Н.С.</p>
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
const int n = 10;
const double a = 0.98;
const double b = 0.02;
const double c = 0.4;
const double d = 0.15;
const double Y0 = 20.0;
const double u = 8.0;
```cpp
Имея данные параметры получим результат работы программы:
```Линейная модель:
y1 = 19.76
y2 = 19.5248
y3 = 19.2943
y4 = 19.0684
y5 = 18.847
y6 = 18.6301
y7 = 18.4175
y8 = 18.2092
y9 = 18.005
y10 = 17.8049

Нелинейная модель:
y1 = 14.9484
y2 = 9.99784
y3 = 8.67719
y4 = 9.85291
y5 = 11.4984
y6 = 12.6752
y7 = 13.1259
y8 = 12.9985
y9 = 12.6412
```console
