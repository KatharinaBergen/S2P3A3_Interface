#include <stdexcept>
#ifndef MYVECTORSIMPLE_H
#define MYVECTORSIMPLE_H

class myVectorSimple {
	int sz; double* elem;
public:
	explicit myVectorSimple(int s);
	myVectorSimple();
	~myVectorSimple();
	//…
	int size() const;
	virtual double& operator[](int index);
	const virtual double& operator[](int index) const;

};

#endif // !MYVECTORSIMPLE_H
