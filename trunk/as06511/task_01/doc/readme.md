<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Макарский А. Э.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br><br><br>
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

__Параметры__
```cpp
Lin lp{0.80, 0.22};
Nonlin np{0.76, 0.18, 0.09, 0.14};

std::vector<double> u(N, 1.0);
std::vector<double> yL(N, 0.0);
std::vector<double> yN(N, 0.0);
```

__Имея данные параметры получим результат работы программы:__
```bash
t       linear          nonlinear
----------------------------------
0       0.000000        0.000000
1       0.220000        0.090000
2       0.396000        0.276206
3       0.536800        0.416264
4       0.649440        0.510435
5       0.739552        0.564547
6       0.811642        0.589964
7       0.869313        0.598810
8       0.915451        0.600251
9       0.952360        0.599454
10      0.981888        0.598536
11      1.005511        0.598012
12      1.024409        0.597810
13      1.039527        0.597771
14      1.051621        0.597784
15      1.061297        0.597802
16      1.069038        0.597813
17      1.075230        0.597818
18      1.080184        0.597819
19      1.084147        0.597819
```

**Вывод:** зная функцию, можно моделировать поведение модели в зависимости от времени.
