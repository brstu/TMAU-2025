<p align="center">Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный Технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center"><strong>Лабораторная работа №1</strong></p>
<p align="center"><strong>По дисциплине:</strong> "Теория и методы автоматического управления" </p>
<p align="center"><strong>Тема:</strong> "Моделирование управляемого объекта"</p>
<br><br><br><br><br>

<div style="float: right; text-align: left; width: 140px; margin-right: 90px;">
<p><strong>Выполнила:</strong></p>
<p>Студентка 3 курса</p>
<p>Группы АС-66</p>
<p>Прокурат В.Д.</p>
<p><strong>Проверил:</strong></p>
<p>Иванюк Д.С.</p>
</div>

<br><br><br><br><br><br><br><br><br><br><br><br>
<p align="center"><strong>Брест 2025</strong></p>

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

## Выполнение задания 1
**Список заданных констант и начальных условий:**

Для линейной модели:
```
a = 0.8;
b = 0.2;

y_prev = 20.0;
y_prev2 = 0;
u_prev = 0;
```
Для нелинейной модели:
```
a = 0.7;
b = 0.01;
c = 0.3;
d = 0.1;

y_prev = 20.0;
y_prev2 = 19.5;
u_prev = 5.0;
```
Управляющие воздействия:
```
control_inputs = [10, 15, 20, 25, 30, 25, 20, 15, 10, 5]
```

**Имея данные параметры, мы получаем следующий результат работы программы:**

Линейная модель

```
y0 = 20.0
y1 = 18.0
y2 = 17.4
y3 = 17.92
y4 = 19.336
y5 = 21.4688
y6 = 22.175
y7 = 21.74
y8 = 20.392
y9 = 18.3136
y10 = 15.6509
```
Нелинейная модель

```
y0 = 20.0
y1 = 13.1016
y2 = 9.61669
y3 = 11.0802
y4 = 14.5869
y5 = 18.7414
y6 = 20.6769
y7 = 19.6915
y8 = 16.8988
y9 = 13.6604
y10 = 10.9249
```

**Вывод:** имея некоторую функцию, мы можем моделировать параметры модели в зависимости от времени.
