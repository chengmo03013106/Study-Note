Compiler will not do this, manual write codes like    
  <code>
  int res = a+b+c+d;
  int res = (a+b)+(c+d);
  </code>
  for out order with processors flow      
  declare variable in the function because of stack ( data is mirrored in Level 1 cache)    
  variable will not be free until function, except that which stored in register. To avoid this, using {} .    
  global stored in static scope. static scope used for static variable, virtual function tables, array initializer list, switch statement jump tables.  
  
  Advantage : static value should be initialized before program run.  
  Disadvantage: stored whole program running time.  
  
  global should be avoided, except that multi threads communicating.  
  integer values are supposed to no cache problem.  
  register 8 floating registers in 32 bits system, 16 for 64 bits system.  
  
  volatile can changed by other thread.  
  // Example 7.3. Explain volatile  
  ···c
  volatile int seconds; // incremented every second by another thread
  void DelayFiveSeconds() {
    seconds = 0;
    while (seconds < 5) {
      // do nothing while seconds count to 5
    }  
  }  
  ```
  
"second" will not be changed if there is no volatile before it. here 'second' could be changed by other threads.  
But it will failed to set the 'second' when other thread who want to set the value as well.  
it doesn't mean that atomic.  

__thread or declare (__thread) is inefficient because there is only 1 point to point the thread evn list, using these value as stack.  

heap can easily fragmented.  

class object not be stored in register, but its data member can be stored in register.  
static class member will be located in static memory, it should be only one, common variable will be stored in each instance of class.  

`int res = (a*b) / c , a*b will be overflow, this is not be check automatically.`  
unsigned vs signed integer:  
unsigned is faster if divide a integer with a constant , it also suit for the module "%"  
signed for convert to double.  
```c
unsigned n = 15;	15/5	or 15%5 is faster.
double c = a*2.5; a is signed is faster
```

integer addition, substruction, comparsion, bit operation are same time clock cycle.
multiple is almost 10 times of clock cycle, division is 40-80 times of clock cycle.

increasement and decreasement are no different except the case which in `while` and `for` case.
`x = array[i++]` is more efficient than `x = array[++i]`, because x should wait for `i`'s value 2 clock cycle.
`a = ++b` is more efficient than `a = b++` because compiler recognize a is equal b and store them in the same register.

TODO:  
  3.template class is more efficient than a polymorphous class?    
  4. pros and cons of using class ......      
  5. drawback of dynamic memory will be discussed later ...  
