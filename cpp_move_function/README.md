
Note.move constructure, std::move is supported by c++0x
It's worked with gcc 4.4.7(CentOS 6.x) rather than gcc 4.1.2(CentOS 5.x)

test.h
```c
#include <iostream>
using namespace std;


class A {
public:
        int x;
	char * value;
	A(int x, char * v) : x(x) {
		value = new char[32];
		strncpy(value, v, strlen(v));
		cout << "Constructor" << endl;
	}
	~A() {
		cout << "Deconstructor" << endl;
		delete value;
	}
	A(const A& a) : x(a.x) {
		value = new char[32];
		strncpy(value, a.value, strlen(a.value));
		cout << "Copy Constructor" << endl;
	}
	A& operator=(A& a) {
		x = a.x;
		value = new char[32];
		strncpy(value, a.value, strlen(a.value));
		cout << "Copy Assignment operator" << endl;
		return *this;
	}
	A(A&& a) : x(a.x) {
		value = NULL;
		value = a.value;
		a.value = NULL;
		cout << "Move Constructor" << endl;
	}
	A& operator=(A&& a) {
		x = a.x;
		value = NULL;
		value = a.value;
		a.value = NULL;
		cout << "Move Assignment operator" << endl;
		return *this;
	}
};
```
test.cpp
```c
int move_constructor() {
        cout << "-------------------------1-------------------------" << endl;
        char *tmp[3] = {"one","two","three"};
        A a(1,tmp[0]);
        std::vector<A>  a_vec;
        a_vec.push_back(a);
        cout << a.value << endl;
        A && ma = move(a);
        a_vec.push_back(move(a));
        if( a.value ) {
                cout << "if a.value ok" << a.value << endl;
        }
        return 0;
        cout << "-------------------------2-------------------------" << endl;
        A b = a;
        cout << "-------------------------3-------------------------" << endl;
        A c(a);
        cout << "-------------------------4-------------------------" << endl;
        b = a;
        cout << "-------------------------5-------------------------" << endl;
        A d = A(1,tmp[1]);
        cout << "-------------------------6-------------------------" << endl;
        A e = std::move(a);

```
