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
<p align="right">Неруш Е. С.</p>
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
const double dt = 0.1;         // шаг дискретизации  
const double x_ref = 10.0;     // целевое положение  
const double kp = 2.0;         // пропорциональный коэффициент  
const double d = 0.5;          // дифференциальный коэффициент  
const double c = 0.0001;       // нелинейный коэффициент u^2  
const double s = 0.01;         // коэффициент sin(u_prev)  
const int steps = 100;
```
Имея данные параметры получим результат работы программы:
```bash
linear model
t=0.0  x=0.000000
t=0.1  x=0.200000
t=0.2  x=0.600000
t=0.3  x=1.186000
t=0.4  x=1.940000
t=0.5  x=2.840980
t=0.6  x=3.865460
t=0.7  x=4.988070
t=0.8  x=6.182150
t=0.9  x=7.420340
t=1.0  x=8.675180
t=1.1  x=9.919700
t=1.2  x=11.128000
t=1.3  x=12.275600
t=1.4  x=13.340300
t=1.5  x=14.302100
t=1.6  x=15.143900
t=1.7  x=15.851500
t=1.8  x=16.414100
t=1.9  x=16.824400
t=2.0  x=17.078200
...
t=9.9  x=10.516900

non linear model
t=0.0  x=0.000000
t=0.1  x=0.200000
t=0.2  x=0.600491
t=0.3  x=1.187480
t=0.4  x=1.942760
t=0.5  x=2.845130
t=0.6  x=3.871190
t=0.7  x=4.995360
t=0.8  x=6.190850
t=0.9  x=7.430360
t=1.0  x=8.686210
t=1.1  x=9.931570
t=1.2  x=11.140300
t=1.3  x=12.288300
t=1.4  x=13.353000
t=1.5  x=14.314500
t=1.6  x=15.156000
t=1.7  x=15.863300
t=1.8  x=16.425400
t=1.9  x=16.835100
t=2.0  x=17.088400
...
t=9.9  x=10.516100
