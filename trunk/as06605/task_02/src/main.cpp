#include <iostream>
#include <vector>
#include "function.h"
using namespace std;

int main()
{
	vector <double> linearT = linear(20);
	vector <double> nonlinearT = nonlinear(20);
	cout << "i" << "\t" << "Linear" << "\t" << "Nonlinear" << endl;
	for (int i = 0; i < iterations; ++i)
	{
		cout << i << "\t" << linearT[i] << "\t\t" << nonlinearT[i] << endl;
	}
	return 0;
}