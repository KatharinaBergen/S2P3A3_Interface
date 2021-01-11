#ifndef MYRANGEVEC_H
#define MYRANGEVEC_H

#include "MyVectorSimple.h"

class myRangeVec : public myVectorSimple {
public:
	myRangeVec() = delete;
	myRangeVec(int lo, int hi);
	int low() const;
	int high() const;
	double& operator[](int i);
	const double& operator[](int i) const;
	bool test(int lb, int sz, double elem[]);
	
private:
	int lb; // lower bound, also der untere Index
};

void tests();
void printTestResults(int testnumber, bool expectedResult, bool actualResult);


#endif // !MYRANGEVEC_H
