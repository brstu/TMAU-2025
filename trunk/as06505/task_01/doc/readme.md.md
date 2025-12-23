
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
<p align="right">Студентка 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Сергиевич М.А.</p>
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
int n = 10;
const double a = 0.9;
const double b = 0.001;
const double c = 0.4;
const double d = 0.1;
double Y0 = 10;
double u[10] = {10,8,12,9,11,10,8,12,9,11};
```
Имея данные параметры получим результат работы программы:
```Линейная модель
y0 = 10
y1 = 9.01
y2 = 8.117
y3 = 7.3173
y4 = 6.59457
y5 = 5.94611
y6 = 5.3615
y7 = 4.83335
y8 = 4.36202
y9 = 3.93481
y10 = 3.55233

Нелинейная модель
y0 = 10
y1 = 12.0456
y2 = 15.64
y3 = 17.4772
y4 = 19.9261
y5 = 21.528
y6 = 22.1238
y7 = 24.3469
y8 = 24.9691
y9 = 26.3206
```
**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.

