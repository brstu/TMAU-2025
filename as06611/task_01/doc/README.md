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
const int STEPS = 12;         // количество шагов моделирования
const double ALPHA = 0.92;    // коэффициент для линейной части
const double BETA = 0.02;     // коэффициент для входного сигнала
const double GAMMA = 0.40;    // коэффициент при u[k] в нелинейной модели
const double DELTA = 0.10;    // коэффициент при sin(u[k-1])
double Y0 = 18.5;             // начальное значение температуры
double U[STEPS] = { 3, 5, 6, 4, 5, 7, 3, 6, 5, 4, 6, 5 };
```

Имея данные параметры получим результат работы программы:

```Линейная модель:
y0 = 18.5
y1 = 17.08
y2 = 15.8136
y3 = 14.6685
y4 = 13.575
y5 = 12.589
y6 = 11.7219
y7 = 10.8442
y8 = 10.0966
y9 = 9.38889
y10 = 8.71778
y11 = 8.14036
y12 = 7.58913

Нелинейная модель:
y0 = 18.5
y1 = 12.1891
y2 = 6.67309
y3 = 4.73981
y4 = 5.39434
y5 = 7.21759
y6 = 7.3239
y7 = 8.11023
y8 = 8.36068
y9 = 7.88042
y10 = 8.17628
y11 = 8.25222

```

**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени.