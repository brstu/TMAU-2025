
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
<p align="right">Колбашко А.В.</p>
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

struct Constants{
    const int n = 10;  

    const double a = 1.2;
    const double b = 0.01;
    const double c = 0.75;
    const double d = 0.03;
};
```
Результат работы программы:
```Linear:
y0: 25
y1: 30.04
y2: 36.088
y3: 43.3456
y4: 52.0547
y5: 62.5057
y6: 75.0468
y7: 90.0962
y8: 108.155
y9: 129.827
y10: 155.832

Nonlinear:
y0: 25
y1: 25
y2: 26.7273
y3: 28.8001
y4: 30.3939
y5: 31.1555
y6: 31.126
y7: 30.6219
y8: 30.0353
y9: 29.6426
y10: 29.5273
```
**Вывод:** зная функцию  отражающую систему, можно моделировать параметры модели в зависимости от времени или других параметров.

