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
<p align="right">Езепчук А.С.</p>
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
double a = 0.9;
double b_lin = 0.2;
// Nonlinear model parameters
double b_nonlin = 0.01;
double c = 0.15;
double d = 0.05;
Enter initial temperature y0: 20   
Enter constant heating u: 2

Simulation results:
Step    Linear          Nonlinear  
---------------------------------  
0       20.0000         20.0000    
1       18.4000         14.3000    
2       16.9600         11.1706    
3       15.6640         9.1512     
4       14.4976         7.7441     
5       13.4478         6.7154     
6       12.5031         5.9384     
7       11.6528         5.3374     
8       10.8875         4.8642     
9       10.1987         4.4867     
10      9.5789          4.1822     
11      9.0210          3.9345     
12      8.5189          3.7317     
13      8.0670          3.5647     
14      7.6603          3.4267     
15      7.2943          3.3120     
16      6.9648          3.2166     
17      6.6683          3.1369     
18      6.4015          3.0703     
19      6.1614          3.0145     
20      5.9452          2.9676
```