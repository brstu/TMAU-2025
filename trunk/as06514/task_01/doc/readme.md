<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">"Брестский Государственный Технический университет"</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине "Теория и методы автоматического управления"</p>
<p align="center">Тема: "Моделирование управляемого объекта"</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Ракецкий П. П.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ - time; $y(\tau)$ - input temperature; $u(\tau)$ - input warm; $Y_0$ - room temperature; $C,RC$ - some constants.

After transformation we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)

$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ - time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ - some constants.

Task is to write program (**С++**), which simulates this object temperature.

## Выполнение работы

### Теоретическая часть

Объект управления описывается дифференциальным уравнением:
dy(τ)/dt = u(τ)/C + (Y₀ - y(τ))/RC

После дискретизации получены модели:
- Линейная: y_{τ+1} = a*y_τ + b*u_τ
- Нелинейная: y_{τ+1} = a*y_τ - b*y_{τ-1}² + c*u_τ + d*sin(u_{τ-1})

### Практическая часть

#### Реализация программы

Программа реализована с использованием функций:
- `linear(double yt, double ut)` - линейная модель
- `nonlinear(double yt, double yt_1, double ut, double ut_1)` - нелинейная модель

Используемые константы:
- `a_lin = 0.8`, `b_lin = 0.2` - коэффициенты линейной модели
- `a_nonlin = 0.7`, `b_nonlin = 0.1`, `c_nonlin = 0.3`, `d_nonlin = 0.05` - коэффициенты нелинейной модели
- `Y0 = 20.0` - начальная температура
- `n = 10` - количество временных шагов

#### Пример использования

```cpp
double yt_lin = Y0;
for (int i = 0; i < n; i++) {
    yt_lin = linear(yt_lin, u[i]);
    cout << "y" << i + 1 << " = " << yt_lin << endl;
}