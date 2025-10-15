
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
<p align="right">Лопато А.В.</p>
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
int steps = 10; 
const double kA = 0.95;
const double kB = 0.02;
const double kC = 0.45;
const double kD = 0.15;
double yStart = 18;
double control[10] = { 5, 7, 6, 5, 7, 6, 5, 7, 6, 5 };
```
Имея данные параметры получим результат работы программы:
```Линейная модель
y0 = 18
y1 = 17.2
y2 = 16.48
y3 = 15.776
y4 = 15.0872
y5 = 14.4728
y6 = 13.8692
y7 = 13.2757
y8 = 12.752
y9 = 12.2344
y10 = 11.7226

Нелинейная модель
y0 = 18
y1 = 26.5862
y2 = 34.5354
y3 = 41.4967
y4 = 48.908
y5 = 55.7412
y6 = 61.6422
y7 = 68.0463
y8 = 73.9225
y9 = 78.9145
```
**Вывод:** на основе математической модели можно прогнозировать изменение параметров во времени.

