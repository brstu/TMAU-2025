#include "function.h"
#include <vector>
#include <cmath>
using namespace std;

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
	// Initialize temps[1] separately to avoid out-of-bounds access for temps[i-1]
	temps[1] = a * temps[0] - b * temps[0] * temps[0] + c * u + d * sin(u);
	for (int i = 2; i < iterations - 1; ++i)
	{
		temps[i + 1] = a * temps[i] - b * temps[i] * temps[i] + c * u + d * sin(u);
	}
	return temps;
}