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
<p align="right">Группы АС-65</p>
<p align="right">Сунцова М.Д.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – output (controlled) temperature; $u(\tau)$ – input heat; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-b_{nl}y_{\tau}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b$ – constants for the linear model; $a,b_{nl},c,d$ – constants for the nonlinear model.

## Выполнение работы
**Настройка параметров и начальных условий:**
```cpp
LinParams lin{0.75, 0.18};
NonlinParams nonlin{0.75, 0.18, 0.07, 0.12};

std::vector<double> u(steps, 1.0);
std::vector<double> y_lin(steps, 0.0);
std::vector<double> y_nonlin(steps, 0.0);
```

**Результаты моделирования:**
```
--- Temperature Simulation ---
Step |  Linear   |  Nonlinear
-------------------------------
  0 |   0.0000 |     0.0000
  1 |   0.1800 |     0.1800
  2 |   0.3150 |     0.3060
  3 |   0.4163 |     0.3946
  4 |   0.4922 |     0.4501
  5 |   0.5491 |     0.4805
  6 |   0.5919 |     0.4949
  7 |   0.6239 |     0.5006
  8 |   0.6479 |     0.5023
  9 |   0.6659 |     0.5026
 10 |   0.6795 |     0.5025
 11 |   0.6896 |     0.5024
 12 |   0.6972 |     0.5023
 13 |   0.7029 |     0.5023
 14 |   0.7072 |     0.5023
 15 |   0.7104 |     0.5023
 16 |   0.7128 |     0.5023
 17 |   0.7146 |     0.5023
 18 |   0.7159 |     0.5023
 19 |   0.7170 |     0.5023
```
---
**Вывод:** имея математическую модель, описывающую поведение системы, можно воспроизводить её изменение во времени и анализировать влияние различных параметров.
