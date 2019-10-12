
## 调试python 进程 （python3）
gdb支持调试python 可以通过 gdb -p attach 到python执行的进程

1.确认python安装时支持debug

2.安装python3-debuginfo(python-debuginfo)，对于RHEL和CentOS
```
wget http://ftp.us2.freshrpms.net/linux/mageia/distrib/cauldron/x86_64/media/debug/core/release/python3-debuginfo-3.8.0-0.rc1.1.mga8.x86_64.rpm
rpm-ivh python3-debuginfo-3.8.0-0.rc1.1.mga8.x86_64.rpm
```

3.编辑 ~/.gdbinit
```
python
import sys
sys.path.append('/root/Python-3.5.6/Tools/gdb/')
import libpython
reload(libpython)
```

usage:
```
gdb python3 -p pid
```
键入 "py-" tab 可以看到
py-bt       py-bt-full  py-down     py-list     py-locals   py-print    py-up
选项，没有支持的gdb应该只有python 一个选项

通过py-bt可以看到python程序的调用进程堆栈信息，bt可以查看原生gdb的对战信息
相比单纯的查阅代码，更容易定位问题所在




## 异常处理
应该精细化使用异常的范围和异常种类。
精确捕捉一些会发生异常的代码以及发生异常的种类，从而做相对的处理。
如果异常国语笼统，会妨碍程序调试，异常会吞掉很多程序中的错误。

### partial( func, *args, **kwargs )
可以起到warpper func函数的作用

### 通过捕捉到异常作相应的函数返回值

### 函数返回*None* 比较笼统，让使用者不明白None到底是什么意思？空？执行错误？

### 使用try except KeyError 代替容器判断 "in","not in"

### bisect 即 二分法，可以替换程序中出现的大量 if/else
