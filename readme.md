# c++ 组成
- c: blocks, statements, preprocessor, pointers
- 面向对象 c++: class, 封装，继承，多态，virtual 函数（动态绑定）
- template c++: 泛型编程
- STL: template 程序库。容器，迭代器，算法，函数对象。。。

## style guide

[google cpp style guide](https://google.github.io/styleguide/cppguide.html)

# 类型

## 类型别名

```cpp
#define BYTE char  // 预处理器，预编译阶段替换，无脑替换
#define addNum(x,y) (x + y)

typedef char BYTE  // 重命名，参与编译。

using FP = void (*) (int, const std::string&);
// 类似于typedef，但是支持template，仅可用于c++11之后
// 等价于 typedef void (*FP) (int, const std::string&);
```

## 数组

- 数组名可以理解为指向数组第一个元素的指针。
- 数组名和指针的区别在于，sizeof(数组名) 返回整个数组的长度（单位为字节）。
- stack[1]表达式在编译器看来就是 \*(stack+1)
- 将数组名与指针对应，可以在将数组地址作为参数传递时节省复制数组所需资源。
- 使用数组声明来创建数组时，采用静态联编，数组的长度在编译时设置。
- 使用 new[] 来创建数组时，采用动态联编，在运行时为数组分配空间，其长度也将在运行时设置。需要使用 delete[] 释放其占用的内存。
- 为了防止函数无意中修改数组内容，可以在声明形参时使用关键字 const。这意味着不能使用 arr 来修改该数据。

```cpp
void show_array(const double arr[], int n);
```

## string

- c++处理字符串：一种是 c-style string,第二种是基于 string 类库的方法。
- c++的 string 把我们从 char\*中拯救了出来，比如，比较 char\*需要使用 strcmp() 方法，而比较 string 字符串只需要 ==。
- 拼接 string 也只需要使用 + 操作符。使用 string 类库需要 include string.h

## struct

```c
typedef struct Person {
    string name;
    string country;
    int age;
}Person;

Person p = { "bigtom", "china", 27 };
Person people[100];
```

如果你有一个指针 p, 则毫不犹豫地使用 p->field。如果你在处理一个值 v,则使用 v.field

## union

union 的用途之一是，当数据项使用两种或更多格式时，可以节省空间。如下，one4all 类型的变量中，同时只能存下一个 int 或者 long 或者 double

```cpp
// 定义
union one4all {
  int int_val;
  long long_val;
  double double_val;
}
```

也可以使用匿名 union

```cpp
struct widget {
  char brand[20];
  int type;
  union {
    long id_num;
    char id_char[20];
  };
}

widget price;
...
price.id_num;
```

## enum

```cpp
enum {red, orange, yellow, green, blue, violet, indigo, ultraviolet};
```

# 指针

**记住在对指针应用解引用操作前，一定要将指针初始化为一个确定的地址。**下面这段代码非常危险。

```cpp
long * p;
*p = 23333 // p确实是一个指针，但是并不知道其会执行哪里，这时候进行解引用操作和赋值操作非常危险。
```

```c
int x = 1, y = 2, z[10];
int * ip       // ip 是一个指向int的指针
ip = &x;       // ip 现在指向x
y = *ip;        // y = 1
*ip = 0;        // x = 0
ip = &z[0];     // ip现在指向z[0]

void * vp    // 可以指向任意类型的指针
void swap(int *px, int *py)   // 指针参数使得我们可以在函数中访问和改变对象
```

### 指针与数组

```c
int a[10];
int *pa;
pa = &a[0];    // 等价于 pa = a
int a1 = *(pa+1)   // a[i] 等价于 *(a+i)，事实上c就是把 a[i] 转换成 *(a+i)
```

数组名和指针很类似，但是它们之间有一个区别，指针是一个变量，但数组名不是。
在作为函数的参数时，数组和指针是等价的，但一般用指针更好（更清晰）,如下：

```c
int strlen(char *s) {...}

strlen("hello, world");   // 传入字符串合法
strlen(array);            // 传入char数组合法
strlen(ptr);              // 传入char指针合法
```

### 指向函数

```cpp
void estimate(int lines, double(*pf)(int)) {
        cout << (*pf) (lines) << endl;
}

double pam(int lns) {
        return 0.03 * lns + 0.0004 * lns * lns;
}

estimate(12, pam);
```

### const int \* （指向 const 的指针）

```c
int a1 = 1;
int a2 = 3;
const int * p = &a1;
printf("%p: %d\n", p, *p);
p = &a2;                  // 合法，指针可以指向其他地方
printf("%p: %d\n", p, *p);
*p = 3;   // 报错，指针指向的值不能改变
```

### int\* const （const 指针）

```c
int a = 1;
int b = 2;
int* const p = &a;
*p = 3;     // 合法, 指针的值可以改变
p = &b;     // 报错，指针不能指向其他地方
```

### const int\* const

指针不能指向其他地方，指针的指向的值也不能改变

### string (char \*)

c 语言里面处理字符串非常糟糕，还好 string.h 里面定义了很多方法

```c
// c里面复制字符串需要使用strcpy函数
void strcpy(char *s, const char *t) {
  while(*s++ = *t++);
}

// c里面的字符串比较strcmp
int strcmp(char *s, char *t) {
  for (; *s == *t; s++; t++) {
    if (*s == '\0') return 0;
  }
  return *s - *t
}
```

# 引用

引用是已定义的变量的别名。引用变量的主要用途是用作函数的形参。通过将引用变量用作参数，函数将使用原始数据，而不是其拷贝。

```cpp
int rats = 101;
int & rodents = rats;
// 引用必须在声明时初始化。
// 之后对rodents的任何操作都会改变rats,注意这里&不是取地址操作。int & 表示一个引用类型。
// rats和rodents不论地址还是值都是一样的。

void swap(int & a, int & b) {
  int temp;
  temp = a;
  a = b;
  b = temp;
}
```

有时候我们会让函数直接返回引用类型。通常情况下返回机制将返回值复制到临时存储区域，随后调用程序将访问该区域。而返回引用则意味着调用程序将直接访问返回值，而不需要拷贝。
返回引用时需要注意： **应当避免返回当函数终止时不再存在的内存单元引用**。

**将类对象传递给函数时，c++通常的做法是使用引用。**

继承的一个特征是，一个基类的引用可以指向派生类对象，而无需进行强制类型转换。因此可以定义一个接受基类引用作为参数的函数，在调用该函数的时候可以将基类或派生类的对象作为参数。比如 ostream & 可以接受 ostream 对象和 ofstream 对象。这就是多态啦。

# 内存管理

malloc 返回一个空指针，用于分配内存。比如开辟一块内存给一个数组，这个数组可以放入 howMany 个 int 数。free 用于释放内存。

```c
char *ptr;
ptr = (char *)malloc(24);   // 分配24个char大小的内存空间
strcpy(ptr, "hello there");
free(ptr);
```

自动存储: 在函数内部定义的常规变量使用自动存储空间，被称为自动变量。在函数被调用时自动产生，在函数结束时消亡。（不用手动管理）
静态存储：整个程序执行期间都存在。使变量称为静态的方式有两种：1.static关键字，2.在函数外定义它。
动态存储：new, delete

## new and delete
使用new请求正确数量的内存，返回指向该块内存的指针。使用指针来跟踪内存的位子，使用delete释放使用new分配的内存。在c中我们需要使用malloc和free来处理内存的分配和回收

```c
int *parr = new int[10];
delete[] parr; // 方括号告诉程序，需要释放整个数组，而不仅仅是指针指向的元素。

当计算机内存不够时，new将会返回0。在c++中，值为0的指针被称为空值指针。
不要使用delete来释放不是new分配的内存。
不要使用delete释放同一个内存块两次。
如果使用new[]为数组分配内存，则应使用delete[]来释放。
如果使用new[]为一个实体分配内存，则应使用delete来释放。
对空值指针应用delete是安全的。
```

# 虚函数

[为啥需要 virtual 函数](https://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c)
没有 virtual 的话，就会 early binding，也就是说调用的 method 在编译时就被决定了。

纯虚函数是在基类中声明的虚函数，它在基类中没有定义，但要求任何派生类都要定义自己的实现方法。在基类中实现纯虚函数的方法是在函数原型后加“=0”
virtual void funtion1()=0
含有纯虚拟函数的类称为抽象类，它不能生成对象。

### Explicit 指定符

修饰构造函数，被修饰的类不能发生隐式类型转换

# cpp 11
## auto 类型推导

c++11 中使用 auto 实现类型推导，c++98 中使用 auto 表示变量为自动变量（现在已经废除）

## lambda 表达式

在 c++11 之后可以使用。 （编译时使用-std=c++11）

```c++
int a[6] = {9,8,2,3,5,4};
std::sort( a, &a[6], [](int x, int y){ return x < y;  }  );
for (int i=0; i<6; i++)
    cout << a[i] << ",";
```

## 右值引用

C++中所有的表达式和变量要么是左值，要么是右值。通俗的左值的定义就是非临时对象，那些可以在多条语句中使用的对象。所有的变量都满足这个定义，在多条代码中都可以使用，都是左值。右值是指临时的对象，它们只在当前的语句中有效。

如果临时对象通过一个接受右值的函数传递给另一个函数时，就会变成左值，因为这个临时对象在传递过程中，变成了命名对象。

右值引用是用来转移语义的。通过转移语义，临时对象中的资源可以转移到其他对象中。

如果已知一个命名对象不再被使用而想对它调用转移构造函数，可以使用 std::move 函数，把左值引用变成右值引用。

```cpp
// 接收左值
void process_value(int &i)
{
    cout << "LValue processed: " << i << endl;
}

// 接收右值
void process_value(int &&i)
{
    cout << "RValue processed: " << i << endl;
}

// 转发，临时对象在此过程中，由右值变成了左值。
void forward_value(int &&i)
{
    process_value(i);
}

// 通过Move减少了三次不必要的拷贝
template <typename T>
void swapit(T &a, T &b)
{
    T tmp(move(a));
    a = move(b);
    b = move(tmp);
}

int main()
{
    int a = 0;
    process_value(a);
    process_value(1);
    process_value(2);
    int x = 10;
    int y = 20;
    cout << "x=" << x << "  y=" << y << endl;
    swapit(x, y);
    cout << "x=" << x << "  y=" << y << endl;
}

// LValue processed: 0
// RValue processed: 1
// RValue processed: 2
// x=10  y=20
// x=20  y=10
```

# oop
### 构造函数
构造函数用于构建类的对象。如果用户没有提供构造函数，c++将自动提供默认构造函数。
**在设计类时，最好主动提供对所有类成员做隐式初始化的构造函数，而不要使用编译器提供的默认构造函数。**

```cpp
class Stock {
public:
  // 声明构造函数
  Stock(const std::string &company, int shares, double share_val);
private:
  std::string company;
  int shares;
  double share_val;
}
// 定义构造函数
Stock::Stock(const std::string &company, int shares, double share_val)
    : company(company), shares(shares), share_val(share_val) {}

Stock s0 = Stock("nano", 20, 12.5);  // 显式调用构造函数
Stock s1("nano", 20, 12.5);          // 隐式调用构造函数
s1.show();

Stock *s2 = new Stock("nano", 20, 12.5);   // 构造函数与new结合使用,返回对象指针。这种情况下对象没有名称，但可以通过指针操作对象
s2->show();
```

tip: **如果既可以通过初始化，也可以通过赋值来设置对象的值，则应该采用初始化方式。通常效率更高**

### 析构函数
对象过期时，程序将自动调用一个特殊的成员函数：析构函数。析构函数负责save our ass。比如说你在构造函数里面使用new分配了一些内存，就需要在析构函数中调用delete来释放这些内存。上面的代码中，我们没有在构造函数中通过new分配内存，所以也不需要在析构函数中执行delete操作，这时候我们直接使用编译器生成的什么都不做的析构函数。

通常不应该在代码中显式调用析构函数（有例外情况），而应该让编译器决定什么时候调用析构函数。如果是静态存储变量，则析构函数在程序结束时调用。如果是自动变量，则在程序执行完代码块时调用。如果对象是通过new创建的，则析构函数在使用delete释放内存时调用。

### 隐式成员函数
c++自动提供了下面这些成员函数：
  默认构造函数，
  复制构造函数，
  赋值操作符，
  默认析构函数，
  地址操作符

### 复制构造函数
复制构造函数用于将一个对象复制到一个新对象中，它用于初始化过程。原型为Class_name (const Class_name &);新建一个对象并将其初始化为同类对象的时候，复制构造函数都会被调用。最常见的情况还是将新对象显示初始化为现有对象的时候。
比如 StringBad sailer = sports；
实际调用了 StringBad sailor = StringBad(sports);
除此之外，当函数按值传递对象时，或者函数返回对象时，也都将调用复制构造函数。
使用默认复制构造函数存在一些危险，比如你希望在构造函数里面搞点黑科技，但是忘了重写复制构造函数。。。可以考虑使用显式复制构造函数来解决。

### const成员函数
const成员函数表明该函数不能修改对象。我们应该尽量将成员函数标记为const成员函数。

### this指针
每个成员函数(包括构造函数和析构函数)都有一个this指针，指向调用对象。如果函数需要使用整个对象而非地址（比如要返回对象引用），则可以使用*this解引用。

```cpp
class Stock {
public:
  const Stock & topval(const Stock & s) const;
}
const Stock & Stock::topval(const Stock & s) const {
  return s.total_val > total_val ? s : *this;
}
```

### 静态类成员
？？

### 操作符重载
operator overloading是一种形式的多态。c++允许将操作符重载扩展到用户定义的类型，比如让两个对象相加。

```h
// time.h
class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int h, int m=0);

    // 重载
    Time operator+ (const Time & t) const;
    Time operator* (double n) const;

    void Show() const;
};
```

```cpp
// time.cpp
Time::Time() {
    hours = minutes = 0;
}

Time::Time(int h, int m) {
    hours = h;
    minutes = m;
}

Time Time::operator+ (const Time & t) const {
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator* (double mult) const {
        Time result;
        long totalminutes = hours * mult * 60 + minutes * mult;
        result.hours = totalminutes / 60;
        result.minutes = totalminutes % 60;
        return result;
}

void Time::Show() const {
        cout << hours << ":" << minutes << endl;
}
```

```cpp
// main.cpp
Time coding(2, 40);
Time fixing(5, 55);
Time total;

coding.Show();
total = coding + fixing;
total.Show();
```

### 友元
c++控制对类对象私有部分的访问。通常，公有类方法提供唯一的访问途径，但是有时候这种限制太严格。此时c++提供了另一种形式的访问权限：友元。

友元有三种：友元函数，友元类，友元成员函数。

在函数重载的例子中，我们希望 time * 10 和 10 * time 相同，但是通过函数重载是做不到的。

```cpp
// 友元函数，处理 10 * time 这种情况
friend Time operator* (double n, const Time & t) {
    // 调用了被重载的 * 运算符
    return t * n;
};

// 重载<<操作符是一种常用的友元
friend std::ostream & operator<< (std::ostream & os, const Time & t);

std::ostream & operator<< (std::ostream & os, const Time & t) {
    os << t.hours << ":" << t.minutes << endl;
    return os;
}
```

### 动态内存分配
让程序在运行时决定内存分配，而不是在编译时决定。这样可以根据需要来使用内存。但是在类中使用new，delete操作符会导致许多编程问题。析构函数将变得必不可少（需要在析构函数中释放内存）

# boost
TR1是一份规范，描述加入c++标准程序库的诸多新机能。
boost是个组织，也是一个网站 http://boost.org, 提供开放的c++程序库。

# template
Bjarne 在《The Design and Evolution of C++》一书中，详细的解释了 C++为什么会变成如今（C++98/03）的模样。
模板作为 C++中最有特色的语言特性，它堪称玄学的语法和语义，理所应当的成为初学者的梦魇。但是实际上 C++模板远没有想象的那么复杂。我们只需要换一个视角：在 C++03 的时候，模板本身就可以独立成为一门“语言”。

# template function

```cpp
// 注意class关键字可以替换为typename关键字
template <class Any>
void Swap(Any &a, Any &b) {
  Any temp;
  temp = a;
  a = b;
  b = temp;
}
int x,y;
...
swap(x,y);
```

如上，在编译时，当遇到一个调用两个 int 引用参数时，编译器生成 swap 函数的 int 版本。

为了进一步了解模板，必须理解实例化和具体化。在代码中编写函数模板并不会生成函数定义，它只是一个用于生成函数定义的方案。而当编译器发现程序调用 swap(x,y)时，会生成一个 swap(int &, int &)的实例。这种实例化被称为**隐式实例化**。

现在 c++还允许显示实例化，可以直接命令编译器创建特定的实例，如 Swap<int>()。编译器看到这个声明将直接创建函数实例。

```cpp
template void Swap<int> (int, int);
```

除此之外，还可以使用显示具体化方法，让编译器不按照 swap()模板来生成函数定义。

```cpp
template <> void Swap<int> (int &, int &);
```

编译器在选择函数原型时，遵循的规则是：非模板版本 优先于 显示具体化 优先于 模板版本。
