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
<p align="right">Осовец А.О.</p>
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
Инициализация параметров  
```
double a = 0.8;
double b = 0.2;
double c = 0.1;
double d = 0.05;

int N = 20; 

vector<double> y(N + 1, 0.0); 
vector<double> u(N + 1, 0.0); 


### Результаты моделирования

#### Линейная модель

| Время t | Температура y(t) |
|---------|------------------|
| 1-5     | 0.0000          |
| 6       | 0.2000          |
| 10      | 0.6723          |
| 15      | 0.8926          |
| 20      | 0.9648          |

#### Нелинейная модель

| Время t | Температура y(t) |
|---------|------------------|
| 2-5     | 0.0000          |
| 6       | 0.1000          |
| 10      | 0.4310          |
| 15      | 0.4800          |
| 20      | 0.4800          |