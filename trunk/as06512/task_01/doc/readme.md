<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный Технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “ТиМАУ”</p>
<p align="center">Тема: “Моделирование управляемого объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Нестюк Н.С.</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д.С.</p>
<br><br><br><br><br><br><br><br>
<p align="center">Брест 2025</p>

---
## Task 1. Modeling controlled object
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

dy(τ)/dτ = u(τ)/C + Y0−y(τ)/RC

where τ – time; y(τ) – input temperature; u(τ) – input warm; Y0 – room temperature; C,RC – some constants.

After transformation we get these linear (2) and nonlinear (3) models:

yτ+1 = ayτ+buτ
 
yτ+1 = ayτ−by^2τ−1 + cuτ+dsin⁡(uτ−1)

where τ – time discrete moments (1,2,3…n); a,b,c,d – some constants.

Task is to write program (С++), which simulates this object temperature.

## Выполнение работы
Константы:  
```
const int n = 10;
const double a = 0.98;
const double b = 0.02;
const double c = 0.4;
const double d = 0.15;
const double Y0 = 20.0;
const double u = 8.0;
```
Имея данные параметры получим результат работы программы:
```bash
```Линейная модель:
y0 = 20
y1 = 19.76
y2 = 19.5248
y3 = 19.2943
y4 = 19.0684
y5 = 18.847
y6 = 18.6301
y7 = 18.4175
y8 = 18.2092
y9 = 18.005
y10 = 17.8049

Нелинейная модель:
y0 = 20
y1 = 14.9484
y2 = 9.99784
y3 = 8.67719
y4 = 9.85291
y5 = 11.4984
y6 = 12.6752
y7 = 13.1259
y8 = 12.9985
y9 = 12.6412
```
**Поведение линейной модели:**
По полученным данным видим плавное экспоненциальное уменьшение температуры. Начальное значение: 20.0 Установившееся состояние: около 17.8. Наблюдается стабильная монотонная динамика

**Поведение нелинейной модели:**
По результатам наблюдаем резкое падение температуры на первых шагах. Минимум достигается на третьем шаге (8.68). Конечные колебания вариируются вокруг значения 12.5. Нелинейная модель проявляет более сложную и нестационарную динамику.

**Вывод:** Разработанная программа успешно моделирует температурное поведение объекта управления согласно заданным математическим моделям. Результаты демонстрируют принципиальные различия в динамике линейной и нелинейной систем, что подтверждает существенное влияние нелинейных членов (-b·y² и d·sin(u)) на поведение объекта управления.
