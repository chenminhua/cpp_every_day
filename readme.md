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

### 指针

c++中创建指针时，计算机将分配用来存储地址的内存，但不会分配用来存储指针指向的数据的内存。**记住在对指针应用解引用操作前，一定要将指针初始化为一个确定的地址。**下面这段代码非常危险。

```cpp
long * p;
*p = 23333 // p确实是一个指针，但是并不知道其会执行哪里，这时候进行解引用操作和赋值操作非常危险。
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

## 连接器

源程序分开单独编译，然后在恰当的时候整合到一起。
典型的连接器把由编译器和汇编器生产的若干模块整合成一个被称为载入模块或可执行文件的实体，该实体能被操作系统直接执行。
