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
<p align="right">Кацевич А.Ю.</p>
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

> **Note:** In the nonlinear model, the quadratic term uses a separate parameter $b_{nl}$, which may differ from $b$ in the linear model.

## Выполнение работы
Инициализация параметров  
```cpp
// Linear model parameters
double a = 0.8;
double b_lin = 0.3;
// Nonlinear model parameters
double b_nonlin = 0.06;
double c = 0.52;
double d = 0.13;
Enter number of steps n: 10
Enter initial temperature y0: 21
Enter constant heating u: 5 

Simulation results:
Step    Linear          Nonlinear
---------------------------------
0       21.0000         21.0000
1       18.3000         -7.0600
2       16.1400         -6.1633
3       14.4120         -4.7344
4       13.0296         -2.6571
5       11.9237         -0.0740
6       11.0389         2.4158
7       10.3312         4.0578
8       9.7649          4.7336
9       9.3119          4.9178
10      8.9496          4.9585  
```