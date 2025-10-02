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
<p align="right">Вавдийчик Н.Д.</p>
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
const double a = 0.97;
const double b = 0.015;
const double c = 0.45;
const double d = 0.08;
double start_value = 18;
double u[N] = {5,7,6,5,7,6,5,7,6,5};
```

Имея данные параметры получим результат работы программы:

```Линейная модель:
y0 = 18
y1 = 17.535
y2 = 17.1139
y3 = 16.6905
y4 = 16.2648
y5 = 15.8819
y6 = 15.4954
y7 = 15.1056
y8 = 14.7574
y9 = 14.4047
y10 = 14.0475

Нелинейная модель:
y0 = 18
y1 = 15.6733
y2 = 13.0956
y3 = 11.2456
y4 = 11.4091
y5 = 11.9224
y6 = 11.8399
y7 = 12.4258
y8 = 12.7029
y9 = 12.2334
```

**Вывод:** зная функцию, можно моделировать параметры модели в зависимости от времени или других параметров.
