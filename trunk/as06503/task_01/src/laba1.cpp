#include <iostream>
#include <cmath>
using namespace std;
//константы
const int n = 10; // такты времени
const double a = 0.99;
const double b = 0.01;
const double c = 0.5;
const double d = 0.1;
const double Y0 = 18;

//линейная
double linear(double yt, double ut) {
    return a * yt + b * ut;
}

//нелинейная
double nonlinear(double yt, double yt_1, double ut, double ut_1) {
    return a * yt - b * pow(yt_1,2) + c * ut + d * sin(ut_1);
}

int main() {
    setlocale(LC_ALL,"RU");
    cout << "Линейная модель"<<endl;
    cout << "y0 = " << Y0<<endl;
    double u[10] = {5,7,6,5,7,6,5,7,6,5};
    double yt = Y0;
    for (int i=0;i<n;i++){
        yt = linear(yt, u[i]);
        cout << "y" << i+1 << " = " << yt<<endl;
    }
    cout << "\n";
    double yt_1;
    yt = Y0;
    yt_1 = yt;
    cout << "Нелинейная модель" << endl;
    cout << "y0 = " << Y0 << endl;
    for (int i = 0; i < n-1; i++) {
        yt_1=yt;
        yt = nonlinear(yt, yt_1, u[i+1], u[i]);
        cout << "y" << i+1 << " = " << yt << endl;
    }
    system("pause");
    return 0;
}
