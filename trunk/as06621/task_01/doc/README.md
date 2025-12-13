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
<p align="right">Группы АС-66</p>
<p align="right">Рогожин А.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – output (controlled) temperature; $u(\tau)$ – input heat; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)


$$\Large y_{\tau+1}=ay_{\tau}-b_{nl}y_{\tau}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b$ – constants for the linear model; $a,b_{nl},c,d$ – constants for the nonlinear model.

> **Note:** In the nonlinear model, the quadratic term uses a separate parameter $b_{nl}$, which may differ from $b$ in the linear model.
>
> Введите количество шагов моделирования: 5
Введите начальную температуру y0: 2
Введите постоянное нагревание u: 3

Результаты моделирования:
t       Линейная        Нелинейная
--------------------------------- 
0       2.0000          2.0000    
1       2.4000          2.2100    
2       2.7600          2.3972    
3       3.0840          2.5571    
4       3.3756          2.6930    
5       3.6380          2.8083
