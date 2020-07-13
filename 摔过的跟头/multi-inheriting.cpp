#include <iostream>

using namespace std;

class Animal {
public:
    char *name;
    void breathe() {
        cout << "Animal breathe" << endl;
    }
    virtual void eat() {
        cout << "Animal eat" << endl;
    }
};

class Human: public Animal {
public:
    int race;
    virtual void breathe() {
        cout << "Human breathe" << endl;
    }
    void eat() {
        cout << "Human eat" << endl;
    }
};

class Asian : public Human {
public:
    int country;
    void breathe() {
        cout << "Asian breathe" << endl;
    }
    void eat() {
        cout << "Asian eat" << endl;
    }
};

int main(void) {
    Animal animal;
    Human human;
    Asian asian;

    Animal *anPtr = NULL;
    Human *hmPtr = NULL;
    Asian *asPtr = NULL;

    cout << "用Animal指针调用human和asian实例" << endl;
    anPtr = &human;
    anPtr->breathe();
    anPtr->eat();
    anPtr = &asian;
    anPtr->breathe();
    anPtr->eat();

    cout << endl;
    cout << "用Human指针调用asian实例" << endl;
    hmPtr = &asian;
    hmPtr->breathe();
    hmPtr->eat();

    return 0;
}

//运行结果如下
//用Animal指针调用human和asian实例
//Animal breathe
//Human eat
//Animal breathe
//Asian eat
//
//用Human指针调用asian实例
//Asian breathe
//Asian eat
/*
有上面的内存分布可以看出：
1、一个类中的某个方法被声明为虚函数，则它将放在虚函数表中。
2、当一个类继承了另一个类，就会继承它的虚函数表，虚函数表中所包含的函数，如果在子类中有重写，则指向当前重写的实现，否则指向基类实现。
若在子类中定义了新的虚函数，则该虚函数指针在虚函数表的后面（如Human类中的breathe，在eat的后面）。
3、在继承或多级继承中，要用一个祖先类的指针调用一个后代类实例的方法，若想体现出多态，则必须在该祖先类中就将需要的方法声明为虚函数
否则虽然后代类的虚函数表中有这个方法在后代类中的实现，但对祖先类指针的方法调用依然是早绑定的。
（如用Animal指针调用Asian实例中的breathe方法，虽然在Human类中已经将breathe声明为虚函数，依然无法调用Asian类中breathe的实现，但用Human指针调用Asian实例中的breathe方法就可以）。
*/
