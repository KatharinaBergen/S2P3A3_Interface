#include "MyRangeVector.h"
#include <iostream>

myRangeVec::myRangeVec(int lo, int hi)
	: myVectorSimple(hi - lo + 1), lb{ lo } 
{
	if (lo > hi ) throw std::runtime_error("myRangeVec(), bad params: lower param bigger than higher");
}

int myRangeVec::low() const { return lb; }
int myRangeVec::high() const { return lb + size() - 1; }

double& myRangeVec::operator[](int i) 
{
	return myVectorSimple::operator[](i - lb);
}

const double& myRangeVec::operator[](int i) const 
{
	return myVectorSimple::operator[](i - lb);
}

bool myRangeVec::test(int lb, int sz, double elem[])
{
	if (this->lb == lb &&
		this->size() == sz)
	{
		for (int i{}; i < size() - 1; ++i)
		{
			if (!(this->operator[](i) == elem[i])) { return false; }
			// std::cout << this->operator[](i) << ", " << elem[i] << std::endl;
		}
		
		return true;
	}
	return false;
}


void tests()
{
	myRangeVec actual{ 0,0 };
	int lb{ 0 };
	int sz{ 1 }; 
	double elem[]{ 0.0 };
	printTestResults(0, true, actual.test(lb, sz, elem));
	
	myRangeVec actual1{ 0,5 };
	actual1[0] = 0.0;
	actual1[1] = 1.0;
	actual1[2] = 2.0;
	actual1[3] = 3.0;
	actual1[4] = 4.0;
	int lb1{ 0 };
	int sz1{ 6 };
	double elem1[]{ 0, 1, 2, 3, 4 };
	printTestResults(1, true, actual1.test(lb1, sz1, elem1));

	myRangeVec actual2{ 0,5 };
	int lb2{ 0 };
	int sz2{ 6 };
	double elem2[]{ 0 };
	printTestResults(2, false, actual2.test(lb2, sz2, elem2));

}

void printTestResults(int testnumber, bool expectedResult, bool actualResult)
{
	if (actualResult == expectedResult) { std::cout << "test number " << testnumber << " succeeded. \n"; }
	else { std::cout << "test number " << testnumber << " failed. \n"; }
}
