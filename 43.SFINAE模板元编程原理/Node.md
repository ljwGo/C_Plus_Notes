[toc]

# 0. 序言

参考[雾里看花：真正意义上的理解 C++ 模板 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/655902377)

​	c++模板涉及4种功能需求

* 代码生成
* 类型约束
* 编译期间计算
* 类型操作



其中, **模板原本的职责应该是代码生成**. 早期后三种功能通过**一些trick**, 也交由模板来实现了, 这些代码称为TMP(Template meta programme)模板元编程. 如今

* 类型约束由(requires c++20)来完成
* 编译期间计算由(constexpr)
* 类型操作可能由未来的静态反射来完成



# 1. 模板实例化过程(Instantiation)

(1) 检查类型是否有匹配的模板,该过程和重载函数选定类似

```c++
template <typename T>
void F(T a, T b) {  };

struct A{};
struct B{};

int main(void) {
	F(A(), B());  // error. Can not find an match template function 
	F(A(), A());  // ok. Start Specific progress.
	return 0;
}
```

(2) 尝试产生**模板特例(specialization)**,也就是具体的类



# 2. SFINAE (Substitution Failure Is Not An Error)

**利用模板函数重载解析不会报编译错误的方式实现判断的逻辑**, 前提必须能找到至少一个符合要求的函数模板.

基于字面量

```c++
template<int I>
void div(char(*)[I % 2 == 0] = nullptr)
{
	// this overload is selected when I is even
	cout << "d1" << endl;
}

template<int I>
void div(char(*)[I % 2 == 1] = nullptr)
{
	// this overload is selected when I is odd
	cout << "d2" << endl;
}

int main(void) {
	div<10>();  // 被实例化为第一个div
	div<11>();  // 被实例化为第二个div
	return 0;
}
```

基于类型(其中...重载函数优先级最低)

```c++
#include <iostream>

// 使用class时注意访问权限
struct A { using type = A; };  // 可见using和typedef关键字都可以定义类型
struct C { typedef C type; };

template <typename T>
void F(typename T::type) {  // typename修饰的是最右边的符号
	std::cout << "f1" << std::endl;
};

// 兜底
template <typename T>
void F(...) {
	std::cout << "f2" << std::endl;
};

template <typename T>
void F(typename T::type*) {  // typename修饰的是最右边的符号
	std::cout << "f3" << std::endl;
};

int main(void) {

	F<A>();  // f2 因为没有实参
	F<A>(A());  // f1 第一个实参A类型, 具有type
	F<A>(0);  // f3 第一个实参是int类型, 可以看作A*的地址
	F<C>(C());  // f1
	F<C>(0);  // f3
	F<int>(0);  // f2 int不具有type类型

	return 0;
}
```

使用**类型的成员**

```c++
#include <iostream>

template <int N>
struct a {};
template <template<typename T> class>  // 这里必须是class
struct b {};

using namespace std;

template<typename T>
void f(typename T::v*) {
	cout << "f" << endl;
};

template<typename T>
void g(a<T::v>*) {
	cout << "g" << endl;
};

template<typename T>
void g1(T::v*) {  // T::v不是类型名; 只能使用T::v*
	cout << "g1" << endl;
};

template<typename T>
void h(b<T::template v>*) {
	cout << "h" << endl;
};

template<typename T>
void h1(T::template v*) {
	cout << "h1" << endl;
};

struct A {};
struct B { int v; };
struct C { typedef int v; };
struct D { typedef int v; };
struct B1 { typedef int v; };
struct C1 { static const int v = 0; };
struct D1
{
	template<typename T>
	struct v {};
};

int main(void) {
	//f<A>(0);  // A does not contain a member v
	//f<B>(0);  // The v member of B is not a type
	//g<C>(0); // The v member of C is not a non-type
	//h<D>(0); // The v member of D is not a template

	f<B1>(0);
	g<C1>(0);
	//g1<C1>(0);  // 报错. 因为T::v是左值, T::v*也不是类型, 这里需要一个类型
	h<D1>(0);
	//h1<D1>(0);  // 报错.

	return 0;
}
```

