#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//constants
const double a = 0.1;
const double b = 0.2;
const double c = 0.3;
const double d = 0.4;
const double InpTemp = 20;
const int iterations = 50;

vector <double> linear(double u)
{
	vector <double> temps(iterations);
	temps[0] = InpTemp;
	for (int i = 0; i < iterations - 1; ++i)
	{
		temps[i + 1] = a * temps[i] + b * u;
	}
	return temps;
}

vector <double> nonlinear(double u)
{
	vector <double> temps(iterations);
	temps[0] = InpTemp;
	for (int i = 1; i < iterations - 1; ++i)
	{
		temps[i + 1] = a * temps[i] - b * temps[i - 1] * temps[i - 1] + c * u + d * sin(u);
	}
	return temps;
}

int main()
{
	setlocale(0, "");
	vector <double> linearT = linear(20);
	vector <double> nonlinearT = nonlinear(20);
	cout << "i" << "\t" << "Линейная" << "\t" << "Нелинейная" << endl;
	for (int i = 0; i < iterations; ++i)
	{
		cout << i << "\t" << linearT[i] << "\t\t" << nonlinearT[i] << endl;
	}
}
