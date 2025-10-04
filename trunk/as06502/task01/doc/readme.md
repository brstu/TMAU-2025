
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
<p align="right">Грущинский Д.Д.</p>
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

# Выполнение работы
## Константы  
* const int STEPS = 10;
* const double A = 0.2;
* const double B = 0.02;
* const double C = 0.03;
* const double D = 0.04;

Используя данные константы и некоторые вводимые данные получим:
### Линейная модель
* y[1] = 4.3
* y[2] = 1.19
* y[3] = 0.598
* y[4] = 0.5196
* y[5] = 0.55392
* y[6] = 0.610784
* y[7] = 0.602157
* y[8] = 0.540431
* y[9] = 0.468086
* y[10] = 0.413617

### Нелинейная модель
* y[1] = -3.47899
* y[2] = -8.18427
* y[3] = -1.30896
* y[4] = -0.88992
* y[5] = 0.518262
* y[6] = 0.802519
* y[7] = 0.748909
* y[8] = 0.710367
* y[9] = 0.580817

**Вывод:** зная надлежащие функции, а также необходимые дополнительные сведения о структуре системы, можно моделировать параметры модели в зависимости от времени и прочих констант.

