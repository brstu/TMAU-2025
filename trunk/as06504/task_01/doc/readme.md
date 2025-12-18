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
<p align="right">Дацкевич М. Г.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
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

Параметры
```cpp
LinearCfg linCfg{0.65, 0.25};
NonlinearCfg nonlinCfg{0.65, 0.25, 0.05, 0.20};

std::vector<double> control(nSteps, 1.0);
std::vector<double> yLinear(nSteps, 0.0);
std::vector<double> yNonlinear(nSteps, 0.0);
```

Результат работы программы:
```
=== Temperature Simulation ===
Step | Linear    | Nonlinear
-------------------------------
  0 |   0.0000 |     0.0000
  1 |   0.2500 |     0.0500
  2 |   0.4125 |     0.2508
  3 |   0.5181 |     0.3807
  4 |   0.5868 |     0.4500
  5 |   0.6314 |     0.4746
  6 |   0.6604 |     0.4761
  7 |   0.6793 |     0.4715
  8 |   0.6915 |     0.4681
  9 |   0.6995 |     0.4670
 10 |   0.7047 |     0.4671
 11 |   0.7080 |     0.4674
 12 |   0.7102 |     0.4675
 13 |   0.7116 |     0.4676
 14 |   0.7126 |     0.4676
 15 |   0.7132 |     0.4676
 16 |   0.7136 |     0.4676
 17 |   0.7138 |     0.4675
 18 |   0.7140 |     0.4676
 19 |   0.7141 |     0.4676
```
**Вывод:** Заданные функции моделируют изменение температуры во времени и показывают поведение объекта при разных режимах управления.
