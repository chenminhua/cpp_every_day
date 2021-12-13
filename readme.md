## 类型系统

### 数组

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

### string

- c++处理字符串：一种是 c-style string,第二种是基于 string 类库的方法。
- c++的 string 把我们从 char\*中拯救了出来，比如，比较 char\*需要使用 strcmp() 方法，而比较 string 字符串只需要 ==。
- 拼接 string 也只需要使用 + 操作符。使用 string 类库需要 include string.h

### struct

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

### union

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

### enum

```cpp
enum {red, orange, yellow, green, blue, violet, indigo, ultraviolet};
```

# 指针

c++中创建指针时，计算机将分配用来存储地址的内存，但不会分配用来存储指针指向的数据的内存。**记住在对指针应用解引用操作前，一定要将指针初始化为一个确定的地址。**下面这段代码非常危险。

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

### 引用

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

## 连接器

源程序分开单独编译，然后在恰当的时候整合到一起。
典型的连接器把由编译器和汇编器生产的若干模块整合成一个被称为载入模块或可执行文件的实体，该实体能被操作系统直接执行。
