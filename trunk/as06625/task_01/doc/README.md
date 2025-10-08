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
<p align="right">Ярома А.И.</p>
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
constexpr int TIME_STEPS = 10; // количество временных шагов
constexpr double COEFF_A = 0.99;
constexpr double COEFF_B = 0.01;
constexpr double COEFF_C = 0.5;
constexpr double COEFF_D = 0.1;
constexpr double INITIAL_Y = 18;
const std::vector<double> INPUTS = {5, 7, 6, 5, 7, 6, 5, 7, 6, 5}; // значения управляющего воздействия

```
Имея данные параметры получим результат работы программы:
```bash
Линейная модель
y0 = 18
y1 = 17.87
y2 = 17.7613
y3 = 17.6437
y4 = 17.5173
y5 = 17.4121
y6 = 17.298
y7 = 17.175
y8 = 17.0732
y9 = 16.9625
y10 = 16.8429
Нелинейная модель
y0 = 18
y1 = 16.9841
y2 = 16.9784
y3 = 16.9897
y4 = 16.4092
y5 = 16.7627
y6 = 16.9682
y7 = 16.4607
y8 = 16.821
y9 = 17.0089
y10 = 16.4814

## Вывод
Зная функцию, можно моделировать параметры модели в зависимости от времени.
