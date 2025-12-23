<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Касьяник К.А.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**С++**), which simulates this object temperature.


## Ход работы

__Пaрaмeтры:__
```cpp
LinearParams lp{0.86, 0.23};
NonlinearParams np{0.69, 0.15, 0.10, 0.21};
```

__Полученные результаты моделирования:__

```bash
  t |     lin |     nonlin
===========================
  0 |  0.0000 |     0.0000
  1 |  0.2300 |     0.1000
  2 |  0.4278 |     0.3457
  3 |  0.5979 |     0.5137
  4 |  0.7442 |     0.6133
  5 |  0.8700 |     0.6603
  6 |  0.9782 |     0.6759
  7 |  1.0713 |     0.6777
  8 |  1.1513 |     0.6758
  9 |  1.2201 |     0.6741
 10 |  1.2793 |     0.6733
 11 |  1.3302 |     0.6732
 12 |  1.3740 |     0.6732
 13 |  1.4116 |     0.6732
 14 |  1.4440 |     0.6733
 15 |  1.4718 |     0.6733
 16 |  1.4958 |     0.6733
 17 |  1.5164 |     0.6733
 18 |  1.5341 |     0.6733
 19 |  1.5493 |     0.6733
 20 |  1.5624 |     0.6733
 21 |  1.5737 |     0.6733
 22 |  1.5834 |     0.6733
 23 |  1.5917 |     0.6733
 24 |  1.5988 |     0.6733
```

__Вывод:__ наличие формализованной модели позволяет воспроизводить динамику системы во времени и исследовать, как изменение параметров отражается на её поведении.
