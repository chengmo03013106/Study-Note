测试代码
compiling codes with -std=c++11

template 关注 编译器 和 组合特性

模板实例化

隐式实例化：成员只有被引用到才会进行实例化，或者被称为推迟实例化

显式实例化


错误例子：

#include <iostream>

// 计算 N 的阶乘 N!
template<int N>
class aTMP{
public:
    enum { ret = N==0 ? 1 : N * aTMP<N-1>::ret }; // Lazy Instantiation，将产生无限递归!
};

int main(){
    std::cout << aTMP<10>::ret << '\n';
    std::cin.get(); return 0;
}

上面的错误是因为，当编译 aTMP<N> 时，并不判断 N==0，而仅仅知道其依赖 aTMP<N-1>（lazy instantiation），从而产生无限递归，纠正方法应该使用模板特例化：

#include <iostream>

// 计算 N 的阶乘 N!
template<int N>
class aTMP{
public:
    enum { ret = N * aTMP<N-1>::ret };
};
template<>
class aTMP<0>{
public:
    enum { ret = 1 };
};

int main(){
    std::cout << aTMP<10>::ret << '\n';
    std::cin.get(); return 0;
}

不同文件中如果有两个链接实例相同，比如print<double>
链接时消除了一个（消除哪个没有规定，上面消除了 b.cpp 中的）。

#include <iostream>

template<typename T>
class aTMP{
public: typedef const T reType;
};

void f() { std::cout << "global f()\n"; }

template<typename T>
class Base {
public:
    template <int N = 99>
    void f() { std::cout << "member f(): " << N << '\n'; }
};

template<typename T>
class Derived : public Base<T> {
public:
    typename T::reType m; // typename 不能省略
    Derived(typename T::reType a) : m(a) { }
    void df1() { f(); }                       // 调用全局 f()，而非想象中的基类 f()
    void df2() { this->template f(); }        // 基类 f<99>()
    void df3() { Base<T>::template f<22>(); } // 强制基类 f<22>()
    void df4() { ::f(); }                     // 强制全局 f()
};

int main(){
    Derived<aTMP<int>> a(10);
    a.df1(); a.df2(); a.df3(); a.df4();
    std::cin.get(); return 0;
}

输出
global f()
member f(): 99
member f(): 22
global f()


