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
<p align="right">группы АС-66</p>
<p align="right">Осовец А.О.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input heat; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Выполнение работы
Инициализация параметров  
```
double a = 0.8;
double b = 0.2;
double c = 0.1;
double d = 0.05;

int N = 20; 

vector<double> y(N + 1, 0.0); 
vector<double> u(N + 1, 0.0); 

```
Имея данные параметры получим результат работы программы:
```bash
Linear model
t=1  y=0.0000
t=2  y=0.0000
t=3  y=0.0000
t=4  y=0.0000
t=5  y=0.0000
t=6  y=0.2000
t=7  y=0.3600
t=8  y=0.4880
t=9  y=0.5904
t=10  y=0.6723
t=11  y=0.7379
t=12  y=0.7903
t=13  y=0.8322
t=14  y=0.8658
t=15  y=0.8926
t=16  y=0.9141
t=17  y=0.9313
t=18  y=0.9450
t=19  y=0.9560
t=20  y=0.9648

Nonlinear model
<!-- Note: The output for t=1 is omitted because the initial condition y(1) is zero and not shown in the results. -->
t=2  y=0.0000
t=3  y=0.0000
t=4  y=0.0000
t=5  y=0.0000
t=6  y=0.1000
t=7  y=0.2221
t=8  y=0.3177
t=9  y=0.3864
t=10  y=0.4310
t=11  y=0.4570
t=12  y=0.4705
t=13  y=0.4767
t=14  y=0.4792
t=15  y=0.4800
t=16  y=0.4801
t=17  y=0.4801
t=18  y=0.4800
t=19  y=0.4800
t=20  y=0.4800
```