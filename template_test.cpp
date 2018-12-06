#include <stdio.h>
#include <string.h>

// class template
// default template arguments could be used in class templates without -std=c++11 or 
template<typename T=int>
class MyNumber{
	public:
		MyNumber(){}
		MyNumber( const T & v ) {val_ = v;}
	private:
		T val_;
};

// function template
// default template arguments may not be used in function templates without -std=c++11 or -std=gnu++11
template<typename T=int>
bool TempEquat( T a, T b) {
	return (false == ((a<b) || (a>b)));
}

// template vector
//
template<typename T, int N>
class MyVec {
	T v_[N];
};

// specific template
template<>
class MyVec<float,4> {
	float v_[4];
};

//
template<typename T1, typename T2>
class TypeSame {	public: enum {ret = false}; };

template<typename T>
class TypeSame<T,T>	{public: enum {ret = true};};


typedef unsigned int uint32_t;

int main(int av, char ** ac) {
	int ret = 0;
	ret = TypeSame<unsigned, int>::ret;
	printf("%d:\t%d\n",__LINE__,ret);
	ret = TypeSame<unsigned, uint32_t>::ret;
	printf("%d:\t%d\n",__LINE__,ret);
	MyNumber<> my_a(1);	// use template class with default type
 	MyNumber<double> my_b(2);
	ret = TempEquat(1,2);	// automatic detect type
	ret = TempEquat<double>(2,2);

	return 0;
}
