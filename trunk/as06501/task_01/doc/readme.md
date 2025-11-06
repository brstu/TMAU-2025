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
const int N = 10;
const double a = 0.85;
const double b = 0.05;
const double c = 0.35;
const double d = 0.12;
double start_value = 10.0;
double u[N] = { 3.0, 5.0, 4.0, 6.0, 5.0, 7.0, 4.0, 6.0, 5.0, 4.0 };
```

Имея данные параметры получим результат работы программы:

```Линейная модель:
y0 = 10.000
y1 = 11.000
y2 = 12.350
y3 = 13.498
y4 = 15.223
y5 = 16.940
y6 = 19.399
y7 = 20.489
y8 = 22.416
y9 = 24.054
y10 = 25.446

Нелинейная модель:
y0 = 10.000
y1 = 11.420
y2 = 13.125
y3 = 14.236
y4 = 15.893
y5 = 17.228
y6 = 18.954
y7 = 19.863
y8 = 21.245
y9 = 22.187
```

**Вывод:** В ходе лабораторной работы были успешно реализованы и протестированы линейная и нелинейная модели температурного объекта.
