# Study-Note
To record nodes of studying 

简单技巧：

1.if (N & N-1) == 0， 则N一定是2的 n次幂


thread_test.cpp:
  多进程通信的方式之一，如果子进程退出，父进程得知子进程退出。
  如果子进程没有退出，为了防止父进程中 wait() 一直阻塞，定时循环fork()出一个undefined子进程，立刻exit()
  通过上面的方式，可以激活wait()阻塞
