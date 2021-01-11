#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <exception>
#include <iostream>
using std::cout;

template<class T> class MyVector {

private:

	int size;	//#of values in vector
	T* elem;	//pointer to first element
	int space;	//space in memory for vector. size cannot surpass space. 
				//If vector needs more space, the vector needs to be allocated/moved/copied to a different space in the memory.


public: //inline definition is necessary for templates. 
	MyVector();
	explicit MyVector(int s, T elements);
	MyVector(int size, int space, T content[]);
	MyVector(const MyVector& v);
	MyVector& operator=(const MyVector& other);
	~MyVector();
	int getSize() const;
	int getCapacity() const;
	T& operator[](int n);
	const T& operator[](int n) const;
	T& at(int n);
	const T& at(int n) const;
	void reserve(int newspace);
	void resize(int newsize, T = T{});
	void push_back(const T& t);
	void print() const;
	void test(const int& testnumber, const MyVector<T>& expected);

};


	//Standardconstructor
	template<class T>
	MyVector<T>::MyVector() : size{ 0 }, space{ 0 }, elem{ nullptr }
	{
		cout << "\nStandardconstructor called.\n";
	}

	//typical vector constructor, defines how many elements are held in the vector
	template<class T>
	MyVector<T>::MyVector(int s, T elements) : size{ s }, space{ s }, elem{ new T[s]{} }
	{
		cout << "\nConstructor called." << " elem: " << elem << " elem input: " << s << std::endl;
	}

	//constructor for testing purposes
	template<class T>
	MyVector<T>::MyVector(int size, int space, T content[]) : size{ size }, space{ space }, elem{ new T[size] {} }
	{
		if (size > space) throw std::runtime_error{ "critical error. size is bigger than space at testing constructor." };
		else if (size == space) cout << "warning. size is the same size as space at testing contructor. last item ignored.";
		for (int i{}; i < size; i++)
		{
			this->elem[i] = content[i];
		}
	}

	//Copyconstructor
	template<class T>
	MyVector<T>::MyVector(const MyVector& v) : size{ v.size }, space{ v.space }, elem{}
	{
		for (int i{}; i < v.size; i++)
		{
			this->elem[i] = v.elem[i];
		}
		cout << "\nCopyconstructor called.\n";
	}

	//operator= 
	template<class T>
	MyVector<T>& MyVector<T>::operator=(const MyVector& other)
	{
		cout << "\noperator= called.\n";

		if (this == &other) return *this;
		if (other.size <= space)
		{ // genug Platz, d.h. keine weitere Allokation
			for (int i{}; i < other.size; ++i) elem[i] = other.elem[i]; // Elemente kopieren
			size = other.size;
			return *this;
		}
		// copy & swap:
		T* p{ new T[other.size] }; // Platz aus dem Heap holen
		for (int i{}; i < other.size; ++i) p[i] = other.elem[i]; // Elemente kopieren
		delete[] elem; // alten Speicherplatz feigeben
		elem = p; // Zeiger umhaengen
		space = size = other.size; // beide Zaehler richtig setzen
		return *this;
	}

	//Destructor
	template<class T>
	MyVector<T>::~MyVector()
	{
		cout << "\nDestructor called.\n";

		if (size != 0)
		{
			delete[] elem;
			elem = nullptr;
		}
	}

	//getter size
	template<class T>
	int MyVector<T>::getSize() const
	{
		return size;
	}

	//getter space
	template<class T>
	int MyVector<T>::getCapacity() const
	{
		return space;
	}

	//operator[]
	template<class T>
	T& MyVector<T>::operator[](int n)
	{
		cout << "\noperator[] called.\n";

		return elem.at(n);
	}

	//const operator[]
	template<class T>
	const T& MyVector<T>::operator[](int n) const
	{
		return const_cast<MyVector*>(this)->operator[](n);
	}

	//adress operator vector.at()
	template<class T>
	T& MyVector<T>::at(int n) // Zugriffsbereich ueberprueft
	{
		if (n < 0 || size <= n)
		{
			throw std::runtime_error("MyVector::at(), bad index");
		}
		return elem[n];
	}

	//adress const operator vector.at()
	template<class T>
	const T& MyVector<T>::at(int n) const
	{
		return const_cast<MyVector*>(this)->at(n);
	}

	//reseve new space in memory
	template<class T>
	void MyVector<T>::reserve(int newspace)
	{
		if (newspace <= space) return; // nie weniger Platz holen
		T* p{ new T[newspace] }; // mit new Speicher allokieren
		for (int i{}; i < size; ++i) // Elemente kopieren
			p[i] = elem[i];
		delete[] elem; // alten Speicher freigeben
		elem = p; // Zeiger umhaengen
		space = newspace;
	}

	//resize the vector
	template<class T>
	void MyVector<T>::resize(int newsize, T elements)
	{
		//cout << "\nresize() called.\n";

		reserve(newsize); // Speicher im Heap reservieren
		for (int i{ size }; i < newsize; ++i) // Initialisierung der
			elem[i] = T{}; // zusaetzlichen Elemente
		size = newsize;

	}

	//push back new T into vector
	template<class T>
	void MyVector<T>::push_back(const T& t)
	{
		cout << "\npushback() called.\n";

		if (space == 0)
		{
			reserve(8);
		}
		else if (space == size)
		{
			reserve(space * 2);
		}
		elem[size] = t;

		cout << elem[size];
		size++;
	}

	template<class T>
	void MyVector<T>::print() const
	{
		for (int i{}; i < size; ++i)
		{
			cout << this->at(i) << ", ";
		}
	}

	template<class T>
	void MyVector<T>::test(const int& testnumber, const MyVector<T>& expected)
	{
		if (size == expected.size &&
			space == expected.space &&
			elem[0] == expected.elem[0])
		{
			cout << "\nTest " << testnumber << " succeeded.";
		}
		else cout << "\nTest " << testnumber << " failed.";
	}

