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
<p align="right">Ракецкий П. П.</p>
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

### Теоретическая часть

Объект управления описывается дифференциальным уравнением:
dy(τ)/dt = u(τ)/C + (Y₀ - y(τ))/RC


После дискретизации получены модели:
- Линейная: y_{τ+1} = a*y_τ + b*u_τ
- Нелинейная: y_{τ+1} = a*y_τ - b*y_{τ-1}² + c*u_τ + d*sin(u_{τ-1})


### Практическая часть

#### Реализация программы

Создан класс `TemperatureModel` с методами:
- `linearModel()` - линейная модель
- `nonlinearModel()` - нелинейная модель
- `reset()` - сброс состояния
- `setInitialTemperature()` - установка начальной температуры

#### Пример использования

```cpp
TemperatureModel linear(0.8, 0.2);
linear.setInitialTemperature(20.0);
double temp = linear.linearModel(5.0);

Программа успешно моделирует температурный объект для различных входных воздействий. Обе модели демонстрируют адекватное поведение системы.

