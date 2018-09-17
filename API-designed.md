# API designed in QT4

### 6. 命名的艺术
命名很可能是API设计中最重要的一个问题。类应该叫什么名字？成员函数应该叫什么名字？

#### 6.1 通用的命名规则
有几个规则对于所有类型的命名都等同适用。第一个，之前已经提到过，不要使用缩写。即使是明显的缩写，比如把*previous*缩写成*prev*，从长远来看是回报是负的，因为用户必须要记住缩写词的含义。
如果API本身没有一致性，之后事情自然就会越来越糟；例如，Qt 3 中同时存在*activatePreviousWindow()*与*fetchPrev()*。恪守『不缩写』规则更容易地创建一致性的API。

另一个时重要但更微妙的准则是在设计类时应该保持子类名称空间的干净。在Qt 3中，此项准则并没有一直遵循。以*QToolButton*为例对此进行说明。如果调用*QToolButton*的 *name()*、*caption()*、*text()*或者*textLabel()*，你觉得会返回什么？用Qt设计器在*QToolButton*上自己先试试吧：

当你找不到好的命名时，写文档也是个很好方法：要做的就是尝试为各个条目（item）（如类、方法、枚举值等等）写文档，并用写下的第一句话作为启发。如果找不到一个确切的命名，往往说明这个条目是不该有的。如果所有尝试都失败了，并且你坚信这个概念是合理的，那么就发明一个新名字。像**widget**、**event**、**focus**和**buddy**这些命名就是在这一步诞生的。
 #### 6.3 枚举类型及其值的命名
声明枚举类型时，需要记住在 **C++** 中枚举值在使用时不会带上类型（与Java、C#不同）。下面的例子演示了枚举值命名得过于通用的危害：

```
namespace Qt
{
    enum Corner { TopLeft, BottomRight, ... };
    enum CaseSensitivity { Insensitive, Sensitive };
    ...
};
```
```
tabWidget->setCornerWidget(widget, Qt::TopLeft);
str.indexOf("$(QTDIR)", Qt::Insensitive);
```
在最后一行，*Insensitive*是什么意思？命名枚举类型的一个准则是在枚举值中至少重复此枚举类型名中的一个元素：

```
namespace Qt
{
    enum Corner { TopLeftCorner, BottomRightCorner, ... };
    enum CaseSensitivity { CaseInsensitive, CaseSensitive };
    ...
};

tabWidget->setCornerWidget(widget, Qt::TopLeftCorner);
str.indexOf("$(QTDIR)", Qt::CaseInsensitive);
```
当对枚举值进行或运算并作为某种标志（ **flag** ）时，传统的做法是把或运算的结果保存在**int**型的值中，但这不是类型安全的。
```
enum RectangleEdge { LeftEdge, RightEdge, ... };
typedef QFlags<RectangleEdge> RectangleEdges;


enum AlignmentFlag { AlignLeft, AlignTop, ... };
typedef QFlags<AlignmentFlag> Alignment;
```
#### 6.4 函数和参数的命名
函数命名的第一准则是可以从函数名看出来此函数是否有副作用。在 Qt 3 中，const函数*QString::simplifyWhiteSpace()*违反了此准则，因为它返回了一个**QString**而不是按名称暗示的那样，改变调用它的**QString**对象。在 Qt 4 中，此函数重命名为*QString::simplified()*。

#### 6.5 **getter**,**setter** 方法
形容词以is为前缀
> *isChecked()*
> *isDown()*
> *isEmpty()*
> *isMovingEnabled()*
动词，名词一般没有前缀
> *acceptDrops()*，而不是*acceptsDrops()*
> *allColumnsShowFocus()*
名词一般没有前缀：
> *autoCompletion()*，而不是*isAutoCompletion()*
> *boundaryChecking()*

**setter**的名字由**getter**衍生，去掉了前缀后在前面加上了*set*；例如，*setDown()*与*setScrollBarsEnabled()*。

### 7. 避免常见陷阱
#### 7.1 简化的陷阱
一个常见的误解是：实现需要写的代码越少，API就设计得越好。应该记住：代码只会写上几次，却要被反复阅读并理解。例如：

*QSlider *slider = new QSlider(12, 18, 3, 13, Qt::Vertical, 0, "volume");*
这段代码比下面的读起来要难得多（甚至写起来也更难）：
```
QSlider *slider = new QSlider(Qt::Vertical);
slider->setRange(12, 18);
slider->setPageStep(3);
slider->setValue(13);
slider->setObjectName("volume");
```
**【译注】：在有IDE的自动提示的支持下，后者写起来非常方便，而前者还需要看相应的文档。**
