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
<p align="right">Гончерёнок К. А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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
```cpp
const ParamsLin PL{0.77, 0.29};
const ParamsNonlin PN{0.86, 0.15, 0.10, 0.11};
```

Имея данные параметры получим результат работы программы:
```bash
 t |    linear   |  nonlinear 
--------------------------------
 0 |     0.0000 |     0.0000
 1 |     0.2900 |     0.1000
 2 |     0.5133 |     0.2786
 3 |     0.6852 |     0.4306
 4 |     0.8176 |     0.5513
 5 |     0.9196 |     0.6388
 6 |     0.9981 |     0.6964
 7 |     1.0585 |     0.7302
 8 |     1.1051 |     0.7478
 9 |     1.1409 |     0.7557
10 |     1.1685 |     0.7586
11 |     1.1897 |     0.7593
12 |     1.2061 |     0.7592
13 |     1.2187 |     0.7590
14 |     1.2284 |     0.7589
15 |     1.2359 |     0.7588
16 |     1.2416 |     0.7587
17 |     1.2460 |     0.7587
18 |     1.2495 |     0.7587
19 |     1.2521 |     0.7587
20 |     1.2541 |     0.7587
21 |     1.2557 |     0.7587
22 |     1.2569 |     0.7587
23 |     1.2578 |     0.7587
24 |     1.2585 |     0.7587
25 |     1.2590 |     0.7587
26 |     1.2595 |     0.7587
27 |     1.2598 |     0.7587
28 |     1.2600 |     0.7587
29 |     1.2602 |     0.7587
```
**Вывод:** использование заданных функций позволяет описывать динамику изменения температуры во времени и анализировать особенности поведения объекта при различных условиях управления.