## 2.1 使用函数模板实例化重载实现if逻辑

```c++
#include <iostream>

using namespace std;

class Test {};
struct TT {};

template <typename T>
class A {
public:
	typedef char yes[1];
	typedef char no[2];

	template<typename C>
	static yes& f(int C::*) {}  // selected if C is a class type

	template<typename C>
	static no& f(...) {}

	// 必须是常量类型
	static bool const value = sizeof(f<T>(nullptr)) == sizeof(yes);
};

int main(void) {
	cout << A<Test>::value << endl;
	cout << A<int>::value << endl;
	cout << A<TT>::value << endl;
	return 0;
}
```

可以看到, 将参数T做为参数使用; **利用模板函数重载判定**, 实现判断逻辑, **最后根据返回值判断执行结果**

## 2.2 使用decltype优化

decltype的作用类似auto, 自动推导类型. 不过decltype使用场景范围更广, 它**根据表达式决定类型**

```c++
#include <iostream>
#include <type_traits>

using namespace std;

class Test {};
struct TT {};

template <typename T>
class A {
public:
	template<typename C>
	static int f(int C::*) {}  // selected if C is a class type

	template<typename C>
	static void f(...) {}

	// 必须是常量类型
	static bool const value = std::is_same_v<int, decltype(f<T>(nullptr))>;
};

int main(void) {
	cout << A<Test>::value << endl;
	cout << A<int>::value << endl;
	cout << A<TT>::value << endl;
	return 0;
}
```

## 2.3 Some error

当发生SFINAE后, 再次找不到匹配的模板函数重载将会发生硬编码错误

```c++
template <typename T>
struct B {
	using type = typename B::type;
};

// 这个例子不太明白
template<
    class T,
    class U = typename T::type,    // SFINAE failure if T has no member type
    class V = typename B<T>::type> // hard error if B has no member type
									// (guaranteed to not occur via CWG 1227 because
									// substitution into the default template argument
									// of U would fail first)
void foo(int);

// 这个例子不太明白
template <typename T>
typename T::type f(typename B<T>::type);

template <typename T>
auto f(typename B<T>::type) -> typename T::type ;  // redeclaration

template <typename T>
void f(...) {};

using R = decltype(f<int>(0));  // ill-formed, no diagnostic required(一种错误行为)
```

- attempting to give an invalid type to a non-type template parameter:

```c++
template<class T, T>
struct S {};

template<class T>
int f(S<T, T()>*);

struct X {};
int i0 = f<X>(0);
```

- attempting to perform an invalid conversion in

  - in a template argument expression

  - in an expression used in function declaration:

```c++
template<class T, T*> int f(int);
int i2 = f<int, 1>(0); // can’t conv 1 to int*
```

The following expression errors are SFINAE errors

- Ill-formed expression used in a template parameter type
- Ill-formed expression used in the function type:

```c++
struct X { };
struct Y { Y(X) {} }; // X is convertible to Y

template<class T>
auto f(T t1, T t2) -> decltype(t1 + t2); // overload #1

// 显示生成的函数类型
X f(Y, Y) { return X(); };                               // overload #2

X x1, x2;
// 必须写入返回值, 这样才能才能使用显示生成的函数. 否则将查找模板, 尝试生成.
X x3 = f(x1, x2);	// deduction fails on #1 (expression x1 + x2 is ill-formed)
					// only #2 is in the overload set, and is called

```

# 3. std::void_t 使用

定义:

```c++
template <typename ...Types>
using void_t = void;
```

void_t 在模板参数都正确的情况下等于void, 它的作用类似**集装箱**.



例子:

