#include <iostream>
#include <vector>
#include "function.h"


int main()
{
	std::vector <double> linearT = linear(20);
	std::vector <double> nonlinearT = nonlinear(20);
	std::cout << "i" << "\t" << "Linear" << "\t" << "Nonlinear" << std::endl;
	for (int i = 0; i < iterations; ++i)
	{
		std::cout << i << "\t" << linearT[i] << "\t\t" << nonlinearT[i] << std::endl;
	}
	return 0;
}