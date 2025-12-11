

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
<p align="right">Романюк Д.А.</p>
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
const std::size_t n = 20; 
const double a = 0.92;
const double b_lin = 0.08;  
const double b_non = 0.005; 
const double c = 0.07; 
const double d = 0.04;

std::vector<double> u(n, 0.0);
```
Имея данные параметры получим результат работы программы:
```bash
 t      u(t)            linear y        nonlinear y
----------------------------------------------------
 0       0.0000           20.0000           20.0000
 1       0.0000           18.4000           16.4000
 2       0.0000           16.9280           13.0880
 3       0.0000           15.5738           10.6962
 4       0.0000           14.3279            8.9840
 5      10.0000           13.1816            7.6932
 6      10.0000           12.9271            7.3742
 7      10.0000           12.6929            7.1666
 8      10.0000           12.4775            6.9996
 9      10.0000           12.2793            6.8611
10      10.0000           12.0970            6.7455
11      10.0000           11.9292            6.6487
12      10.0000           11.7749            6.5675
13      10.0000           11.6329            6.4993
14      10.0000           11.5022            6.4420
15      10.0000           11.3821            6.3936
16      10.0000           11.2715            6.3529
17      10.0000           11.1698            6.3185
18      10.0000           11.0762            6.2895
19      10.0000           10.9901            6.2649
```
**Вывод:** разработана программа моделирования температурного объекта и исследованы особенности его линейной и нелинейной динамики.
