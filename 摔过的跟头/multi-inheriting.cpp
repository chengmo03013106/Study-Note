// 多态的核心思想，就是用一个通用的基类指针，调用不同的派生类实例中的不同方法
// 为了实现这个目的，需要借助虚方法，虚继承
// 所谓的“虚” 就是把直接的调用，静态的调用，通过指针的形式间接调用，就是把直接转化成间接

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
通过上面的内存分布可以看出：
1、一个类中的某个方法被声明为虚函数，则它将放在虚函数表中。
2、当一个类继承了另一个类，就会继承它的虚函数表，虚函数表中所包含的函数，如果在子类中有重写，则指向当前重写的实现，否则指向基类实现。
若在子类中定义了新的虚函数，则该虚函数指针在虚函数表的后面（如Human类中的breathe，在eat的后面）。
3、在继承或多级继承中，要用一个祖先类的指针调用一个后代类实例的方法，若想体现出多态，则必须在该祖先类中就将需要的方法声明为虚函数
否则虽然后代类的虚函数表中有这个方法在后代类中的实现，但对祖先类指针的方法调用依然是早绑定的。
（如用Animal指针调用Asian实例中的breathe方法，虽然在Human类中已经将breathe声明为虚函数，依然无法调用Asian类中breathe的实现，但用Human指针调用Asian实例中的breathe方法就可以）。
*/

//菱形继承 
#include <iostream>

using namespace std;

class Animal {
public:
    int name;
    virtual void breathe() {
        cout << "Animal breathe" << endl;
    }
};

class LandAnimal: public Animal {
public:
    int numLegs;
    virtual void run() {
        cout << "Land animal run" << endl;
    }
};

class Mammal: public Animal {
public:
    int numBreasts;
    virtual void milk() {
        cout << "Mammal milk" << endl;
    }
};

class Human: public Mammal, public LandAnimal {
public:
    int race;
    void milk() {
        cout << "Human milk" << endl;
    }
    void run() {
        cout << "Human run" << endl;
    }
    void eat() {
        cout << "Human eat" << endl;
    }
};

int main(void) {
    Human human;

    cout << "用LandAnimal指针调用Human实例的方法" << endl;
    LandAnimal *laPtr = NULL;
    laPtr = &human;
    laPtr->run();

    cout << "用Mammal指针调用Human实例的方法" << endl;
    Mammal *mPtr = NULL;
    mPtr = &human;
    mPtr->milk();

    cout << "用Animal指针调用Human实例的方法" << endl;
    Animal *aPtr = NULL;
    aPtr = &human; // error: base class "Animal" is ambiguous

    return 0;
}

// 此时需要使用虚继承，用来解决菱形继承的问题
class Animal {
public:
    int name;
    virtual void breathe() {
        cout << "Animal breathe" << endl;
    }
};

class LandAnimal: virtual public Animal {
public:
    int numLegs;
    virtual void run() {
        cout << "Land animal run" << endl;
    }
};

class Mammal: virtual public Animal {
public:
    int numBreasts;
    virtual void milk() {
        cout << "Mammal milk" << endl;
    }
};

//当使用虚继承时，子类的实例中并不包括基类实例的一份内存，而是加了一个vbptr(虚基表 (virtual base)) 指针，避免内存中同时存在基类的共同方法而出现冲突
