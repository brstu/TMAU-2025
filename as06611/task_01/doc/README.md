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
<p align="right">Лысюк Р.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – output temperature; $u(\tau)$ – input heat; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Выполнение работы
Инициализация параметров  
```
double a = 0.8;  
double b = 0.5;  
double c = 0.3;  
double d = 0.1;  
vector<double> u = { 1.0, 1.2, 0.8, 1.5, 1.0, 0.7, 1.3, 0.9, 1.1, 0.6 };
```
Результат работы программы:
```bash
Linear model:
t=1, u=1, y=0.5
t=2, u=1.2, y=1
t=3, u=0.8, y=1.2
t=4, u=1.5, y=1.71
t=5, u=1, y=1.868
t=6, u=0.7, y=1.8444
t=7, u=1.3, y=2.12552
t=8, u=0.9, y=2.15042
t=9, u=1.1, y=2.27033
t=10, u=0.6, y=2.11627

Nonlinear model:
t=1, u=1, y=0.3
t=2, u=1.2, y=0.684147
t=3, u=0.8, y=0.835522
t=4, u=1.5, y=0.956124
t=5, u=1, y=0.815601
t=6, u=0.7, y=0.489541
t=7, u=1.3, y=0.513452
t=8, u=0.9, y=0.657292
t=9, u=1.1, y=0.80235
t=10, u=0.6, y=0.694984


```
**Вывод:** зная функцию отражающую систему, можно моделировать параметры модели в зависимости от времени или других параметров.
