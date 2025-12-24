<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “Теория и методы автоматического управления”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Хвисюк К.Г.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
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


## Выполнение работы
**Параметры и количество итераций:**
```cpp
int total_steps = 30;

LinearParams lin_params{0.8, 0.15};
NonlinearParams nonlin_params{0.8, 0.15, 0.05, 0.1};
```

**Результаты моделирования:**
```bash
Time	LinearTemp	NonlinearTemp
0	0.0000		0.0000
1	0.1500		0.1500
2	0.2700		0.2541
3	0.3660		0.3341
4	0.4428		0.3917
5	0.5042		0.4308
6	0.5534		0.4558
7	0.5927		0.4709
8	0.6242		0.4797
9	0.6493		0.4847
10	0.6695		0.4874
11	0.6856		0.4888
12	0.6985		0.4896
13	0.7088		0.4900
14	0.7170		0.4902
15	0.7236		0.4903
16	0.7289		0.4903
17	0.7331		0.4904
18	0.7365		0.4904
19	0.7392		0.4904
20	0.7414		0.4904
21	0.7431		0.4904
22	0.7445		0.4904
23	0.7456		0.4904
24	0.7465		0.4904
25	0.7472		0.4904
26	0.7477		0.4904
27	0.7482		0.4904
28	0.7485		0.4904
29	0.7488		0.4904
```



---
**Вывод:** имея математическую модель, описывающую поведение системы, можно воспроизводить её изменение во времени и анализировать влияние различных параметров.
