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
<p align="right">Николова М.С.</p>
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
const double a = 0.6;
const double b = 0.3;
const double c = 0.8;
const double d = 0.5;
```
Имея данные параметры получим результат работы программы:
```bash
Linear Model Simulation:
Step 1: y = 7.5
Step 2: y = 7.2
Step 3: y = 7.02
Step 4: y = 6.912
Step 5: y = 6.8472
Step 6: y = 6.80832
Step 7: y = 6.78499
Step 8: y = 6.771
Step 9: y = 6.7626
Step 10: y = 6.75756
Step 11: y = 6.75453

Nonlinear Model Simulation:
Step 1: y = -6.99394
Step 2: y = -15.9903
Step 3: y = -16.8627
Step 4: y = -79.4185
Step 5: y = -125.55
Step 6: y = -1960.11
Step 7: y = -5897.51
Step 8: y = -1.15615e+06
Step 9: y = -1.11279e+07
Step 10: y = -4.01008e+11
Step 11: y = -3.73894e+13
```
**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.