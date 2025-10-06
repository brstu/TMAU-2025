
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
<p align="right">Гуща И.В.</p>
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
const int n = 10; // такты времени
const double a = 0.99;
const double b = 0.01;
const double c = 0.5;
const double d = 0.1;
const double Y0 = 18;
double u[n] = {5,7,6,5,7,6,5,7,6,5};
```
Имея данные параметры получим результат работы программы:
```bash
Линейная модель
y0 = 18
y1 = 17.87
y2 = 17.7613
y3 = 17.6437
y4 = 17.5173
y5 = 17.4121
y6 = 17.298
y7 = 17.175
y8 = 17.0732
y9 = 16.9625
y10 = 16.8429

Нелинейная модель
y0 = 18
y1 = 17.9841
y2 = 17.63
y3 = 16.6857
y4 = 16.683
y5 = 16.3418
y6 = 15.4105
y7 = 15.4205
y8 = 15.092
y9 = 14.1731
```
**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.

