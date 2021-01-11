#include "MyVectorSimple.h"

myVectorSimple::myVectorSimple(int s) : sz{ s }, elem{ new double[s] {} } {}
myVectorSimple::myVectorSimple() : myVectorSimple{ 0 } {}
myVectorSimple::~myVectorSimple() { delete[] elem; }
//…
int myVectorSimple::size() const { return sz; }

double& myVectorSimple::operator[](int index)
{
	if (index < 0 || sz <= index) throw std::runtime_error("myVector::operator[](), bad index");
	return elem[index];	// TODO: insert return statement here
}

const double& myVectorSimple::operator[](int index) const
{
	if (index < 0 || sz <= index) throw std::runtime_error("myVector::operator[](), bad index");
	return elem[index];
}
