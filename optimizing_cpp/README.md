Compiler will not do this, manual write codes like for out order with processors flow:    
  ```
  int res = a+b+c+d;
  int res = (a+b)+(c+d);
  ```      
Declare variable **in function** because of stack ( data is mirrored in Level 1 cache)    
Variable will not be free until function, except that which stored in register. To avoid this, using {}    

Global stored in static scope. static scope used for static variable, virtual function tables, array initializer list, switch statement jump tables.    
  Advantage : static value should be initialized before program run.  
  Disadvantage: stored whole program running time.  
Global variable should be avoided, except that multi threads communicating.  


### basic value type
Integer values are supposed to no cache problem.  
Register 8 floating registers in 32 bits system, 16 for 64 bits system.  

Volatile can changed by other thread.    
```c
// Example 7.3. Explain volatile  
volatile int seconds; // incremented every second by another thread
void DelayFiveSeconds() {
  seconds = 0;
  while (seconds < 5) {
    // do nothing while seconds count to 5
  }  
}  
```  
"Second" will not be changed if there is no volatile before it. here 'second' could be changed by other threads.  
But it will failed to set the 'second' when other thread who want to set the value as well.  
it doesn't mean that atomic.  

__thread or declare (__thread) is inefficient because there is only 1 point to point the thread evn list, using these value as stack.  

Heap can easily fragmented.  

Class object not be stored in register, but its data member can be stored in register.  
static class member will be located in static memory, it should be only one, common variable will be stored in each instance of class.  

`int res = (a*b) / c , a*b will be overflow, this is not be check automatically.`  

### unsigned vs signed integer:  
1.Unsigned is faster if divide a integer with a constant , it also suit for the module "%"  
2.Signed is faster convert to double.  
```c
unsigned n = 15;	15/5	or 15%5 is faster.
double c = a*2.5; a is signed is faster
```

Integer addition, substruction, comparsion, bit operation are same time clock cycle.
multiple is almost 10 times of clock cycle, division is 40-80 times of clock cycle.

Increasement and decreasement are no different except the case which in `while` and `for` case.
`x = array[i++]` is more efficient than `x = array[++i]`, because x should wait for `i`'s value 2 clock cycle.
`a = ++b` is more efficient than `a = b++` because compiler recognize a is equal b and store them in the same register.

### Loop control:
```c
// Example 7.31a
// upper string
char string[100], *p = string;
while (*p != 0) *(p++) |= 0x20;
```
If the length is known, it 's more efficient as follow:   
```c
// Example 7.31b
char string[100], *p = string; int i, StringLength;
for (i = StringLength; i > 0; i--) *(p++) |= 0x20;
```
`for (i = (int)n - 2, x = 2.0; i >= 0; i--, x++) factorial *= x;`
more efficient than  
`for (x = 2.0; x > 10; x++) factorial *= x;`

`if (x > 0)` better than `if (x > non-zero)`
For the array index , The data cache is optimized for accessing arrays `forwards`, not `backwards`.

## Function:
Avoid unnecessary functions,Splitting up a function into multiple smaller functions only makes the program less efficient, it just make it clear.

Using inline functions and template and define.

### Function's Parameters:
1.Simple function parameters are transferred on the stack in 32-bit systems, but in registers in
64-bit systems.
2.The return type of a function should preferably be a simple type, a pointer, a reference, or
void，Returning objects of a composite type is more complex and often inefficient.

### Function tail calls is more efficient:
```c
// Example 7.36. Tail call with return value
  int function2(int x);
  int function1(int y) {
    ...
    return function2(y+1);
  }
```

### Class and structure:
1.class object will take up one register which is scarely in 32bit.
2.There is no performance penalty for organizing data into classes or structures.
```c
// Example 7.40
class S2 {
  public:
    int a[100]; // 400 bytes. first byte at 0, last byte at 399
    int b; // 4 bytes. first byte at 400, last byte at 403
    int ReadB() {return b;}
};

class S3 {
  public:    
    int b; // 4 bytes. first byte at 400, last byte at 403
    int ReadB() {return b;}
    int a[100]; // 400 bytes. first byte at 0, last byte at 399        
};
```
<font color=#8B008B size=3>a and b swapped is more efficient because of if the offset is not larger than 128 bytes. </font>
<font color=#8B008B size=3>compiler can access it directly rather than using pointer.</font>

static member function is faster than member function because 'this' pointer is no need.
mk it staticed if it needn't access any un-static function or data.

##  Runtime type identification (RTTI): is not efficient. 
If the compiler has an option for RTTI then turn it off and use alternative implementations.

## Template programming:
```c
// Example 7.46
// pass m in runtime
int Multiply (int x, int m) {
  return x * m;
}

// Passing m in compile time.
// To avoid m overhead, but it will make code big, per m will generated one codes of function.

template <int m>
int MultiplyBy (int x) {
  return x * m;
}

int a, b;
a = Multiply(10,8);			// except it is declared as inlined.
b = MultiplyBy<8>(10);	// this one is faster because compiler recognize 10*8 earlier and replaced by (10 <<3)
```

## multi-threads optimizing:
### Here are 4 kinds of costs to multithreading take into account.
1. too short for the thread start and stop costs.
2. cost of threads switch.
3. communicated with threads, volatile is considered. to grantee the value re-read before using.
4. storage with each threads.

### others:
1.static various should be used in thread.
2.using thread safe function.

## Exception is good in sometimes:
it raised by hardware and it will not cost any extra time.
```c
float a = 1.0; b = 2.0;
for ( int i = 0; i < 10000; i++) {	
	try {
		a = log(a*b);
		a *= b;
	}
	except FLT_OVERFLOW{
		a = log(a) * log(b);		// here will double call log(), log() may be the extra consuming function.
	}
}
```

上面的例子，省去了循环中，每次保证浮点不溢出，所以每次进行浮点比较。
如果发现溢出异常，直接执行更好的处理，从而节约了比较的性能。
这里干得漂亮！终于找到了异常的意义所在。

Things that may need to be cleaned up include:
> * Memory allocated with new or malloc.
> * Handles to windows, graphic brushes, etc.
> * Locked mutexes.
> * Open database connections.
> * Open files and network connections.
> * Temporary files that need to be deleted.66
> * User work that needs to be saved.
> * Any other allocated resource


## TODO:  
  3.template class is more efficient than a polymorphous class?    
  4. pros and cons of using class ......      
  5. drawback of dynamic memory will be discussed later ...  
