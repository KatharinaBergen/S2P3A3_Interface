#include <exception>
#include <iostream>
#include "MyRangeVector.h"

int main() try
{

	tests(); 

	return 0;
}
catch (const std::exception& e)
{
	std::cerr << e.what();
	return -1;
}
catch (...)
{
	std::cerr << "unkown error";
	return -2;
}