```c++
#include <iostream>
#include <type_traits>

using namespace std;

struct A { using type = int; typedef int type2; };
struct B { using type = int;};

//template <typename ...Types>
//using void_t = void;

//template <typename T, typename V = void>
//void f(T){ cout << "f1" << endl; };

// 模板复用, void不能做为类型, 但是可以做为模板类型参数
// 对于模板函数, 只有在参数列表中使用了, 才会检查对应模板参数是否正确(比如这里跳过了void_t的检查, 因为没有用到)
//template <typename T>
//void f<T, void_t<typename T::type, typename T::type2>>(T) {
//	cout << "f2" << endl;
//};

// 主模板
// 使用结构体无论是否用到, 都会进行检查
template <typename T, typename V = void>
struct f{
	f() {
		cout << "f1" << endl;
	}
};

//必须使用std::void_t
//template <typename T>
//struct f<T, typename T::type> {
//	f() {
//		cout << "f3" << endl;
//	}
//};

//模板复用, 复用主模板
template <typename T>
struct f<T, void_t<typename T::type, typename T::type2>> {
	f() {
		cout << "f2" << endl;
	}
};

int main(void) {
	f<int>();  // f1 因为int没有type和type2, 检测失败
	f<A>();  // f2 因为A有type和type2, void_t = void类型, 并传入模板
	f<B>();  //	f1
	return 0;
}
```



# 4. std::declval使用

declval的作用是在**不调用K的构造函数的前提下, 生成一个K类的右值引用**. 注意一定是右值引用.

```c++
K v = declval<K>();
```



例子: (检测类型T是否可比较)

```c++
#include <type_traits>
#include <iostream>

using namespace std;

struct B {};
struct C { bool operator== (const C& other) { return true; } };

template <typename T, typename U = void>
struct A : std::false_type {};

//template <typename T>
//struct A<T, decltype(std::declval<T>() == std::declval<T>())> : std::true_type {};

// 次要模板的优先级更高
template <typename T>
// 必须使用std::void_t
struct A<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type {};

int main(void) {
	cout << A<B>::value << endl;
	cout << A<int>::value << endl;
	cout << A<float>::value << endl;
	cout << A<C>::value << endl;
	return 0;
}
```



# 5. 一些例子

判断一个类型是否可以引用

```c++
#include <iostream>
#include <type_traits>

using namespace std;

template<typename T, typename U = void>
struct A {
	using lRef = T;
	using rRef = T;

	A() {
		cout << "A1" << endl;
	}
};

template<typename T>
struct A<T, std::void_t<T&>> {
	using lRef = T&;
	using rRef = T&&;

	A() {
		cout << "A2" << endl;
	}
};

int main(void) {
	A<int> a;
	A<void> b;
	return 0;
}
```

判断一个方法是否在一个对象中(**a.\*f, 其中a是对象, f是函数地址**).

类的数据在内存中是多份的, 函数代码是唯一的.

```c++
#include <iostream>
#include <type_traits>

using namespace std;

class A {
public:
	void fn() {}
};

class B {
public:
};

template <typename T, typename C>
auto f(T t, C c) -> decltype((t.*c)()) {
	cout << "f1" << endl;
};

template <typename T, typename C>
auto f(T t, C c) -> decltype((t->*c)()) {
	cout << "f2" << endl;
};

void f(...) {
	cout << "f3" << endl;
}

int main(void) {
	A a;
	B b;
	f(a, &A::fn);  // f1
	f(&a, &A::fn);  // f2
	f(3, 3);  // f3
	f(b, &A::fn);  // f3
	return 0;
}
```

# 6. std::enable_if

[std::enable_if](https://en.cppreference.com/w/cpp/types/enable_if)的作用, 可以手动控制是否选择该模板重载. 用法查看源码就好.

```c++
#include <iostream>
#include <type_traits>

using namespace std;

struct C
{
	using type = float;
};

struct B
{
	using type = int;
};

template <typename T, typename U = void>
struct A{ A() { cout << "A1" << endl; } };

// declval返回右值引用
// T必须有类型的type(int 别名)
template <typename T>
struct A<T, std::void_t<typename std::enable_if<std::is_same_v<int&&, decltype(declval<typename T::type>())>, typename T::type>::type>> {
	A() { cout << "A2" << endl; }
}; 

int main(void) {
	//std::is_same_v<int, decltype(declval<typename T::type>())>
	A<int> a;
	A<B> b;
	A<C> c;
	return 0;
}
```

