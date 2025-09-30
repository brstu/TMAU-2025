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
<p align="right">Ярмак К.А.</p>
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
**Инициализация параметров:**
```cpp
int n = 30;
double a = 0.8, b = 0.15, c = 0.05, d = 0.1;

std::vector<double> u(n, 1.0);
std::vector<double> y_lin(n, 0.0);
std::vector<double> y_nonlin(n, 0.0);
```

**Результат работы программы:**
```
Simulation results:
Step    Linear model    Nonlinear model
0       0.00000         0.00000
1       0.15000         0.15000
2       0.27000         0.25415
3       0.36600         0.33409
4       0.44280         0.39173
5       0.50424         0.43079
6       0.55339         0.45576
7       0.59271         0.47092
8       0.62417         0.47972
9       0.64934         0.48466
10      0.66947         0.48736
11      0.68558         0.48880
12      0.69846         0.48956
13      0.70877         0.48995
14      0.71701         0.49016
15      0.72361         0.49027
16      0.72889         0.49032
17      0.73311         0.49035
18      0.73649         0.49037
19      0.73919         0.49037
20      0.74135         0.49038
21      0.74308         0.49038
22      0.74447         0.49038
23      0.74557         0.49038
24      0.74646         0.49038
25      0.74717         0.49038
26      0.74773         0.49038
27      0.74819         0.49038
28      0.74855         0.49038
29      0.74884         0.49038
```
**Вывод:** зная функцию  отражающую систему, можно моделировать параметры модели в зависимости от времени или других параметров.