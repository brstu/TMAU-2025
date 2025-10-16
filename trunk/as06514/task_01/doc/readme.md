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
<p align="right">Рапин Е.Ю.</p>
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

## Ход работы
Константы  
```
int n = 10;
const double a = 0.8;
const double b = 0.1;
const double c = 0.05;
const double d = 0.02;
double Y0 = 20;
double u[10] = {3, 4, 5, 6, 7, 8, 9, 10, 9, 8};
```
Имея данные параметры получили результат выполнения работы программы:
```Линейная модель
y0 = 20
y1 = 16.5
y2 = 13.8
y3 = 11.74
y4 = 10.192
y5 = 9.0536
y6 = 8.24288
y7 = 7.4943
y8 = 6.79544
y9 = 6.13635
y10 = 5.50908

Нелинейная модель
y0 = 20
y1 = 18.25
y2 = 16.8808
y3 = 15.6741
y4 = 14.6405
y5 = 13.7496
y6 = 12.972
y7 = 12.1916
y8 = 11.4587
y9 = 10.7559
```
**Вывод:** если зная функцию, то можно моделировать параметры модели в зависимости от времени.

