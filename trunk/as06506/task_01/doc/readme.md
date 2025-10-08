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
<p align="right">Зинчук М.С.</p>
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
int N = 10;
const double A = 0.97;
const double B = 0.015;
const double C = 0.45;
const double D = 0.12;
double Y_value = 20;
double input[N] = {4,6,5,4,6,5,4,6,5,4};
```

Имея данные параметры получим результат работы программы:

```Линейная модель:
y0 = 20
y1 = 19.46
y2 = 18.9662
y3 = 18.4722
y4 = 17.978
y5 = 17.5287
y6 = 17.0778
y7 = 16.6255
y8 = 16.2167
y9 = 15.8052
y10 = 15.3911

Нелинейная модель:
y0 = 20
y1 = 16.0092
y2 = 11.7454
y3 = 9.23354
y4 = 9.49641
y5 = 10.1491
y6 = 10.1768
y7 = 10.9357
y8 = 11.2705
y9 = 10.8235
```

**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.
