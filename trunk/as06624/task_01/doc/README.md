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
<p align="right">Янчук А.Ю.</p>
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
linear model
t=1  y=0
t=2  y=0
t=3  y=0
t=4  y=0
t=5  y=0
t=6  y=0.2
t=7  y=0.36
t=8  y=0.488
t=9  y=0.5904
t=10  y=0.67232
t=11  y=0.737856
t=12  y=0.790285
t=13  y=0.832228
t=14  y=0.865782
t=15  y=0.892626
t=16  y=0.914101
t=17  y=0.931281
t=18  y=0.945024
t=19  y=0.95602
t=20  y=0.964816

 non linear model
t=2  y=0
t=3  y=0
t=4  y=0
t=5  y=0
t=6  y=0.1
t=7  y=0.222074
t=8  y=0.317732
t=9  y=0.386396
t=10  y=0.431
t=11  y=0.457013
t=12  y=0.470532
t=13  y=0.476727
t=14  y=0.479175
t=15  y=0.47996
t=16  y=0.48012
t=17  y=0.480097
t=18  y=0.480048
t=19  y=0.480013
t=20  y=0.479995
```