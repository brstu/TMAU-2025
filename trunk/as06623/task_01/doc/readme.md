
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
<p align="right">Цеван К.А.</p>
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
const int N = 10;
const double COEFF_A = 0.7;
const double COEFF_B = 0.05;
const double COEFF_C = 0.3;
const double COEFF_D = 0.2;
double INITIAL_VALUE = 15;
double inputSequence[10] = { 12, 9, 14, 11, 13, 10, 8, 15, 12, 11 };
```
Имея данные параметры получим результат работы программы:
```Линейная модель
y0 = 15
y1 = 11.1
y2 = 8.22
y3 = 6.454
y4 = 5.0678
y5 = 4.19746
y6 = 3.43822
y7 = 2.80676
y8 = 2.71473
y9 = 2.50031
y10 = 2.30022
Нелинейная модель
y0 = 15
y1 = 1.84269
y2 = -5.6777
y3 = -0.646041
y4 = 1.63596
y5 = 4.20834
y6 = 5.10321
y7 = 7.38462
y8 = 7.59715
y9 = 5.78406
```
**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.