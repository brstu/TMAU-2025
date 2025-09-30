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
const int STEPS = 10;
const double K1 = 0.98;
const double K2 = 0.03;
const double K3 = 0.4;
const double K4 = 0.2;
const double Y0 = 19.0;
double u[10] = {5,7,6,5,7,6,5,7,6,5};
```
Имея данные параметры  получим результат работы программы:
```Линейная модель
=== Линейная модель ===
y0 = 19
Шаг 1: y = 18.77
Шаг 2: y = 18.6046
Шаг 3: y = 18.4125
Шаг 4: y = 18.1943
Шаг 5: y = 18.0404
Шаг 6: y = 17.8596
Шаг 7: y = 17.6524
Шаг 8: y = 17.5093
Шаг 9: y = 17.3391
Шаг 10: y = 17.1424

=== Нелинейная модель ===
y0 = 19
Шаг 1: y = 10.3982
Шаг 2: y = 9.47796
Шаг 3: y = 8.53757
Шаг 4: y = 8.78833
Шаг 5: y = 8.82692
Шаг 6: y = 8.25706
Шаг 7: y = 8.65476
Шаг 8: y = 8.76592
Шаг 9: y = 8.22948
``` 
**Вывод:** Имея заданную функцию, можно описывать изменение параметров модели во времени.