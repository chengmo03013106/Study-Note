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
Unsigned is faster if divide a integer with a constant , it also suit for the module "%"  
Signed is faster convert to double.  
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

### Function:
Avoid unnecessary functions,Splitting up a function into multiple smaller functions only makes the program less efficient, it just make it clear.

Using inline functions and template and define.

### Function's Parameters:


TODO:  
  3.template class is more efficient than a polymorphous class?    
  4. pros and cons of using class ......      
  5. drawback of dynamic memory will be discussed later ...  
