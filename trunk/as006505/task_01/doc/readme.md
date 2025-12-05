<p align="center"> Министерство образования Республики Беларусь</p>
<p align="center">Учреждение образования</p>
<p align="center">“Брестский Государственный технический университет”</p>
<p align="center">Кафедра ИИТ</p>
<br><br><br><br><br><br><br>
<p align="center">Лабораторная работа №1</p>
<p align="center">По дисциплине “ТМАУ</p>
<p align="center">Тема: “Моделирование температуры объекта”</p>
<br><br><br><br><br>
<p align="right">Выполнил:</p>
<p align="right">Студент 3 курса</p>
<p align="right">Группы АС-65</p>
<p align="right">Егоренков Н.Д</p>
<p align="right">Проверил:</p>
<p align="right">Иванюк Д. С.</p>
<br><br><br><br><br>
<p align="center">Брест 2025</p>

<hr>

# Общее задание #
1. Написать отчет по выполненной лабораторной работе №1 в .md формате (readme.md) и с помощью запроса на внесение изменений (**pull request**) разместить его в следующем каталоге: **trunk\ii0xxyy\task_01\doc** (где **xx** - номер группы, **yy** - номер студента, например **ii02102**).
2. Исходный код написанной программы разместить в каталоге: **trunk\ii0xxyy\task_01\src**.
## Task 1. Modeling controlled object ##
Let's get some object to be controlled. We want to control its temperature, which can be described by this differential equation:

$$\Large\frac{dy(\tau)}{d\tau}=\frac{u(\tau)}{C}+\frac{Y_0-y(\tau)}{RC} $$ (1)

where $\tau$ – time; $y(\tau)$ – input temperature; $u(\tau)$ – input warm; $Y_0$ – room temperature; $C,RC$ – some constants.

After transformation, we get these linear (2) and nonlinear (3) models:

$$\Large y_{\tau+1}=ay_{\tau}+bu_{\tau}$$ (2)
$$\Large y_{\tau+1}=ay_{\tau}-by_{\tau-1}^2+cu_{\tau}+d\sin(u_{\tau-1})$$ (3)

where $\tau$ – time discrete moments ($1,2,3{\dots}n$); $a,b,c,d$ – some constants.

Task is to write program (**C++**), which simulates this object temperature.

<hr>

# Выполнение задания #

Код программы:
```cpp
#include <iostream>
#include <cmath>

double nextLinear(double a, double b, double u, double y) {
    return a * y + b * u;
}

void simulateLinear(double a, double b, double u, int steps) {
    std::cout << "Линейная модель" << std::endl;
    double y = 0.0;
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        y = nextLinear(a, b, u, y);
    }
}

struct NonlinearParams {
    double a;
    double b;
    double c;
    double d;
};

double nextNonlinear(const NonlinearParams& params, double u_prev, double y, double y_prev) {
    return params.a * y - params.b * (y_prev * y_prev) + params.c * u_prev + params.d * std::sin(u_prev);
}

void simulateNonlinear(double a, double b, double c, double d, double u, int steps) {
    std::cout << "Нелинейная модель" << std::endl;
    double y = 0.0;
    double y_prev = 0.0;
    double u_prev = 0.0;
    
    NonlinearParams params{a, b, c, d};
    
    for (int i = 0; i < steps; i++) {
        std::cout << "τ=" << i << ": y=" << y << std::endl;
        double y_next = nextNonlinear(params, u_prev, y, y_prev);
        y_prev = y;
        y = y_next;
        u_prev = u; 
    }
}

int main() {
    double a1 = 0.3;
    double b1 = 0.3;
    double u1 = 0.9;
    int n1 = 10;
    simulateLinear(a1, b1, u1, n1);
    std::cout << std::endl;

    double a2 = 0.1;
    double b2 = 0.2;
    double c2 = 0.4;
    double d2 = 0.2;
    double u2 = 0.8;
    int n2 = 10;
    simulateNonlinear(a2, b2, c2, d2, u2, n2);

    return 0;
}
  
Линейная модель
Time Step | Temperature
----------|------------
0         | 0
1         | 0.27
2         | 0.351
3         | 0.3753
4         | 0.38259
5         | 0.384777
6         | 0.385433
7         | 0.38563
8         | 0.385689
9         | 0.385707
Нелинейная модель
Time Step | Temperature
----------|------------
0         | 0
1         | 0.568294
2         | 0.625124
3         | 0.461392
4         | 0.431455
5         | 0.46404
6         | 0.472645
7         | 0.467669
8         | 0.46556
9         | 0.466284
```
