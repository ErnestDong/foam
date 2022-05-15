---
tags: CS
---
# C/Cpp

## 面向对象

### init

类如果没有显式的声明以下六种函数，编译器会自动添加（需要的时候才添加），而且都不会被派生类继承：

- 构造函数
- 析构函数
- 拷贝构造函数
- 重载赋值操作符函数
- 取址运算符重载函数
- const 取址运算符重载函数

```cpp
class A {
  public:
    A();
    ~A();
    A(const A &);
    A &      operator=(const A &);
    A *      operator&();
    const A *operator&() const;
}
```

## 拷贝构造、重载

在声明的时候将一个已经存在的对象赋值给他，调用的是拷贝构造函数；

如果对象已经存在，将另一个对象赋值给他，调用的就是重载赋值操作符函数

在传递参数或者是函数返回值时，如果不是引用，则会调用拷贝构造函数。

```cpp
#include <iostream>
using namespace std;

class CTest {
  public:
    CTest() {
        cout << "init." << endl;
    }
    ~CTest() {
    }

    CTest(const CTest &test) {
        cout << "copy constructor." << endl;
    }

    void operator=(const CTest &test) {
        cout << "operator=" << endl;
    }

    void Test(CTest test) {
    }

    CTest Test2() {
        CTest a;
        return a;
    }

    void Test3(CTest &test) {
    }

    CTest &Test4() {
        CTest *pA = new CTest;
        return *pA;
    }
};

int main() {
    CTest obj;

    CTest obj1(obj); // 调用复制构造函数

    obj1 = obj; // 调用重载赋值操作符

    /* 传参的过程中，要调用一次复制构造函数
     * obj1入栈时会调用复制构造函数创建一个临时对象，与函数内的局部变量具有相同的作用域
     */
    obj.Test(obj1);

    /* 函数返回值时，调用复制构造函数；将返回值赋值给obj2时，调用重载赋值操作符
     * 函数返回值时，也会构造一个临时对象；调用复制构造函数将返回值复制到临时对象上
     */
    CTest obj2;
    obj2 = obj.Test2();

    obj2.Test3(obj); // 参数是引用，没有调用复制构造函数

    CTest obj3;
    obj2.Test4(); // 返回值是引用，没有调用复制构造函数

    return 0;
}
```

### 委托构造

### virtual

函数继承的是调用权

- 非虚函数：不希望子类被 override
- 虚函数 virtual：希望子类 override，并提供了默认定义
- 纯虚函数 virtual const=0：子类必须 override

## 内存管理

### 堆栈

[[数据结构#栈]]是程序自动生成的，生命期在作用域内；static 对象在程序结束时生命期结束

[[heap]]是手动管理的，delete 之后指向对象生命期结束

### new & delete

new 先分配内存（内部调用 malloc），然后转型（static_cast），再调用构造函数

delete 先调用析构函数，再释放内存（内部调用 free）

VC 编译器在 new 时候会对象前后加一个 cookie，cookie 值为整个对象大小的 16 进制+1

new String[3] 一定要调用 delete[] *p 是因为这样才能调用多次析构函数

### static

静态数据多个对象共享一份

静态函数没有 this 指针，只能处理静态数据，可以用对象调用或类名直接调用

## STL

C++ 的标准模版库 STL 有 6 大类

- algorithms
- containers
- allocator
- iterators
- functors

## 容器

### sequence container

方便排序、查找，包括 array vector deque list forward-list

### associative container

方便大量查找，包括 set/multiset（key-value 不分） map/multimap（key-value 查询），通常用[[红黑树]]实现

### unordered container

也是一种关联容器，是不定序的容器，[[哈希表]] 的 separate chaining 链接法实现

## 分配器

```cpp
// 标准的位于
#include<memory>
// 非标准的，gnu的在ext下面，包括
#include<ext/array_allocator.h>
// in __gnu_cxx namespace
#include<ext/mt_allocator.h>
#include<ext/debug_allocator.h>
#include<ext/pool_allocator.h>
#include<ext/bitmap_allocator.h>
#include<ext/malloc_allocator.h>
#include<ext/new_allocator.h>
```

搭配不同的分配器，在 container 上的写法是

```cpp
list<string, allocator<string>> c;
```

实现了 allocate, deallocate

不应该直接使用，因为不用容器和手动 malloc free 之外反而更复杂