void tests() {

	cout << "----------------------TESTS---------------------------------\n" << std::endl;

	//#1
	MyVector<int> actual1{};
	actual1.push_back(1);
	actual1.push_back(2);
	actual1.push_back(3);

	int expectedContent1[]{ 1,2,3 };
	MyVector<int> expected1{ 3, 8, expectedContent1 };

	actual1.test(1, expected1);

	//#2
	MyVector<int> actual2{};
	actual2.push_back(1);
	actual2.push_back(2);
	actual2.push_back(3);
	actual2.push_back(4);
	actual2.push_back(5);
	actual2.push_back(6);
	actual2.push_back(7);
	actual2.push_back(8);
	actual2.push_back(9);
	actual2.push_back(10);

	int expectedContent2[]{ 1,2,3, 4, 5, 6, 7, 8, 9, 10 };
	MyVector<int> expected2{ 10, 16, expectedContent2 };

	actual2.test(2, expected2);

	//#3
	MyVector<double> actual3{};
	actual3.push_back(1.1);
	actual3.push_back(2.2);
	actual3.push_back(3.3);

	double expectedContent3[]{ 1.1,2.2,3.3 };
	MyVector<double> expected3{ 3, 8, expectedContent3 };

	actual3.test(3, expected3);


	//#4
	MyVector<double> actual4{};
	actual4.push_back(1);
	actual4.push_back(2);
	actual4.push_back(3);
	actual4.push_back(4);
	actual4.push_back(5.05);
	actual4.push_back(6);
	actual4.push_back(7);
	actual4.push_back(8);
	actual4.push_back(9);
	actual4.push_back(10);
	actual4.push_back(11);
	actual4.push_back(12);
	actual4.push_back(13);
	actual4.push_back(14);
	actual4.push_back(15);
	actual4.push_back(16);
	actual4.push_back(17);
	actual4.push_back(18.06);

	double expectedContent4[]{ 1,2,3, 4, 5.05, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18.06 };
	MyVector<double> expected4{ 18, 32, expectedContent4 };

	actual4.test(4, expected4);


	//#5
	MyVector<char> actual5{};
	actual5.push_back('c');
	actual5.push_back('v');
	actual5.push_back('f');

	char expectedContent5[]{ 'c', 'v', 'f' };
	MyVector<char> expected5{ 3, 8, expectedContent5 };

	actual5.test(5, expected5);


	//#6
	MyVector<std::string> actual6{};
	actual6.push_back("abc");
	actual6.push_back("def");
	actual6.push_back("ghi");

	std::string expectedContent6[]{ "abc", "def", "ghi" };
	MyVector<std::string> expected6{ 3, 8, expectedContent6 };

	actual6.test(6, expected6);


	//#7 -------------------issue with expectedContent requireing the '0' to be innitialized.....................??????????????????????????????????????????????????????
	MyVector<int> actual7{};

	int* expectedContent7{ new int[0] {} };
	MyVector<int> expected7{ 0, 0, expectedContent7 };

	actual7.test(7, expected7);


	//#8
	MyVector<std::string> actual8{};
	actual8.push_back("abc");

	std::string expectedContent8[]{ "abc" };
	MyVector<std::string> expected8{ 1, 8, expectedContent8 };

	actual8.test(8, expected8);
}



#endif // !MYVECTOR_H



